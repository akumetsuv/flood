﻿using System;
using System.Threading.Tasks;

namespace Flood.Network
{
    /// <summary>
    /// Hosts represents a node connected to the network.
    /// </summary>
    public class Host
    {
        protected Flood.Host host;

        public ServiceManager ServiceManager { get; private set; }
        
        public Host()
        {
            ServiceManager = new ServiceManager();
        }

        protected void OnPacket(Session session, Packet packet, int channel)
        {
            if (packet.Id != 1)
                return;

            var rpcData = RPCDataHelper.CreateRPCData(packet);
            rpcData.Session = session;
            ServiceManager.Process(rpcData);
        }

        public void Update()
        {
            if (host == null)
                return;

            host.ProcessEvents(0);

            if(SendData(1))
                host.ProcessEvents(0);
        }

        private bool SendData(byte channel)
        {
            var hasDataToSend = ServiceManager.Data.Count>0;

            while (ServiceManager.Data.Count != 0)
            {
                var data = ServiceManager.Data.Dequeue(); 
                var packet = RPCDataHelper.CreatePacket(data, 1);
                data.Session.Peer.QueuePacket(packet, channel);
            }

            return hasDataToSend;
        }
    }

    /// <summary>
    /// Represents a server host in the network.
    /// </summary>
    public class Server : Host
    {
        public Server(HostConnectionDetails details)
        {
            FloodNetwork.NetworkInitialize();

            var server = new HostServer();
            host = server;

            server.SessionPacket += OnPacket;
            server.CreateSocket(details);
        }
    }

    /// <summary>
    /// Represents a client host in the network.
    /// </summary>
    public class Client : Host
    {
        public async Task<bool> Connect(HostConnectionDetails details, int timeout = 1000)
        {
            FloodNetwork.NetworkInitialize();

            var client = new HostClient();
            host = client;

            var tcs = new TaskCompletionSource<bool>();

            var session = client.Session;
            session.StateChange += state =>
                                       {
                                           if (state == SessionState.Open)
                                               tcs.SetResult(true);
                                       };

            client.Connect(details);

            // Wait for task somewhere else
            if (await Task.WhenAny(tcs.Task, Task.Delay(timeout)) != tcs.Task)
                return false;

            client.SessionPacket += OnPacket;

            Log.Info("Client connected with session!");
            return true;
        }

        public Session Session
        {
            get { return ((HostClient) host).Session; }
        }
    }
}
