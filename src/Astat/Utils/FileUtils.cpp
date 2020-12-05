#include "atpch.h"

#include "FileUtils.h"

#include "Astat/Logging/Logger.h"

Astat::Utils::File::File ()
{

}

Astat::EError Astat::Utils::File::Assign (const std::string& a_path, const EFileMode a_mode)
{
	m_path = a_path;
	m_mode = a_mode;
	return EError::NO_ERROR;
}

Astat::EError Astat::Utils::File::Read (std::string& o_content)
{
	Astat::Logger::Logger::sLog (m_path);
	std::ifstream stream;

	switch (m_mode)
	{
		case Astat::Utils::File::EFileMode::TEXT:
			stream = std::ifstream (m_path);
			break;
		case Astat::Utils::File::EFileMode::BINARY:
			stream = std::ifstream (m_path, std::ios::binary);
			break;
		default:
			return EError::INVALID_STATE;
	}

	if (!stream.good ())
	{
		return EError::FILE_NOT_GOOD;
	}

	std::string data ((std::istreambuf_iterator<char> (stream)), std::istreambuf_iterator<char> ());
	o_content = data;

	stream.close ();
	return EError::NO_ERROR;
}
