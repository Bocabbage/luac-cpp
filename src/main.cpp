#include <iostream>
#include <fstream>
#include "binary_chunk/reader.hpp"
#include "binary_chunk/types.hpp"
#include "binary_chunk/binary_chunk_test.hpp"

using namespace std;

/**
 * 	todo 临时 demo，后续需移除
 */
int main()
{
	/* Reader-class UT */
	luaccpp::TestReader::TestMain();

	/* Read .lua file */
    // todo
	const std::string input_file = "../resource/hello_world_withvar.luac";
	ifstream infile(input_file, ios_base::binary);

	infile.seekg(0, std::ios_base::end);
	// size_t length = infile.tellg();
	infile.seekg(0, std::ios_base::beg);

	luaccpp::BYTE_ARRAY buffer(
		(istreambuf_iterator<char>(infile)), // The() is necessary here
		istreambuf_iterator<char>());
	auto prof = luaccpp::Undump(buffer);
	cout << "for breakpoint" << endl;

}