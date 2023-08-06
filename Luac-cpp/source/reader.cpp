#include "Reader.hpp"
#include <cstring>
using namespace luaccpp;


// Read a byte from the data_ stream
uint8_t 
Reader::ReadByte()
{
	uint8_t res = data_[0];
	data_.erase(data_.begin());
	return res;
}

// Read a uint64 var from the data_ stream
uint32_t
Reader::ReadUint32()
{
	uint32_t res = 0;
	// Small-endian Read
	for (int8_t i = 3; i >= 0; --i)
		res = (res << 8) | data_[i];
	
	data_.erase(data_.begin(), data_.begin() + 4);
	return res;
}

// Read a uint64 var from the data_ stream
uint64_t
Reader::ReadUint64()
{
	uint64_t res = 0;
	// LittleEndian Read
	for (int8_t i = 7; i >= 0; --i)
		res = (res << 8) | data_[i];

	data_.erase(data_.begin(), data_.begin() + 8);
	return res;
}

// Read a luaint var (int64) from the data_ stream
int64_t
Reader::ReadLuaInteger()
{
	int64_t res = 0;
	// LittleEndian Read
	for (int8_t i = 7; i >= 0; --i)
		res = (res << 8) | data_[i];

	data_.erase(data_.begin(), data_.begin() + 8);
	return res;
}

// Read a luanumber var (float64) from the data_ stream
double
Reader::ReadLuaNumber()
{
	double res = 0;
	// Extract double-byte-data_ from the data_ stream
	BYTE_ARRAY res_data(data_.begin(), data_.begin() + 8);
	// std::reverse(res_data->begin(), res_data->end());
	std::memcpy(&res, res_data.data(), sizeof(res));
	data_.erase(data_.begin(), data_.begin() + 8);
	return res;
}

// Read a string var from the data_ stream
STRING
Reader::ReadString()
{
	auto size = ReadByte();
	if (size == 0)
		return "";
	if (size == 0xff)
		// Long-string
		size = ReadUint64();
	
	size--;
	STRING res(data_.begin(), data_.begin() + size);
	data_.erase(data_.begin(), data_.begin() + size);
	return res;
}

// Read bytes from the data_ stream
BYTE_ARRAY 
Reader::ReadBytes(unsigned int n)
{
	// +Todo: check if there are enough bytes
	BYTE_ARRAY res(data_.begin(), data_.begin() + n);
	data_.erase(data_.begin(), data_.begin() + n);
	return res;
}

bool
Reader::CheckHeader()
{
	// Read signature
	auto sign = ReadBytes(4);
	for (size_t i = 0; i < 4; ++i)
	{
		if (sign[i] != LUA_SIGNATURE[i])
			return false;
	}
	// Read version
	if (ReadByte() != LUAC_VERSION)
		return false;
	// Read format
	if (ReadByte() != LUAC_FORMAT)
		return false;
	// Read data
	auto luac_data = ReadBytes(6);
	for (size_t i = 0; i < 6; ++i)
	{
		if (luac_data[i] != LUAC_DATA[i])
			return false;
	}
	// Read sizes
	if (ReadByte() != CINT_SIZE)
		return false;
	if (ReadByte() != CSIZET_SIZE)
		return false;
	if (ReadByte() != INSTRUCTION_SIZE)
		return false;
	if (ReadByte() != LUA_INTEGER_SIZE)
		return false;
	if (ReadByte() != LUA_NUMBER_SIZE)
		return false;
	if (ReadLuaInteger() != LUAC_INT)
		return false;
	if (ReadLuaNumber() != LUAC_NUM)
		return false;

	return true;
}

Prototype 
Reader::ReadProto(STRING parent_source)
{
	auto source = ReadString();
	if (source.empty())
		source = parent_source;
	Prototype res;
	res.LineDefined = ReadUint32();
	res.LastLineDefined = ReadUint32();
	res.NumParams = ReadByte();
	res.IsVararg = ReadByte();
	res.MaxStackSize = ReadByte();
	res.Code = ReadCode();
	res.Constants = ReadConstants();
	res.Upvalues = ReadUpValues();

	res.Protos = ReadProtos(source);

	res.LineInfo = ReadLineInfo();
	res.LocVars = ReadLocVars();
	res.UpvalueNames = ReadUpvalueNames();

	return res;
}

Prototype_ARRAY 
Reader::ReadProtos(STRING parent_source)
{
	Prototype_ARRAY res;
	auto pro_num = ReadUint32();
	for (size_t i = 0; i < pro_num; ++i)
		// Todo: Check move or copy
		res.push_back(ReadProto(parent_source));
	return res;
}

Constant
Reader::ReadConstant()
{
	Constant res;
	res.Tag = ReadByte();
	switch (res.Tag)
	{
	case TAG_BOOLEAN:
		res.Const = (ReadByte() == 1); break;
	case TAG_INTEGER:
		res.Const = ReadLuaInteger(); break;
	case TAG_SHORT_STR:
	case TAG_LONG_STR:
		res.Const = ReadString(); break;
	case TAG_NIL:
	default:
		res.Const = nullptr;
	}
	return res;
}

Constant_ARRAY
Reader::ReadConstants()
{
	std::vector<Constant> res;
	auto const_num = ReadUint32();
	for (size_t i = 0; i < const_num; ++i)
	{
		Constant const_val = ReadConstant();
		res.push_back(const_val);
	}
	return res;
}

UWORD32_ARRAY 
Reader::ReadCode()
{
	UWORD32_ARRAY res;
	auto code_num = ReadUint32();
	for (size_t i = 0; i < code_num; ++i)
		res.push_back(ReadUint32());

	return res;
}

Upvalue_ARRAY
Reader::ReadUpValues()
{
	std::vector<Upvalue> res;
	auto upvalue_num = ReadUint32();
	for (size_t i = 0; i < upvalue_num; ++i)
	{
		Upvalue upv;
		upv.Idx = ReadByte();
		upv.Instack = ReadByte();
		res.push_back(upv);
	}

	return res;
}

WORD32_ARRAY 
Reader::ReadLineInfo()
{
	WORD32_ARRAY res;
	auto line_num = ReadUint32();
	for (size_t i = 0; i < line_num; ++i)
		res.push_back(ReadUint32());
	return res;
}

LocVar_ARRAY
Reader::ReadLocVars()
{
	std::vector<LocVar> res;
	auto loc_var_num = ReadUint32();
	for (size_t i = 0; i < loc_var_num; ++i)
	{
		LocVar* loc_var = new LocVar;
		// Todo: Check move or copy
		loc_var->VarName = std::move(ReadString());
		loc_var->StartPC = ReadUint32();
		loc_var->EndPC = ReadUint32();
		// Todo: Check move or copy
		res.emplace_back(std::move(*loc_var));
	}

	return res;
}

STRING_ARRAY 
Reader::ReadUpvalueNames()
{
	STRING_ARRAY res;
	auto name_num = ReadUint32();
	for (size_t i = 0; i < name_num; ++i)
		// res.emplace_back(std::move(ReadString()));
		// Todo: Check move or copy
		res.emplace_back(ReadString());
	return res;
}
