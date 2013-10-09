﻿
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Threading.Tasks;
using EngineManaged.Modules;
using Flood.Remoting;
using Flood.Remoting.Metadata;

namespace Flood.Modules
{
    public struct ModuleId : IContextId
    {
        public string Name;
        public int MajorVersion;

        public ModuleId(string name, int majorVersion)
        {
            Name = name;
            MajorVersion = majorVersion;
        }

        public void Write(Message data)
        {
            data.Serializer.WriteString(Name);
            data.Serializer.WriteI32(MajorVersion);
        }

        public void Read(Message data)
        {
            Name = data.Serializer.ReadString();
            MajorVersion = data.Serializer.ReadI32();
        }
    }

    public class ModuleManager : IContextLoader
    {
        public readonly ModuleLibrary ModuleLibrary;

        private Dictionary<ModuleId, Assembly> loadedModules;

        private ServiceManager serviceManager;

        public ModuleManager()
        {
            loadedModules = new Dictionary<ModuleId, Assembly>();

            ModuleLibrary = new ModuleLibrary();
        }

        public void Init(ServiceManager serviceManager)
        {
            this.serviceManager = serviceManager;
        }

        IContextId IContextLoader.ReadContextId(Message data)
        {
            var moduleId = new ModuleId();
            moduleId.Read(data);
            return moduleId;
        }

        IContextId IContextLoader.GetContextId(Assembly assembly)
        {
            var assemblyName = assembly.GetName();
            return new ModuleId { Name = assemblyName.Name, MajorVersion = assemblyName.Version.Major };
        }

        async Task<Assembly> IContextLoader.LoadContext(IContextId contextId)
        {
            return LoadModule((ModuleId)contextId);
        }

        public Assembly LoadModule(ModuleId moduleId)
        {
            if(serviceManager == null)
                throw new NullReferenceException("Init ModuleManager before loading any module");

            Assembly assembly;
            if (loadedModules.TryGetValue(moduleId, out assembly))
                return assembly;

            var stream = ModuleLibrary.GetModuleStream(moduleId);
            assembly = Assembly.Load(stream.ReadAllBytes());

            var module = CreateModuleObject(assembly);
            module.OnLoad(serviceManager);

            CheckGlobalServices(assembly);

            return assembly;
        }

        private IModule CreateModuleObject(Assembly assembly)
        {
            Type moduleType = null;
            foreach (var type in assembly.GetTypes())
            {
                if (!typeof (IModule).IsAssignableFrom(type)) 
                    continue;

                if(moduleType != null)
                    throw new Exception("Package can have only one IModule implementation.");

                moduleType = type;
            }

            if(moduleType == null)
                throw new Exception("Package must have one IModule implementation.");

            var ctor = moduleType.GetConstructor(new Type[] {});
            if(ctor == null)
                throw new Exception("Package's IModule implementation must have a paramerless constructor.");

            return (IModule) ctor.Invoke(new object[]{});
        }

        internal void CheckGlobalServices(Assembly assembly)
        {
            foreach (var type in assembly.GetTypes())
            {
                var attribute = type.GetCustomAttribute<GlobalServiceAttribute>();
                if (attribute == null)
                    continue;

                if(!serviceManager.HasGlobalService(type))
                    throw new Exception("Context does not instantiate global service "+type);
            }
        }
    }
}