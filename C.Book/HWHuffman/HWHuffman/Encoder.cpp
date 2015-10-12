#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <iterator>

#include "Encoder.h"
// Delete 
#include <iostream>

Encoder::Encoder()
	: alphabet_(std::vector<symbol>(ALPHABET_SIZE))
	, alpabet_codes_(std::vector<std::vector<bool>>(ALPHABET_SIZE))
{
	for (unsigned int i = 0; i < ALPHABET_SIZE; ++i)
	{ 
		alphabet_[i] = {static_cast<unsigned char>(i), 0};
	}
}

Encoder::~Encoder()
{
	delete coded_input_;
}

void Encoder::encode(const std::string &input_filename, const std::string &output_filename)
{
	count_input_frequency(input_filename);
	create_translation_tree();
	create_code_table();
	write_output_coded_file(input_filename, output_filename);
}

void Encoder::decode(const std::string &input_filename, const std::string &output_filename)
{
	using std::vector;

	read_input_file(input_filename);
	vector<bool> *data_in_bit_representation = convert_binary_data();
	write_output_decoded_file(output_filename, *data_in_bit_representation);

	delete data_in_bit_representation;
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

	unsigned int index = 0;
	while (p_queue.size() > 1)
	{
		tree_node test = p_queue.top();
		coding_tree_.push_back(p_queue.top());
		unsigned int fst_frequency = coding_tree_[index].character.frequnecy;
		p_queue.pop();
		index++;

		coding_tree_.push_back(p_queue.top());
		unsigned int snd_frequency = coding_tree_[index].character.frequnecy;
		p_queue.pop();
		index++;
		
		symbol link_symbol = { '+',  fst_frequency + snd_frequency };
		tree_node union_node = { index - 2, index - 1, link_symbol };
		p_queue.push(union_node);
	}

	tree_node root_node = p_queue.top();
	coding_tree_.push_back(root_node);
	root_node_index_ = index;
	p_queue.pop();
}

void Encoder::create_code_table()
{
	using namespace std;

	for (unsigned int i = 0; i < ALPHABET_SIZE; ++i)
	{
		vector<bool> symbol_code;
		generate_code(root_node_index_, alphabet_[i].letter, symbol_code, i);
	}
}

void Encoder::generate_code(unsigned int sub_tree, unsigned char letter, std::vector<bool> code_seq, unsigned int code_place)
{
	if (is_leaf(coding_tree_[sub_tree]))
	{
		if (coding_tree_[sub_tree].character.letter == letter)
		{
			alpabet_codes_[code_place] = code_seq;
		}
	}
	else
	{
		std::vector<bool> left_code_seq = code_seq;
		left_code_seq.push_back(false);
		generate_code(coding_tree_[sub_tree].left_child, letter, left_code_seq, code_place);

		std::vector<bool> right_code_seq = code_seq;
		right_code_seq.push_back(true);
		generate_code(coding_tree_[sub_tree].right_child, letter, right_code_seq, code_place);
	}
}

bool Encoder::is_leaf(const tree_node &node) const
{
	return (node.left_child == std::numeric_limits<unsigned int>::max()) && (node.left_child == std::numeric_limits<unsigned int>::max());
}

void Encoder::write_output_coded_file(const std::string &input_filename, const std::string &output_filename)
{
	using namespace std;
	
	ofstream file_out(output_filename, ios::binary);
	
	const uint32_t coding_tree_size = coding_tree_.size();
	file_out.write(reinterpret_cast<const char*>(&coding_tree_size), sizeof(coding_tree_size));

	const unsigned int size_of_node = sizeof(tree_node);
	for (tree_node &node : coding_tree_)
	{
		file_out.write(reinterpret_cast<char*>(&node), size_of_node);
	}
	
	file_out.write(reinterpret_cast<char*>(&file_length_in_symbols_), sizeof(file_length_in_symbols_));
	file_out.write(reinterpret_cast<char*>(&root_node_index_),        sizeof(root_node_index_));
	
	ifstream file_in(input_filename, std::ios::binary);
	const unsigned int size_of_uchar = sizeof(unsigned char);
	unsigned char accumulator = 0;
	while (file_in.read(reinterpret_cast<char*>(&accumulator), size_of_uchar))
	{
		write_byte(alpabet_codes_[accumulator], file_out, false);
	}
	// Push last byte with extra zeros
	write_byte(alpabet_codes_[accumulator], file_out, true);
}

