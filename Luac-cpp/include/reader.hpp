#pragma once
#ifndef READER 
#define READER
#include <cstdint>
#include <memory>
#include <vector>
#include "types.hpp"
#include "binary_chunk.hpp"

namespace luaccpp
{
	class Reader
	{
		BYTE_ARRAY data_;

	public:
		Reader(BYTE_ARRAY rdata): data_(rdata) {  }

		// Utils
		bool eof() { return data_.empty(); }

		uint8_t ReadByte();
		uint32_t ReadUint32();
		uint64_t ReadUint64();
		int64_t ReadLuaInteger();
		double ReadLuaNumber();
		STRING ReadString();
		BYTE_ARRAY ReadBytes(unsigned int n);

		// Read Header
		bool CheckHeader();

		// Read Body
		Prototype ReadProto(STRING parent_source);
		Prototype_ARRAY ReadProtos(STRING parent_source);
		Constant ReadConstant();
		Constant_ARRAY ReadConstants();
		UWORD32_ARRAY ReadCode();
		Upvalue_ARRAY ReadUpValues();
		WORD32_ARRAY ReadLineInfo();
		LocVar_ARRAY ReadLocVars();
		STRING_ARRAY ReadUpvalueNames();

	};
}

#endif
