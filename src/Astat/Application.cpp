#include "atpch.h"

#include "Astat/Astat.h"
#include "Astat/Logging/Logger.h"
#include "Astat/Utils/ConfigUtils.h"

#include "Astat/Networking/HTTP/HttpServer.h"

int main( )
{
    Astat::Utils::Config& config = Astat::Utils::Config::GetConfig();
    config.Assign ("./config.config");

    std::cout << "Starting" << std::endl;
    Astat::Networking::Http::HttpServer httpServer (Astat::Utils::Config::GetConfig().GetCSTRValue("BindAddress"), (short)Astat::Utils::Config::GetConfig ().GetIValue ("BindPort"));
    if(httpServer.init() != 0)
        return -1;
    std::thread httpServerThread(&Astat::Networking::Http::HttpServer::run, &httpServer);
    std::cout << "Started!" << std::endl;
    httpServerThread.join();
    std::cout << "Exiting!" << std::endl;
    return 0;
}