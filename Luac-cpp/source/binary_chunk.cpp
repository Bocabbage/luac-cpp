#include "binary_chunk.hpp"
#include "reader.hpp"
using namespace luaccpp;

Prototype 
luaccpp::Undump(BYTE_ARRAY data)
{
	auto reader = std::make_unique<Reader>(data);
	bool check_header_success = reader->CheckHeader();
	if (!check_header_success)
		return Prototype();
	reader->ReadByte();			// Ignore the Upvalue-num
	return reader->ReadProto("");
}
