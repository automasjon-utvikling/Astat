#pragma once
#include "atpch.h"
#include "Astat/Astat.h"

#include "Astat/Networking/TCP/TcpListner.h"

namespace Astat
{
    namespace Networking
    {
        namespace Http
        {
            class HttpServer : public Astat::Networking::Tcp::TcpListner
            {
            public:
                HttpServer(const char* aIpAddress, u_short aPort)
                    :TcpListner(aIpAddress, aPort)
                {
                }

            protected:
                virtual void onClientConnect(SOCKET aClientSocketId);
                virtual void onClientDisconnect(SOCKET aClientSocketId);
                virtual void onClientMessage(SOCKET aClientSocketId, const char* aMessage);
            };

            struct HttpFileType {
                std::string suffix;
                std::string type;
                std::string group;

                HttpFileType(std::string a_suffix, std::string a_type, std::string a_group)
                    :suffix(a_suffix), type(a_type), group(a_group)
                {

                }
            };
        }
    }
}

