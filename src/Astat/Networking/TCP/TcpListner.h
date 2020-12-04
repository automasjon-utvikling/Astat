#pragma once

#include "Astat/Astat.h"

#ifdef AT_PLATFORM_WINDOWS
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#endif

namespace Astat
{
    namespace Networking
    {
        namespace Tcp
        {
            class TcpListner
            {
            public:
                TcpListner(const char* aIpAddress, u_short aPort)
                    : m_IpAddress(aIpAddress), m_Port(aPort), m_SocketId(0), m_Master({ 0 })
                {
                }

                int init( );
                int run( );

            protected:
                virtual void onClientConnect(SOCKET aClientSocketId) = 0;
                virtual void onClientDisconnect(SOCKET aClientSocketId) = 0;
                virtual void onClientMessage(SOCKET aClientSocketId, const char* aMessage) = 0;

                void execSendTo(SOCKET aClientSocketID, const char* aMessage, size_t aLength);
                void execBroadcast(const char* aMessage, size_t aLength);
            
            private:
                void clientConnected();
                void clientHandle(SOCKET aSocket, char aBuffer[4096]); // TODO/FIX: give pointer/reference to buffer  instead of a copy of the buffer
                void clientDisconnected(SOCKET aSocket);

            private:
                const char* m_IpAddress;
                u_short m_Port;
                SOCKET m_SocketId;
                fd_set m_Master;
            };
        }
    }
}


