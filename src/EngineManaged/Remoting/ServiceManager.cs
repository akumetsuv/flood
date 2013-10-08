﻿using System;
using System.Collections.Generic;
using System.Reflection;
using System.Threading;
using Flood.Remoting.Metadata;

namespace Flood.Remoting
{
    public class ServiceManager
    {
        private Dictionary<int, ServiceStub> stubs;
        private int stubIdCounter;

        private Dictionary<object, ServiceImpl> impls;
        private Dictionary<Tuple<RemotingPeer, int>, ServiceProxy> proxies;

        private Dictionary<Tuple<RemotingPeer, GlobalServiceId>, ServiceProxy> globalServiceProxies;
        private Dictionary<GlobalServiceId, int> localGlobalServiceIds;
        private Dictionary<int, GlobalServiceId> stubIdToGlobalServiceId;

        private MessageProcessor MessageProcessor;

        public ServiceManager(MessageProcessor messageProcessor)
        {
            stubs = new Dictionary<int, ServiceStub>();
            impls = new Dictionary<object, ServiceImpl>();
            proxies = new Dictionary<Tuple<RemotingPeer, int>, ServiceProxy>();
            globalServiceProxies = new Dictionary<Tuple<RemotingPeer, GlobalServiceId>, ServiceProxy>();
            localGlobalServiceIds = new Dictionary<GlobalServiceId, int>();
            stubIdToGlobalServiceId = new Dictionary<int, GlobalServiceId>();

            MessageProcessor = messageProcessor;
        }

        internal void Process(Message data)
        {
            var stubId = data.Header.LocalId;

            if(data.Header.CallType == MessageType.Call)
            {
                var call = Message.Call.Create(data);
                if (stubId == 0)
                    if (!localGlobalServiceIds.TryGetValue(call.GlobalServiceId, out stubId))
                        throw new Exception("Global service unavailable.");

                ((ServiceImpl)stubs[stubId]).ProcessCall(call);
                return;
            }

            var stub = stubs[stubId];

            var impl = stub as ServiceImpl;
            if (impl != null)
            {
                switch (data.Header.CallType)
                {
                    case MessageType.EventSubscribe:
                        impl.ProcessEventSubscribe(data);
                        return;
                    case MessageType.EventUnsubscribe:
                        impl.ProcessEventUnsubscribe(data);
                        return;
                    default:
                        throw new NotImplementedException();
                }
            }

            var proxy = (ServiceProxy)stub;
            switch (data.Header.CallType)
            {
                case MessageType.Reply:
                    proxy.ProcessReply(Message.Reply.Create(data));
                    return;
                default:
                    throw new NotImplementedException();
            }
        }

        protected int GetNextStubId()
        {
            return Interlocked.Increment(ref stubIdCounter);
        }

        public T GetService<T>(int implId)
        {
            var serviceAttribute = typeof (T).GetCustomAttribute<ServiceAttribute>(false);
            var globalServiceAttribute = typeof (T).GetCustomAttribute<GlobalServiceAttribute>(false);
            if (serviceAttribute == null && globalServiceAttribute == null)
                throw new Exception("Type has no attribute Service or GlobalService.");

            ServiceStub stub;
            if(!stubs.TryGetValue(implId, out stub))
                throw new Exception("Local service implementation not found.");

            var impl = (ServiceImpl)stub;
            return (T) impl.Impl;
        }

        public T GetService<T>(RemotingPeer peer, int implId)
        {
            var serviceAttribute = typeof (T).GetCustomAttribute<ServiceAttribute>(false);
            var globalServiceAttribute = typeof (T).GetCustomAttribute<GlobalServiceAttribute>(false);
            if (serviceAttribute == null && globalServiceAttribute == null)
                throw new Exception("Type has no attribute Service or GlobalService.");

            return GetCreateProxy<T>(peer, implId);
        }

