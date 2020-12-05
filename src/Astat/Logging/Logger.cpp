#include "atpch.h"

#include "Logger.h"

Astat::Logger::Logger( )
{
    m_Name = "TBN";
} // Logger

Astat::Logger::Logger(std::string aName)
{
    m_Name = aName;
} // Logger()

void Astat::Logger::Log(std::string aStr)
{
    std::cout << "["<< m_Name << "]: " << aStr << std::endl;
} // Log()

void Astat::Logger::sLog(std::string aStr)
{
    std::cout << "[---]: " << aStr << std::endl;
} // sLog()
