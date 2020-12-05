#pragma once

#include "Astat/Astat.h"

namespace Astat
{
	namespace Utils
	{
		class Config
		{
		public:
			void Assign (std::string a_path);

			const char* GetCSTRValue (std::string a_key);
			int GetIValue (std::string a_key);

			static Config &GetConfig ();

		private:
			Config ();

		public:
			Config (Config const &) = delete;
			void operator=(Config const &) = delete;

		private:
			std::unordered_map<std::string, std::string> m_map;

			static Config *m_instance;
		};
	}
}