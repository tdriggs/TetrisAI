#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <Eigen/Dense>

#include "NeuralNetwork.h"

class Trainer
{
    public:
        typedef std::pair<Eigen::VectorXf, Eigen::VectorXf> InOutPair;
    
    public:
        Trainer(NeuralNetwork &network);
        
        std::vector<InOutPair> parse_file(std::ifstream &file);
    
        void train(const std::vector<InOutPair> &test_data);
        void train(const Eigen::VectorXf &input, const Eigen::VectorXf &output);
        void train(std::ifstream &file);
        
    private:
        static int get_next_value(std::ifstream &file);
        
    private:
        NeuralNetwork &m_network;
};
