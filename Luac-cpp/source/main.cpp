#include <iostream>
#include <fstream>
#include <algorithm>
#include "reader.hpp"
#include "types.hpp"
#include "test.hpp"

using namespace std;

int main()
{
	/* Reader-class UT */
	luaccpp::TestReader tr;
	tr.TestMain();

	/* Read .lua file */
	const std::string input_file = "C:/Users/37806/OneDrive/codes/Luac-cpp/Luac-cpp/resource/luac.5.3.4.out";
	ifstream infile(input_file, ios_base::binary);

	infile.seekg(0, std::ios_base::end);
	size_t length = infile.tellg();
	infile.seekg(0, std::ios_base::beg);

	luaccpp::BYTE_ARRAY buffer(
		(istreambuf_iterator<char>(infile)), // The() is necessary here
		istreambuf_iterator<char>());
	auto prof = luaccpp::Undump(buffer);
	cout << "for breakpoint" << endl;

}