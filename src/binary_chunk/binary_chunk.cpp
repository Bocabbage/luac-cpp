#include "binary_chunk.hpp"
#include "reader.hpp"
using namespace luac;

Prototype 
luac::Undump(const BYTE_ARRAY& data)
{
	const auto reader = std::make_unique<Reader>(data);
	if (const bool check_header_success = reader->CheckHeader(); !check_header_success)
		return {};
	reader->ReadByte();			// Ignore the UpValue-num
	return reader->ReadProto("");
}
