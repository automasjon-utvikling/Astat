#include "atpch.h"
#include "Logger.h"

Astat::Logger::Logger( )
{
    m_Name = "TBN";
}

Astat::Logger::Logger(std::string aName)
{
    m_Name = aName;
}

void Astat::Logger::Log(std::string aStr)
{
    std::cout << "["<< m_Name << "]: " << aStr << std::endl;
}

void Astat::Logger::sLog(std::string aStr)
{
    std::cout << "[---]: " << aStr << std::endl;
}
