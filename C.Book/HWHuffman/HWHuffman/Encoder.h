#pragma once

#include <string>
#include <vector>

#include "Symbol.h"
#include "TreeNode.h"

const uint32_t ALPHABET_SIZE = 256;
const uint32_t BITS_IN_BYTE = 8;

class Encoder
{
public:

	Encoder();
	virtual ~Encoder();

	void encode(const std::string &input_filename, const std::string &output_filename);
	void decode(const std::string &input_filename, const std::string &output_filename);

private:
	
	void count_input_frequency(const std::string &input_filename);
	void create_translation_tree();
	void create_code_table();
	bool is_leaf(const tree_node &) const;
	void generate_code(unsigned int sub_tree, unsigned char letter, std::vector<bool> code_seq, unsigned int code_place);
	void write_output_coded_file(const std::string &input_filename, const std::string &output_filename);
	void write_byte(const std::vector<bool> &bits, std::ofstream &file_out, bool last_byte) const;

	void read_input_file(const std::string &input_filename);
	std::vector<bool> *convert_binary_data();
	void write_output_decoded_file(const std::string &output_filename, const std::vector<bool> &bit_data);
	void find_letter_by_code(unsigned int sub_tree, unsigned char &letter, const std::vector<bool> &code_seq, unsigned long long &decision_index) const;

	unsigned long long file_length_in_symbols_;
	unsigned int root_node_index_;
	std::vector<symbol> alphabet_;
	std::vector<std::vector<bool>> alpabet_codes_;
	std::vector<tree_node> coding_tree_;

	std::vector<uint8_t> *coded_input_;
};
