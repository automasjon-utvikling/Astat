#include "atpch.h"

#include "ConfigUtils.h"

#include "Astat/Logging/Logger.h"
#include "Astat/Utils/FileUtils.h"

Astat::Utils::Config::Config ()
{

}

void Astat::Utils::Config::Assign (std::string a_path)
{
	Astat::Utils::File file;
	file.Assign (a_path);
	std::string file_content;
	if (file.Read (file_content) == Astat::EError::NO_ERROR)
	{
		std::istringstream iss(file_content);
		std::vector<std::string> pairs;
		for (std::string line; std::getline(iss, line);)
		{
			pairs.push_back (line);
		}
		for (std::string pair : pairs)
		{
			std::string delimiter = " = ";

			size_t pos = 0;
			if ((pos = pair.find (delimiter)) != std::string::npos)
			{
				std::string key = pair.substr (0, pos);
				pair.erase (0, pos + delimiter.length ());
				std::string value = pair;
				m_map[key] = value;
			}

		}
	}
	else
	{
		Astat::Logger::sLog ("Valid config file not found!");
	}
}

const char *Astat::Utils::Config::GetCSTRValue (std::string a_key)
{
	return m_map.at(a_key).c_str();
}

int Astat::Utils::Config::GetIValue (std::string a_key)
{
	return std::stoi (m_map.at (a_key));
}

Astat::Utils::Config &Astat::Utils::Config::GetConfig ()
{
	static Config s_instance;
	return s_instance;
}

