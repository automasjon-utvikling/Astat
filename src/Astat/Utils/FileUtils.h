#pragma once

#include "Astat/Astat.h"

/*
 * File file;
 * file.Assign("docs/component.htm");
 * std::string file_content = file.Read();
 */

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
			};

		public:
			File ();

			EError Assign (const std::string& a_path, const EFileMode a_mode = EFileMode::TEXT);
			EError Read (std::string& o_content);

		private:
			std::string m_path = "";
			EFileMode m_mode = EFileMode::TEXT;
		};
	}
}