#include "Parser.h"

parser::parser(unsigned int argc, const char *argv[]) 
	: input_length_(argc)
	, input_params_(argv)
	, command_task_(task::undefined)
	, input_filename_("")
	, output_filename_("")
{
}

parser::~parser()
{
}

void parser::update(int argc, const char *argv[])
{
	input_length_    = argc;
	input_params_    = argv;
	command_task_    = task::undefined;
	input_filename_  = "";
	output_filename_ = "";
}

task parser::retrive_task()
{
	using std::string;

	if (input_length_ != KEY_AMOUNT)
	{
		return task::signal_fail;
	}

	for (unsigned int i = 0; i < input_length_; ++i)
	{
		string key(input_params_[i], strlen(input_params_[i]));

		if (key == "-c")
		{
			command_task_ = task::archive;
			continue;
		}

		if (key == "-u")
		{
			command_task_ = task::extract;
			continue;
		}

		if (key == "-f" && (i + 1) < input_length_)
		{
			input_filename_ = string(input_params_[i + 1], strlen(input_params_[i + 1]));
			++i;
		}

		if (key == "-o" && (i + 1) < input_length_)
		{
			output_filename_ = string(input_params_[i + 1], strlen(input_params_[i + 1]));
			++i;
		}

	}

	if (!input_filename_.empty() && !output_filename_.empty())
	{
		return command_task_;
	}
	else
	{
		return task::signal_fail;
	}
}

std::string parser::get_input_filename() const
{
	return input_filename_;
}

std::string parser::get_output_filename() const
{
	return output_filename_;
}

	
