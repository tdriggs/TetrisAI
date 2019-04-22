#include "NeuralNetwork.h"

#include <iostream>
#include <fstream>
#include <string>

#include <Eigen/Dense>

#include "Game.h"


typedef std::pair<Eigen::VectorXf, Eigen::VectorXf> InOutPair;

int get_next_value(std::ifstream &file)
{
	char c;

	do
	{
		c = file.get();
	} while (c == ',' || c == '\n');

	return c - '0';
}

std::vector<InOutPair> parse_file(std::string filename)
{
	std::ifstream file(filename);

	std::vector<InOutPair> test_data;

	while (true)
	{
		Eigen::VectorXf input(Game::NUM_INPUTS);
		Eigen::VectorXf output(Game::NUM_OUTPUTS);

		for (int i = 0; i < Game::NUM_INPUTS; i++)
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

		for (int i = 0; i < Game::NUM_OUTPUTS; i++)
		{
			int val = get_next_value(file);

			if (val != 0 && val != 1)
			{
				throw std::runtime_error("wrong number of cells per row");
			}

			output[i] = static_cast<float>(val);
		}

		test_data.push_back({ input, output });
	}

	return test_data;
}


NeuralNetwork::NeuralNetwork(int num_inputs, int num_hidden, int num_outputs)
	:m_num_inputs(num_inputs)
	, m_num_hidden(num_hidden)
	, m_num_outputs(num_outputs)
	, m_learning_factor(0.2f)
{
	m_weights_input_hidden = Eigen::MatrixXf::Random(m_num_hidden, m_num_inputs + 1);
	m_weights_hidden_outputs = Eigen::MatrixXf::Random(m_num_outputs, m_num_hidden + 1);

	m_input = Eigen::VectorXf(num_inputs + 1);
	m_hidden = Eigen::VectorXf(num_hidden + 1);
	m_output = Eigen::VectorXf(num_outputs);

	m_delta_h = Eigen::VectorXf(num_hidden);
	m_delta_o = Eigen::VectorXf(num_outputs);

	m_input[num_inputs] = 1;
	m_hidden[num_hidden] = 1;
	//m_delta_h[num_hidden]  = 1;
	//m_delta_o[num_outputs] = 1;

	//std::cout << "weights_input_hidden: " << std::endl << m_weights_input_hidden << std::endl;
	//std::cout << "weights_hidden_outputs: " << std::endl << m_weights_input_hidden << std::endl;
}

void NeuralNetwork::forward_propagate(const Eigen::VectorXf& input)
{
	if (input.size() != m_num_inputs)
		throw std::invalid_argument("The input vector must be of size <" + std::to_string(m_num_inputs) + ">");

	m_input.head(m_num_inputs) = input;
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
	m_weights_input_hidden += m_learning_factor * (m_delta_h * m_input.transpose());

	// std::cout << "weights_input_hidden: " << std::endl << m_weights_input_hidden << std::endl;
	// std::cout << "weights_hidden_outputs: " << std::endl << m_weights_input_hidden << std::endl;
}

void NeuralNetwork::train(const std::string filename)
{
	train(parse_file(filename));
}

void NeuralNetwork::train(const std::vector<std::pair<Eigen::VectorXf, Eigen::VectorXf>> & test_data)
{
	for (const auto & in_out : test_data)
	{
		train(in_out.first, in_out.second);
	}
}

void NeuralNetwork::train(const Eigen::VectorXf& input, const Eigen::VectorXf& output)
{
	forward_propagate(input);
	back_propagate(output);
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
