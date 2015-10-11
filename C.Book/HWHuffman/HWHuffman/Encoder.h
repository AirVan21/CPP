#pragma once

#include <string>
#include <vector>

#include "Symbol.h"
#include "TreeNode.h"

const unsigned int ALPHABET_SIZE = 256;

class Encoder
{
public:

	Encoder();
	virtual ~Encoder();

	void encode(const std::string &input_filename, const std::string &output_filename);

private:
	
	void count_input_frequency(const std::string &input_filename);
	void create_translation_tree();

	std::vector<symbol> alphabet_;
	unsigned int file_length_in_symbols_;
};
