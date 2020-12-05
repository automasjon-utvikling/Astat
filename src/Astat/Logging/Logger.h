#pragma once

#include "Astat/Astat.h"

namespace Astat
{
    class Logger
    {
    public:
        Logger();
        Logger(std::string aName);

    public:
        void Log(std::string aStr);
        static void sLog(std::string aStr);

    private:
        std::string m_Name;

    }; // class Logger
} // namespace Astat