void Encoder::write_byte(const std::vector<bool>& bits, std::ofstream &file_out, bool last_byte) const
{
	static uint8_t buffer  = 0;
	static uint8_t counter = 0;
	
	if (last_byte)
	{
		file_out.write(reinterpret_cast<char*>(&buffer), sizeof(uint8_t));
		return;
	}

	for (bool bit : bits)
	{
		if (counter < BITS_IN_BYTE)
		{
			if (bit)
			{
				buffer |= 1 << (BITS_IN_BYTE - counter - 1);
			}
			counter++;
		}
		else
		{
			file_out.write(reinterpret_cast<char*>(&buffer), sizeof(uint8_t));
			buffer  = 0;
			counter = 0;
			if (bit)
			{
				buffer |= 1 << (BITS_IN_BYTE - counter - 1);
			}
			counter++;
		}
	}
}

void Encoder::read_input_file(const std::string &input_filename)
{
	using namespace std;
	
	std::ifstream file_in(input_filename, std::ios::binary);
	uint32_t size_of_coding_tree = 0;
	file_in.read(reinterpret_cast<char*>(&size_of_coding_tree), sizeof(size_of_coding_tree));

	symbol empty_symbol = { '+', 0 };
	tree_node recipient = { 0, 0, empty_symbol };
	const unsigned int size_of_node = sizeof(tree_node);
	for (unsigned int i = 0; i < size_of_coding_tree; i++)
	{
		file_in.read(reinterpret_cast<char*>(&recipient), size_of_node);
		coding_tree_.push_back(recipient);
	}

	file_in.read(reinterpret_cast<char*>(&file_length_in_symbols_), sizeof(file_length_in_symbols_));
	file_in.read(reinterpret_cast<char*>(&root_node_index_),        sizeof(root_node_index_));

	uint8_t code_recipient = 0;
	const uint8_t size_of_code_reciepient = sizeof(code_recipient);
	
	// Memory allocation (should be deleted in desctructor)
	coded_input_ = new vector<uint8_t>;
	while (file_in.read(reinterpret_cast<char*>(&code_recipient), size_of_code_reciepient))
	{
		coded_input_->push_back(code_recipient);
	}
}

std::vector<bool>* Encoder::convert_binary_data()
{
	using namespace std;
	
	vector<bool> *bit_data = new vector<bool>;
	for (uint8_t binary_byte : *coded_input_)
	{
		for (unsigned int i = 0; i < BITS_IN_BYTE; ++i)
		{
			bool last_bit = binary_byte & (1 << (BITS_IN_BYTE - i - 1));
			bit_data->push_back(last_bit);
		}
	}

	return bit_data;
}

void Encoder::write_output_decoded_file(const std::string &output_filename, const std::vector<bool> &bit_data)
{
	using namespace std;

	//ofstream file_out(output_filename);
	unsigned long long search_iterations = file_length_in_symbols_;
	unsigned char found_letter = 0;
	unsigned long long iteration_index = 0;
	while (search_iterations > 0)
	{
		find_letter_by_code(root_node_index_, found_letter, bit_data, iteration_index);
		cout << found_letter;
		search_iterations--;
	}

}

void Encoder::find_letter_by_code(unsigned int sub_tree, unsigned char &letter, const std::vector<bool> &code_seq, unsigned long long &decision_index) const
{
	if (is_leaf(coding_tree_[sub_tree]))
	{
		letter = coding_tree_[sub_tree].character.letter;
	} 
	else
	{
		if (code_seq[decision_index])
		{
			decision_index++;
			find_letter_by_code(coding_tree_[sub_tree].right_child, letter, code_seq, decision_index);
		}
		else
		{
			decision_index++;
			find_letter_by_code(coding_tree_[sub_tree].left_child, letter, code_seq, decision_index);
		}
	}
}




