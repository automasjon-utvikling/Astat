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