#include "NeuralNetwork.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include <Eigen/Dense>


NeuralNetwork NeuralNetwork::from_stream(std::istream &is)
{
    int num_inputs, num_hidden, num_outputs;
    float learning_factor;
    
    is.read((char*) &num_inputs, sizeof(num_inputs));
    is.read((char*) &num_hidden, sizeof(num_hidden));
    is.read((char*) &num_outputs, sizeof(num_outputs));
    is.read((char*) &learning_factor, sizeof(num_outputs));
    
    NeuralNetwork nn(num_inputs, num_hidden, num_outputs, learning_factor);
    
    for (int r = 0; r < nn.m_weights_input_hidden.rows(); r++)
    {
        for (int c = 0; c < nn.m_weights_input_hidden.cols(); c++)
        {
            is.read((char *) &nn.m_weights_input_hidden(r, c), sizeof(float));
        }
    }
    
    for (int r = 0; r < nn.m_weights_hidden_outputs.rows(); r++)
    {
        for (int c = 0; c < nn.m_weights_hidden_outputs.cols(); c++)
        {
            is.read((char *) &nn.m_weights_hidden_outputs(r, c), sizeof(float));
        }
    }
    
    return nn;
}


NeuralNetwork::NeuralNetwork(int num_inputs, int num_hidden, int num_outputs, float learning_factor)
    :m_num_inputs(num_inputs)
    ,m_num_hidden(num_hidden)
    ,m_num_outputs(num_outputs)
    ,m_learning_factor(learning_factor)
{
    m_weights_input_hidden = Eigen::MatrixXf::Random(m_num_hidden, m_num_inputs+1);
    m_weights_hidden_outputs = Eigen::MatrixXf::Random(m_num_outputs, m_num_hidden+1);

    m_input  = Eigen::VectorXf(num_inputs + 1);
    m_hidden = Eigen::VectorXf(num_hidden + 1);
    m_output = Eigen::VectorXf(num_outputs);

    m_delta_h = Eigen::VectorXf(num_hidden);
    m_delta_o = Eigen::VectorXf(num_outputs);

    m_input[num_inputs]    = 1;
    m_hidden[num_hidden]   = 1;
    //m_delta_h[num_hidden]  = 1;
    //m_delta_o[num_outputs] = 1;

    //std::cout << "weights_input_hidden: " << std::endl << m_weights_input_hidden << std::endl;
    //std::cout << "weights_hidden_outputs: " << std::endl << m_weights_input_hidden << std::endl;
}

void NeuralNetwork::forward_propagate(const Eigen::VectorXf& input)
{
    if (input.size() != m_num_inputs)
        throw std::invalid_argument("The input vector must be of size <" + std::to_string(m_num_inputs) + ">");

    m_input.head(m_num_inputs)  = input;
    m_hidden.head(m_num_hidden) = (m_weights_input_hidden * m_input).unaryExpr(&sigmoid);
    m_output = (m_weights_hidden_outputs * m_hidden).unaryExpr(&sigmoid);
}

void NeuralNetwork::back_propagate(const Eigen::VectorXf& output)
{
    if (output.size() != m_num_outputs)
        throw std::invalid_argument("The output vector must be of size <" + std::to_string(m_num_outputs) + ">");

    Eigen::VectorXf error = output - m_output;
    m_delta_o = error.array() * m_output.unaryExpr(&sigmoid_prime).array();
    m_delta_h = m_hidden.head(m_num_hidden).unaryExpr(&sigmoid_prime).array() * (m_weights_hidden_outputs.transpose() * m_delta_o).head(m_num_hidden).array();

    m_weights_hidden_outputs += m_learning_factor * (m_delta_o * m_hidden.transpose());
    m_weights_input_hidden   += m_learning_factor * (m_delta_h * m_input.transpose());

    // std::cout << "weights_input_hidden: " << std::endl << m_weights_input_hidden << std::endl;
    // std::cout << "weights_hidden_outputs: " << std::endl << m_weights_input_hidden << std::endl;
}

Eigen::VectorXf NeuralNetwork::test(const Eigen::VectorXf& input, const Eigen::VectorXf& output)
{
    forward_propagate(input);
    return output - m_output;
}

int NeuralNetwork::classify(const Eigen::VectorXf& input)
{
    float max_val = -1;
    int max_index = -1;

    forward_propagate(input);

    for (int i = 0; i < m_num_outputs; ++i)
    {
        if (max_val < m_output[i])
        {
            max_val = m_output[i];
            max_index = i;
        }
    }

    return max_index;
}

std::vector<std::pair<int, float>> NeuralNetwork::classification(const Eigen::VectorXf& input)
{
	std::vector<std::pair<int, float>> classification_vector(m_num_outputs);

	forward_propagate(input);

	for (int i = 0; i < m_num_outputs; i++)
	{
		classification_vector.push_back({ i, m_output[i] });
	}

	std::sort
	(
		classification_vector.begin(), classification_vector.end(), 
		[](std::pair<int, float> lhs, std::pair<int, float> rhs) 
		{
			return lhs.second > rhs.second; 
		}
	);

	return classification_vector;
}

void NeuralNetwork::serialize(std::ostream &os) const
{
    os.write((char*) &m_num_inputs, sizeof(m_num_inputs));
    os.write((char*) &m_num_hidden, sizeof(m_num_hidden));
    os.write((char*) &m_num_outputs, sizeof(m_num_outputs));
    os.write((char*) &m_learning_factor, sizeof(m_num_outputs));
       
    for (int r = 0; r < m_weights_input_hidden.rows(); r++)
    {
        for (int c = 0; c < m_weights_input_hidden.cols(); c++)
        {
            os.write((char *) &m_weights_input_hidden(r, c), sizeof(float));
        }
    }
    
    for (int r = 0; r < m_weights_hidden_outputs.rows(); r++)
    {
        for (int c = 0; c < m_weights_hidden_outputs.cols(); c++)
        {
            os.write((char *) &m_weights_hidden_outputs(r, c), sizeof(float));
        }
    }
}

int NeuralNetwork::get_num_inputs() const
{
    return m_num_inputs;
}

int NeuralNetwork::get_num_outputs() const
{
    return m_num_outputs;
}

Eigen::VectorXf NeuralNetwork::get_output() const
{
    return m_output;
}

const Eigen::MatrixXf& NeuralNetwork::get_weights_ih() const
{
    return m_weights_input_hidden;
}

const Eigen::MatrixXf& NeuralNetwork::get_weights_ho() const
{
    return m_weights_hidden_outputs;
}
