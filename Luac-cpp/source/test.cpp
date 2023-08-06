#include "test.hpp"
#include <iostream>
using std::cout;
using std::endl;

bool luaccpp::TestReader::TestMain()
{
	/* Reader-class UT */
	// ReadByte
	if (TestReadByte())
		cout << "ReadByte UT success!" << endl;
	else
	{
		cout << "ReadByte UT failed!" << endl;
		return false;
	}
	// ReadBytes
	if (TestReadBytes())
		cout << "ReadBytes UT success!" << endl;
	else
	{
		cout << "ReadBytes UT failed!" << endl;
		return false;
	}
	// ReadUint32
	if (TestReadUint32())
		cout << "ReadUint32 UT success!" << endl;
	else
	{
		cout << "ReadUint32 UT failed" << endl;
		return false;
	}
	// ReadUint64
	if (TestReadUint64())
		cout << "ReadUint64 UT success!" << endl;
	else
	{
		cout << "ReadUint64 UT failed" << endl;
		return false;
	}
	// ReadLuaNumber
	if (TestReadLuaInteger())
		cout << "ReadLuaInteger UT success!" << endl;
	else
	{
		cout << "ReadLuaInteger UT failed" << endl;
		return false;
	}

	return true;
}
