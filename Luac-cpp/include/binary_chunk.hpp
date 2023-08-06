#pragma once
#ifndef BINARY_CHUNK
#define BINARY_CHUNK

// #pragma pack(1)
#include <cstdint>
#include "types.hpp"

namespace luaccpp
{
	// Header constants
	const char LUA_SIGNATURE[] = { 0x1B, 0x4C, 0x75, 0x61 };
	const uint8_t LUAC_VERSION = 0x53;
	const uint8_t LUAC_FORMAT = 0x0;
	const uint8_t LUAC_DATA[] = { 0x19, 0x93, 0x0D, 0x0A, 0x1A, 0x0A };
	const uint8_t CINT_SIZE = 0x4;
	const uint8_t CSIZET_SIZE = 0x8;
	const uint8_t INSTRUCTION_SIZE = 0x4;
	const uint8_t LUA_INTEGER_SIZE = 0x8;
	const uint8_t LUA_NUMBER_SIZE = 0x8;
	const uint64_t LUAC_INT = 0x5678;
	const double LUAC_NUM = 370.5;

	// Tag constants
	const uint8_t TAG_NIL = 0x00;
	const uint8_t TAG_BOOLEAN = 0x01;
	const uint8_t TAG_NUMBER = 0x03;
	const uint8_t TAG_INTEGER = 0x13;
	const uint8_t TAG_SHORT_STR = 0x04;
	const uint8_t TAG_LONG_STR = 0x14;


	struct Header
	{
		// Meta data
		uint32_t signature;
		uint8_t version;
		uint8_t format;

		// 6-bytes luacData field
		uint32_t luacData_0;
		uint16_t luacData_1;

		// Lua type size
		uint8_t cintSize;
		uint8_t sizetSize;
		uint8_t instructionSize;
		uint8_t luaIntegerSize;
		uint8_t luaNumberSize;

		// Small/Big-endian tag
		int64_t luacInt;
		double luacNum;
	};

	struct Constant {
		uint8_t Tag;
		ANY Const;
	};

	using Constant_ARRAY = std::vector<Constant>;

	struct Upvalue
	{
		uint8_t Instack;
		uint8_t Idx;
	};

	using Upvalue_ARRAY = std::vector<Upvalue>;

	struct LocVar
	{
		STRING VarName;
		uint32_t StartPC;
		uint32_t EndPC;
	};

	using LocVar_ARRAY = std::vector<LocVar>;

	// Lua function struct
	struct Prototype
	{
		STRING Source;				// Source file name

		uint32_t LineDefined;		// Func start line number
		uint32_t LastLineDefined;	// Func end line number

		uint8_t NumParams;
		uint8_t IsVararg;
		uint32_t MaxStackSize;

		UWORD32_ARRAY Code;						// Instruction table
		Constant_ARRAY Constants;				// Constant table 
		Upvalue_ARRAY Upvalues;
		std::vector<Prototype> Protos;			// Sub-func table

		WORD32_ARRAY LineInfo;					// Line number table
		LocVar_ARRAY LocVars;					// Local variable table
		STRING_ARRAY UpvalueNames;
	};

	using Prototype_ARRAY = std::vector<Prototype>;

	struct BinaryChunk
	{
		Header Header;
		uint8_t SizeUpvalues;
		Prototype MainFunc;
	};

	Prototype Undump(BYTE_ARRAY data);
}

#endif