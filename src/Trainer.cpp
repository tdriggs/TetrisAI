#include "Trainer.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <Windows.h>

int Trainer::get_next_value(std::ifstream &file)
{
    char c;
    
    do
    {
        c = file.get();
    } while (!(c == '0' || c == '1') && !file.eof());
    
    return c - '0';
}

std::vector<Trainer::InOutPair> Trainer::parse_file(std::ifstream &file)
{    
    std::vector<InOutPair> test_data;
    
    while (true)
    {
        Eigen::VectorXf input(m_network.get_num_inputs());
        Eigen::VectorXf output(m_network.get_num_outputs());
        
        for (int i = 0; i < m_network.get_num_inputs(); i++)
        {
            int val = get_next_value(file);
            
            if (val != 0 && val != 1)
            {
                if (i == 0)
                    return test_data;
                else
                    throw std::runtime_error("wrong number of cells per row");
            }
            
            input[i] = static_cast<float>(val);
        }
        
        for (int i = 0; i < m_network.get_num_outputs(); i++)
        {
            int val = get_next_value(file);
            
            if (val != 0 && val != 1)
            {
                throw std::runtime_error("wrong number of cells per row");
            }
            
            output[i] = static_cast<float>(val);
        }
        
        test_data.push_back({input, output});
    }
    
    return test_data;
}


Trainer::Trainer(NeuralNetwork &network)
    : m_network(network)
{
}
    
void Trainer::train(std::ifstream &file)
{
    train(parse_file(file));
}

void Trainer::train(const std::vector<InOutPair> &test_data)
{
    for (const auto & in_out : test_data)
    {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}

        train(in_out.first, in_out.second);
    }
}

void Trainer::train(const Eigen::VectorXf& input, const Eigen::VectorXf& output)
{
    m_network.forward_propagate(input);
    m_network.back_propagate(output);
}

int Trainer::validate(const std::vector<InOutPair> &test_data)
{
	int successes = 0;

	for (const InOutPair & input_output : test_data)
	{
		float max_val = 0.0f;
		int max_index = 0;

		for (int i = 0; i < input_output.second.size(); ++i)
		{
			if (input_output.second[i] > max_val)
			{
				max_index = i;
				max_val = input_output.second(i);
				//std::cout << "Max: " << max_index << " " << max_val << std::endl;
			}
		}

		int classification = m_network.classify(input_output.first);

		//std::cout << "Max: " << max_index << " Class: " << classification << std::endl;
		//std::cout << max_val << std::endl;

		if (classification == max_index)
		{
			successes++;
		}
	}

	return successes;
}
