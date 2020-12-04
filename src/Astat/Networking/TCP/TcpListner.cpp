#include "atpch.h"
#include "TcpListner.h"

namespace Astat
{
    namespace Networking
    {
        namespace Tcp
        {
#ifdef AT_PLATFORM_WINDOWS
            int TcpListner::init( )
            {
                WSADATA wsaData;
                WORD version = MAKEWORD(2, 2);

                int wsa_ok = WSAStartup(version, &wsaData);
                if (wsa_ok != 0)
                {
                    return wsa_ok;
                }

                m_SocketId = socket(AF_INET, SOCK_STREAM, 0);
                if (m_SocketId == INVALID_SOCKET)
                {
                    WSACleanup( );
                    return WSAGetLastError( );
                }



                sockaddr_in hint;
                hint.sin_family = AF_INET;
                hint.sin_port = htons(m_Port);
                inet_pton(AF_INET, m_IpAddress, &hint.sin_addr);

                if (bind(m_SocketId, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
                {
                    WSACleanup( );
                    return WSAGetLastError( );
                }

                if (listen(m_SocketId, SOMAXCONN) == SOCKET_ERROR)
                {
                    WSACleanup( );
                    return WSAGetLastError( );
                }

                FD_ZERO(&m_Master);
                FD_SET(m_SocketId, &m_Master);

                return 0;
            }

            int TcpListner::run( )
            {
                bool running = true;

                while (running)
                {
                    fd_set master_copy = m_Master;
                    int socket_count = select(0, &master_copy, nullptr, nullptr, nullptr);

                    for (int i = 0; i < socket_count; i++)
                    {
                        SOCKET socket = master_copy.fd_array[i];

                        if (socket == m_SocketId)
                        {
                            clientConnected( );
                        }
                        else
                        {
                            char buffer[4096];
                            ZeroMemory(buffer, 4096);

                            int bytes_in = recv(socket, buffer, 4096, 0);
                            if (bytes_in <= 0)
                            {
                                clientDisconnected(socket);
                            }
                            else
                            {
                                clientHandle(socket, buffer);
                            }
                        }

                    }
                }

                FD_CLR(m_SocketId, &m_Master);
                closesocket(m_SocketId);

                while (m_Master.fd_count > 0)
                {
                    SOCKET socket = m_Master.fd_array[0];

                    const char* shutdown_message = "¤A00¤";
                    execBroadcast(shutdown_message, sizeof(shutdown_message));
                    FD_CLR(socket, &m_Master);
                    closesocket(socket);
                }

                WSACleanup( );
                return 0;
            }

            void TcpListner::execSendTo(SOCKET aClientSocketID, const char* aMessage, size_t aLength)
            {
                if (aLength > INT_MAX)
                {
                    throw std::overflow_error("TcpListner::execSendTo's aLength is langer than INT_MAX, can't perform static cast from size_t to int!");
                }
                send(aClientSocketID, aMessage, static_cast<int>(aLength), 0);
            }

            void TcpListner::execBroadcast(const char* aMessage, size_t aLength)
            {
                for (unsigned int i = 0; i < m_Master.fd_count; i++)
                {
                    SOCKET socket = m_Master.fd_array[i];
                    if (socket != m_SocketId)
                    {
                        execSendTo(socket, aMessage, aLength);
                    }
                }
            }

            void TcpListner::clientConnected( )
            {
                SOCKET client_socket = accept(m_SocketId, nullptr, nullptr);
                FD_SET(client_socket, &m_Master);
                onClientConnect(client_socket);
            }

            void TcpListner::clientHandle(SOCKET aSocket, char aBuffer[4096])
            {
                onClientMessage(aSocket, aBuffer);
            }

            void TcpListner::clientDisconnected(SOCKET aSocket)
            {
                onClientDisconnect(aSocket);
                closesocket(aSocket);
                FD_CLR(aSocket, &m_Master);
            }
#endif
        }
    }
}