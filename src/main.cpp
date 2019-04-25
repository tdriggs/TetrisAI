#include <iostream>

#include <string>

#include <cassert>
#include <cstdio>

#include <windows.h>

#include <document.h>
#include <filereadstream.h>

#include "Trainer.h"
#include "NeuralNetwork.h"


int main(int argc, char *argv[])
{
	rapidjson::Document configuration_document;

	if (argc < 2)
	{
		std::cerr << "Usage:" << std::endl
			<< "\ttrain <configuration_filename>" << std::endl;

		return 1;
	}
	else
	{
		std::string configuration_filename = argv[1];

		FILE* fp = fopen(configuration_filename.c_str(), "rb"); // non-Windows use "r"
		char readBuffer[65536];

		if (fp == NULL)
		{
			std::cerr << "Could not open file: " << configuration_filename << std::endl;

			return 2;
		}

		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		configuration_document.ParseStream(is);

		if (configuration_document.HasParseError())
		{
			std::cerr << "Error parsing file: " << configuration_filename << std::endl;

			return 2;
		}
	}

	// assert format
	std::string field_names[] = { "learning_rate", "input_size", "output_size", "hidden_sizes", "training_data", "training_iterations", "input_network", "output_network" };

	assert(configuration_document.IsObject());

	for (const std::string & field_name : field_names)
	{
		if (!configuration_document.HasMember(field_name.c_str()))
			throw std::invalid_argument("Configuration document must have field " + field_name);
	}

	std::vector<int> sizes;

	float learning_rate = configuration_document["learning_rate"].GetFloat();
	int input_size = configuration_document["input_size"].GetInt();
	int output_size = configuration_document["output_size"].GetInt();
	const rapidjson::Value &size_array = configuration_document["hidden_sizes"];
	
	sizes.push_back(input_size);
	for (size_t i = 0; i < size_array.Size(); ++i)
	{
		sizes.push_back(size_array[i].GetInt());
	}
	sizes.push_back(output_size);

	std::string input_data_filename = configuration_document["training_data"].GetString();
	int num_trainings = configuration_document["training_iterations"].GetInt();

	std::string input_network_filename = configuration_document["input_network"].GetString();
	std::string output_filename = configuration_document["output_network"].GetString();


	NeuralNetwork nn(sizes, learning_rate);

	if (input_network_filename != "")
	{
		std::ifstream input_network_file = std::ifstream(input_network_filename, std::ios::binary);

		if (!input_network_file)
		{
			std::cerr << "Could not open input network file: " << input_network_filename << std::endl << strerror(errno);
			return 3;
		}

		nn = NeuralNetwork::from_stream(input_network_file);
		nn.set_learning_factor(learning_rate);
		std::cout << "Setting learning rate to: " << learning_rate << std::endl;
	}

	Trainer trainer(nn);
	std::ifstream data_file = std::ifstream(input_data_filename, std::ios::binary);

	if (!data_file)
	{
		std::cerr << "Could not open input data file: " << input_data_filename << std::endl << strerror(errno);
		return 4;
	}

	std::vector<Trainer::InOutPair> training_data = trainer.parse_file(data_file);
	std::cout << "got vector " << input_data_filename << " " << training_data.size() << std::endl;

	std::vector<Trainer::InOutPair> test_data;
	if (configuration_document.HasMember("test_data"))
	{
		std::string test_data_filename = configuration_document["test_data"].GetString();
		std::ifstream test_data_file;
		test_data_file.open(test_data_filename);

		if (!test_data_file)
		{
			std::cerr << "Error loading test_data file: " << test_data_filename << std::endl << strerror(errno);
			return 6;
		}

		test_data = trainer.parse_file(test_data_file);
		std::cout << "got test vector " << test_data_filename << " " << test_data.size() << std::endl;
	}

	//return 0;

	for (int i = 0; i < num_trainings; i++)
	{
		if (i % 1 == 0)
		{
			std::cout << "Training number: " << i << std::endl;
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			std::cout << "Terminating early at training number: " << i << std::endl;
			break;
		}

		trainer.train(training_data);
		
		if (test_data.size() != 0)
		{
			std::cout << "Test data correct percent: " << trainer.validate(test_data) / static_cast<float>(test_data.size()) << std::endl;
		}
	}

	std::ofstream data_output = std::ofstream(output_filename, std::ios::binary);

	if (!data_output)
	{
		std::cerr << "Could not open output file: " << output_filename << std::endl << strerror(errno);
		return 5;
	}

	nn.serialize(data_output);
	std::cout << "Training data correct percent: " << trainer.validate(training_data) / static_cast<float>(training_data.size()) << std::endl
		<< "Test data correct percent: " << trainer.validate(test_data) / static_cast<float>(test_data.size()) << std::endl;
}
