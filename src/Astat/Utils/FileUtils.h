#pragma once

#include "Astat/Astat.h"

namespace Astat
{
	namespace Utils
	{
		class File
		{
		public:
			enum class EFileMode
			{
				TEXT,
				BINARY,
			}; // enum class EFileMode

		public:
			File ();

			EError Assign (const std::string& a_path, const EFileMode a_mode = EFileMode::TEXT);
			EError Read (std::string& o_content);

		private:
			std::string m_path = "";
			EFileMode m_mode = EFileMode::TEXT;

		}; // class File
	} // namespace Utils
} // namespace Astat