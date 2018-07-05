#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include <CL/cl.hpp>

#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <iomanip>

namespace GlobalVariables
{
	const size_t BLOCK_SIZE = 16;
}

using namespace GlobalVariables;
using std::vector;

size_t matrix_a_dimension;
size_t matrix_b_dimension;

void load_matrix(size_t dimension, vector<float>& matrix, std::ifstream& file_stream)
{
	for (size_t i = 0; i < dimension; ++i)
		for (size_t j = 0; j < dimension; ++j)
			file_stream >> matrix[i * dimension + j];
}

void ñreate_test_matrix(size_t dimension_first, size_t dimension_second)
{
	std::ofstream output_file("test.txt");
	output_file << std::fixed << std::setprecision(3);

	output_file << dimension_first << " " << dimension_second << std::endl;
	for (size_t i = 0; i < dimension_first; ++i)
	{
		for (size_t j = 0; j < dimension_first; ++j)
		{
			output_file << 1 << " ";
		}
		output_file << std::endl;
	}

	for (size_t i = 0; i < dimension_second; ++i)
	{
		for (size_t j = 0; j < dimension_second; ++j)
		{
			output_file << 1 << " ";
		}
		output_file << std::endl;
	}
}

void read_input_file(vector<float>& matrix_a, vector<float>& matrix_b)
{
	std::ifstream input_file("input.txt");

	input_file >> matrix_a_dimension;
	input_file >> matrix_b_dimension;

	size_t matrix_a_length = matrix_a_dimension * matrix_a_dimension;
	size_t matrix_b_length = matrix_b_dimension * matrix_b_dimension;

	matrix_a.resize(matrix_a_length);
	matrix_b.resize(matrix_b_length);

	load_matrix(matrix_a_dimension, matrix_a, input_file);
	load_matrix(matrix_b_dimension, matrix_b, input_file);
}

void set_devices(vector<cl::Platform>& platforms, vector<cl::Device>& devices)
{
	cl::Platform::get(&platforms);
	for (cl_uint i = 0; i < platforms.size(); ++i)
	{
		std::string name;
		std::string version;

		platforms[i].getInfo(CL_PLATFORM_NAME, &name);
		platforms[i].getInfo(CL_PLATFORM_VERSION, &version);

		if (name.find("NVIDIA") != std::string::npos)
		{
			platforms[i].getDevices(CL_DEVICE_TYPE_GPU, &devices);
		}
	}
}

void write_output(const vector<float>&matrix_c)
{
	std::ofstream output_file("output.txt");
	output_file << std::fixed << std::setprecision(3);

	for (size_t i = 0; i < matrix_a_dimension; ++i)
	{
		for (size_t j = 0; j < matrix_a_dimension; ++j)
		{
			output_file << matrix_c[i * matrix_a_dimension + j] << " ";
		}
		output_file << std::endl;
	}
}

int main()
{
    vector<cl::Platform> platforms;
    vector<cl::Device> devices;
    vector<cl::Kernel> kernels;

	vector<float> matrix_a;
	vector<float> matrix_b;
	read_input_file(matrix_a, matrix_b);

	// output matrix
	vector<float> matrix_c(matrix_a.size());
	
	try 
	{
	   set_devices(platforms, devices);

       // create context
       cl::Context context(devices);

       // create command queue
       cl::CommandQueue queue(context, devices[0]);

       // load opencl source
       std::ifstream cl_file("convolution.cl");
       std::string cl_string(std::istreambuf_iterator<char>(cl_file), (std::istreambuf_iterator<char>()));
       cl::Program::Sources source(1, std::make_pair(cl_string.c_str(), cl_string.length() + 1));

       // create program
       cl::Program program(context, source);

       // compile opencl source
       program.build(devices, "-D BLOCK_SIZE=16");
	   
	   // allocate device buffers
	   cl::Buffer matrix_a_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * matrix_a.size());
	   cl::Buffer matrix_c_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * matrix_c.size());
	   cl::Buffer matrix_b_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * matrix_b.size());
	   
	   // copy from cpu to 
	   queue.enqueueWriteBuffer(matrix_a_buffer, CL_TRUE, 0, sizeof(float) * matrix_a.size(), &matrix_a[0]);
	   queue.enqueueWriteBuffer(matrix_b_buffer, CL_TRUE, 0, sizeof(float) * matrix_b.size(), &matrix_b[0]);
	   queue.flush();

	   // load named kernel from opencl source
	   cl::Kernel kernel_gmem(program, "convolution");

	   size_t size = 0;
	   if (matrix_a.size() % BLOCK_SIZE == 0)
	   {
		   size = matrix_a.size();
	   }
	   else
	   {
		   // up to BLOCK_SIZE
		   size = matrix_a.size() + (BLOCK_SIZE - matrix_a.size() % BLOCK_SIZE);
	   }

	   cl::make_kernel<cl::Buffer&, cl::Buffer&, cl::Buffer&, int, int> convolution(kernel_gmem);
	   cl::EnqueueArgs args(queue, cl::NullRange, cl::NDRange(size, size), cl::NDRange(BLOCK_SIZE, BLOCK_SIZE));
	   convolution(args, matrix_a_buffer, matrix_b_buffer, matrix_c_buffer, (int) matrix_b_dimension, (int) matrix_a_dimension);

	   queue.enqueueReadBuffer(matrix_c_buffer, CL_TRUE, 0, sizeof(int) * matrix_c.size(), &matrix_c[0]);

	   write_output(matrix_c);
   }
   catch (cl::Error e)
   {
	   std::cout << std::endl << e.what() << " : " << e.err() << std::endl;
   }

   return 0;
}