#include <iostream>

#include <string>

#include <windows.h>

#include "Trainer.h"
#include "NeuralNetwork.h"


int main(int argc, char *argv[])
{
	std::string input_data_filename;
	std::string output_filename;
	int num_trainings;

	std::string input_network_filename = "";
	if (argc >= 3 + 1)
	{
		input_data_filename = std::string(argv[1]);
		output_filename = std::string(argv[2]);
		num_trainings = atoi(argv[3]);

		if (argc >= 4 + 1)
		{
			input_network_filename = std::string(argv[4]);
		}
	}
	else
	{
		std::cerr << "Usage:" << std::endl
			      << "\ttrain <input_data_filename> <output_filename> <num_trainings>[<input_network_filename>]" << std::endl;

		return 1;
	}

	std::vector<int> sizes({ 221, 4000, 241 });

	NeuralNetwork nn(sizes);

	if (input_network_filename != "")
	{
		std::ifstream input_network_file = std::ifstream(input_network_filename, std::ios::binary);

		if (!input_network_file)
		{
			std::cerr << "Could not open input network file: " << input_network_filename << std::endl << strerror(errno);
			return 2;
		}

		nn = NeuralNetwork::from_stream(input_network_file);
	}

	Trainer trainer(nn);
	std::ifstream data_file = std::ifstream(input_data_filename, std::ios::binary);

	if (!data_file)
	{
		std::cerr << "Could not open input data file: " << input_data_filename << std::endl << strerror(errno);
		return 3;
	}

	std::ofstream data_output = std::ofstream(output_filename, std::ios::binary);

	if (!data_output)
	{
		std::cerr << "Could not open output file: " << output_filename << std::endl << strerror(errno);
		return 4;
	}

	std::vector<Trainer::InOutPair> data = trainer.parse_file(data_file);

	for (int i = 1; i < num_trainings; i++)
	{
		if (i % 100 == 0)
		{
			std::cout << "Training number: " << i << std::endl;
		}

		if (GetAsyncKeyState(VK_TAB))
		{
			std::cout << "Terminating early at training number: " << i << std::endl;
			break;
		}

		trainer.train(data);
	}

	nn.serialize(data_output);
}
