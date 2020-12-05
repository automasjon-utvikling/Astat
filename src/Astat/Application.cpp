#include "atpch.h"
#include "config.h"

#include "Astat/Astat.h"
#include "Astat/Logging/Logger.h"

#include "Astat/Networking/HTTP/HttpServer.h"

int main( )
{
    std::cout << "Started! 123" << std::endl;
    Astat::Networking::Http::HttpServer httpServer(AT_CONFIG_SERVER_IP_ADDRESS, AT_CONFIG_SERVER_HTTP_PORT);
    if(httpServer.init() != 0)
        return -1;
    std::thread httpServerThread(&Astat::Networking::Http::HttpServer::run, &httpServer);
    std::cout << "Ready to join" << std::endl;
    httpServerThread.join();
    std::cout << "Joined" << std::endl;
    return 0;
}