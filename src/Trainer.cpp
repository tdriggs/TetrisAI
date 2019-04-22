#include "Trainer.h"

#include <iostream>
#include <fstream>
#include <vector>

int Trainer::get_next_value(std::ifstream &file)
{
    char c;
    
    do
    {
        c = file.get();
    } while (c == ',' || c == '\n');
    
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
        train(in_out.first, in_out.second);
    }
}

void Trainer::train(const Eigen::VectorXf& input, const Eigen::VectorXf& output)
{
    m_network.forward_propagate(input);
    m_network.back_propagate(output);
}