        public T GetGlobalService<T>()
        {
            var globalServiceAttribute = typeof (T).GetCustomAttribute<GlobalServiceAttribute>(false);
            if (globalServiceAttribute == null)
                throw new Exception("Type has no attribute Service or GlobalService.");

            var globalServiceId = MessageProcessor.ContextManager.GetGlobalServiceId(typeof(T));

            int serviceId;
            if(!localGlobalServiceIds.TryGetValue(globalServiceId, out serviceId))
                    throw new Exception("Global service not available.");

            return GetService<T>(serviceId);
        }

        public T GetGlobalService<T>(RemotingPeer peer)
        {
            var globalServiceAttribute = typeof (T).GetCustomAttribute<GlobalServiceAttribute>(false);
            if (globalServiceAttribute == null)
                throw new Exception("Type has no attribute Service or GlobalService.");

            var globalServiceId = MessageProcessor.ContextManager.GetGlobalServiceId(typeof(T));
            var tuple = new Tuple<RemotingPeer, GlobalServiceId>(peer, globalServiceId);
            ServiceProxy globalServiceProxy;
            if(globalServiceProxies.TryGetValue(tuple, out globalServiceProxy))
                return (T) (object) globalServiceProxy;

            var ret = GetCreateProxy<T>(peer, 0);
            var proxy = (ServiceProxy) (object) ret;

            globalServiceProxies.Add(tuple, proxy);
            stubIdToGlobalServiceId.Add(proxy.LocalId, globalServiceId);

            return ret;
        }

        public ServiceImpl GetCreateImplementation<T>(T service)
        {
            var serviceAttribute = typeof (T).GetCustomAttribute<ServiceAttribute>(false);
            var globalServiceAttribute = typeof (T).GetCustomAttribute<GlobalServiceAttribute>(false);
            if (serviceAttribute == null && globalServiceAttribute == null)
                throw new Exception("Type has no attribute Service or GlobalService.");

            ServiceImpl impl;
            if (impls.TryGetValue(service, out impl))
                return impl;

            var implId = GetNextStubId();

            var serviceType = typeof(T);

            var stubsType = GetServiceStubType(serviceType);
            var implType = stubsType.GetNestedType("Impl");
            impl = (ServiceImpl)Activator.CreateInstance(implType, service, implId);

            stubs.Add(implId, impl);
            impls.Add(service, impl);
            impl.MessageProcessor = MessageProcessor;

            if (globalServiceAttribute != null)
            {
                var globalServiceId = MessageProcessor.ContextManager.GetGlobalServiceId(typeof(T));
                localGlobalServiceIds.Add(globalServiceId, impl.LocalId);
                stubIdToGlobalServiceId.Add(implId, globalServiceId);
            }

            return impl;
        }

        private T GetCreateProxy<T>(RemotingPeer peer, int implId)
        {
            var tuple = new Tuple<RemotingPeer, int>(peer, implId);
            ServiceProxy proxy;
            if (proxies.TryGetValue(tuple, out proxy))
                return (T)(object)proxy;

            var serviceType = typeof(T);

            var stubsType = GetServiceStubType(serviceType);
            var proxyType = stubsType.GetNestedType("Proxy");

            var proxyId = GetNextStubId();

            var stub = Activator.CreateInstance(proxyType, peer, implId, proxyId);
            proxy = (ServiceProxy) stub;

            stubs.Add(proxyId, proxy);
            proxies.Add(tuple, proxy);
            proxy.MessageProcessor = MessageProcessor;

            return (T)stub;
        }

        private Type GetServiceStubType(Type serviceType)
        {
            var serviceAssembly = serviceType.Assembly;

            var stubClassName = serviceType.FullName.Replace("+", "_") + "Stubs";

            return serviceAssembly.GetType(stubClassName);
        }

        internal bool HasGlobalService(Type type)
        {
            var globalServiceId = MessageProcessor.ContextManager.GetGlobalServiceId(type);
            return localGlobalServiceIds.ContainsKey(globalServiceId);
        }

        internal GlobalServiceId GetGlobalServiceId(int stubId)
        {
            GlobalServiceId globalServiceId;
            if(stubIdToGlobalServiceId.TryGetValue(stubId, out globalServiceId))
                return globalServiceId;

            throw new Exception("Global service unavailable.");
        }
    }
}