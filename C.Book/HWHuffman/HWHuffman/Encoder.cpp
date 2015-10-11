#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <queue>

#include "Encoder.h"

Encoder::Encoder()
	: alphabet_(std::vector<symbol>(ALPHABET_SIZE))
{
	for (unsigned int i = 0; i < ALPHABET_SIZE; ++i)
	{ 
		alphabet_[i] = {static_cast<unsigned char>(i), 0};
	}
}

Encoder::~Encoder()
{
}

void Encoder::encode(const std::string &input_filename, const std::string &output_filename)
{
	count_input_frequency(input_filename);
}

void Encoder::count_input_frequency(const std::string &input_filename)
{
	std::ifstream file_in(input_filename, std::ios::binary);

	const unsigned int size_of_uchar = sizeof(unsigned char);
	unsigned char accumulator = 0;
	while (file_in.read(reinterpret_cast<char*>(&accumulator), size_of_uchar))
	{
		alphabet_[accumulator].frequnecy++;
		file_length_in_symbols_++;
	}
}

void Encoder::create_translation_tree()
{
	using namespace std;
	
	priority_queue<tree_node, vector<tree_node>, compare_tree_node> p_queue;
	for (symbol &record : alphabet_)
	{
		p_queue.push({numeric_limits<unsigned int>::max(), numeric_limits<unsigned int>::max(), record});
	}

	while (p_queue.size() > 1)
	{
		p_queue.pop();
	}
}

