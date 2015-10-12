#pragma once

#include <string>

const uint32_t KEY_AMOUNT = 6;

enum task
{
	undefined
	, archive
	, extract
	, signal_fail
};

class parser
{
public:

	parser(unsigned int argc, const char *argv[]);
	virtual ~parser();
	
	void update(int argc, const char *argv[]);
	task retrive_task();

	std::string get_input_filename()  const;
	std::string get_output_filename() const;

private:

	uint32_t     input_length_;
	const char **input_params_;
	task         command_task_;
	std::string  input_filename_;
	std::string  output_filename_;
};

