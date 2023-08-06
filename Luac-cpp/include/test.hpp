#pragma once
#ifndef TEST

#include "reader.hpp"

namespace luaccpp
{
	class TestReader
	{
	public:
		bool TestReadByte()
		{
			/* Case-1: normal START */
			BYTE_ARRAY test_data = { 'h','e','l','l','o' };
			
			auto reader = std::make_unique<Reader>(test_data);

			if (reader->ReadByte() != 'h')
				return false;
			if (reader->ReadByte() != 'e')
				return false;
			if (reader->ReadByte() != 'l')
				return false;
			if (reader->ReadByte() != 'l')
				return false;
			if (reader->ReadByte() != 'o')
				return false;

			return reader->eof();
			/* Case-1: normal END */

		}

		bool TestReadBytes()
		{
			/* Case-1: normal START */
			BYTE_ARRAY test_data = { 'h','e','l','l','o' };
			BYTE_ARRAY test_data_cp = test_data;
			auto reader = std::make_unique<Reader>(test_data);
			auto res = reader->ReadBytes(5);
			for (size_t i = 0; i < 5; ++i)
				if (res[i] != test_data_cp[i])
					return false;
			return reader->eof();
			/* Case-1: normal END */
		}

		bool TestReadUint32()
		{
			/* Case-1: normal START */
			BYTE_ARRAY test_data = { 0x1,0x1,0x1,0x1,0x3,0x3,0x3,0x3 };

			auto reader = std::make_unique<Reader>(test_data);
			auto res = reader->ReadUint32();
			if (res != 16843009)
				return false;
			res = reader->ReadUint32();
			if (res != 50529027)
				return false;


			return reader->eof();
			/* Case-1: normal END */
		}

		bool TestReadUint64()
		{
			/* Case-1: normal START */
			BYTE_ARRAY test_data = { 0x1,0x1,0x1,0x1,0x3,0x3,0x3,0x3 };

			auto reader = std::make_unique<Reader>(test_data);
			auto res = reader->ReadUint64();
			if (res != 217020518480544001)
				return false;

			return reader->eof();
			/* Case-1: normal END */
		}

		bool TestReadLuaInteger()
		{
			/* Case-1: normal START */
			BYTE_ARRAY test_data = { 0x1,0x1,0x1,0x1,0x3,0x3,0x3,0x3 };

			auto reader = std::make_unique<Reader>(test_data);
			auto res = reader->ReadLuaInteger();
			if (res != 217020518480544001)
				return false;

			return reader->eof();
			/* Case-1: normal END */
		}

		bool TestMain();
	};
}

#endif // !TEST


