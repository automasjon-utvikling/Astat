#pragma once

#include "atpch.h"

#define AT_PLATFORM_WINDOWS

namespace Astat
{
	enum class EError
	{
		// General
		NO_ERROR,
		INVALID_STATE,

		// File reading
		FILE_NOT_GOOD,
	}; // enum class EError
} // namespace Astat

#pragma pack(push, 1)
struct uint24_t
{
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
};
#pragma pack(pop)