#pragma once
#ifndef TYPES
#define TYPES
#include <vector>
#include <string>
#include <cstdint>
#include <any>

namespace luaccpp
{
	using BYTE_ARRAY = std::vector<uint8_t>;
	using UWORD32_ARRAY = std::vector<uint32_t>;
	using WORD32_ARRAY = std::vector<int32_t>;
	using STRING = std::string;
	using STRING_ARRAY = std::vector<STRING>;

	// C++17
	using ANY = std::any;
	using ANY_ARRAY = std::vector<ANY>;
}

#endif // !TYPES
