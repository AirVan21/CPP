#include <iostream>
#include <fstream>

#include "Parser.h"
#include "Encoder.h"

int main(unsigned int argc, char const *argv[])
{
	using namespace std;

	parser key_parser(argc, argv);
	task current_task = key_parser.retrive_task();
	
	switch (current_task)
	{
		case task::archive :
		{
			Encoder huffman_encoder = Encoder();
			huffman_encoder.encode(key_parser.get_input_filename(), key_parser.get_output_filename());
			break;
		}
		case task::extract :
		{
			Encoder huffman_encoder = Encoder();
			huffman_encoder.decode(key_parser.get_input_filename(), key_parser.get_output_filename());
			break;
		}
		case task::signal_fail :
		{
			break;
		}
		case task::undefined :
		{
			break;
		}
		default:
			break;
	}

	return 0;
}