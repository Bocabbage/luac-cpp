#pragma once
#ifndef BINARY_CHUNK
#define BINARY_CHUNK

// #pragma pack(1)
#include <cstdint>
#include "types.hpp"
#include "prototype.hpp"

namespace luac {
	// Header constants
	constexpr char LUA_SIGNATURE[] = { 0x1B, 0x4C, 0x75, 0x61 };
	constexpr uint8_t LUAC_VERSION = 0x53;	// fixed to 5.3
	constexpr uint8_t LUAC_FORMAT = 0x0;
	constexpr uint8_t LUAC_DATA[] = { 0x19, 0x93, 0x0D, 0x0A, 0x1A, 0x0A };
	constexpr uint8_t CINT_SIZE = 0x4;
	constexpr uint8_t CSIZET_SIZE = 0x8;
	constexpr uint8_t INSTRUCTION_SIZE = 0x4;
	constexpr uint8_t LUA_INTEGER_SIZE = 0x8;
	constexpr uint8_t LUA_NUMBER_SIZE = 0x8;
	constexpr uint64_t LUAC_INT = 0x5678;		// for big/small-end checking
	constexpr double LUAC_NUM = 370.5;			// for float format checking (IEEE 754)

	struct Header
	{
		// Meta data
		uint32_t signature; // magic number
		uint8_t version;	// version
		uint8_t format;		// chunk format version number

		// 6-bytes luac data field
		uint32_t luac_data_0;
		uint16_t luac_data_1;

		// Lua type size
		uint8_t cint_size;
		uint8_t sizet_size;
		uint8_t instruction_size;
		uint8_t lua_integer_size;
		uint8_t lua_number_size;

		// Small/Big-endian tag
		int64_t luac_int;
		double luac_num;
	};

	struct BinaryChunk
	{
		Header header;
		uint8_t size_upvalues;
		Prototype main_func;
	};

	// Read a binary-chunk and load as a Prototype instance
	Prototype Undump(const BYTE_ARRAY& data);
}

#endif