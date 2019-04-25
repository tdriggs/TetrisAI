#include "NeuralNetwork.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include <Eigen/Dense>


NeuralNetwork NeuralNetwork::from_stream(std::istream &is)
{
	float learning_factor;
    int num_layers;
    
    is.read((char *)&learning_factor, sizeof(learning_factor));
    is.read((char *)&num_layers, sizeof(num_layers));

	std::vector<int> sizes;

	std::cout << "reading size: ";

	for (int i = 0; i < num_layers; i++)
	{
		int size;
		is.read((char *)&size, sizeof(size));
		sizes.push_back(size);
		std::cout << size << " ";
	}
    
	std::cout << std::endl;

    NeuralNetwork nn(sizes, learning_factor);

	std::cout << "Sizes: " << std::endl;
	for (int size : nn.m_sizes)
	{
		std::cout << size << " ";
	}
	std::cout << std::endl;

	for (auto & weight_matrix : nn.m_weights)
	{
		for (int r = 0; r < weight_matrix.rows(); r++)
		{
			for (int c = 0; c < weight_matrix.cols(); c++)
			{
				is.read((char *)&weight_matrix(r, c), sizeof(float));
			}
		}
	}
    
    return nn;
}


NeuralNetwork::NeuralNetwork(std::vector<int> layer_sizes, float learning_factor)
	: m_num_layers(layer_sizes.size())
	, m_sizes(layer_sizes)
	, m_layers()
	, m_deltas()
	, m_weights()
	, m_learning_factor(learning_factor)
{
	if (m_num_layers == 0)
	{
		throw std::invalid_argument("The number of layers must be at least one!");
	}

	for (int i = 0; i < m_num_layers - 1; i++)
	{
		m_layers.push_back(Eigen::VectorXf::Ones(m_sizes[i] + 1)); // extra for the bias
	}

	m_layers.push_back(Eigen::VectorXf::Ones(m_sizes[m_num_layers - 1])); // output doesn't get bias

	for (int i = 1; i < m_num_layers; i++)
	{
		m_deltas.push_back(Eigen::VectorXf::Ones(m_sizes[i]));
		m_weights.push_back(Eigen::MatrixXf::Random(m_sizes[i], m_sizes[i - 1] + 1)); // extra for the bias
	}

	std::cout << m_layers.size() << std::endl;
}

void NeuralNetwork::forward_propagate(const Eigen::VectorXf& input)
{
    if (input.size() != m_sizes[0])
        throw std::invalid_argument("The input vector must be of size <" + std::to_string(m_sizes[0]) + ">");

	m_layers[0].head(m_sizes[0]) = input;

	for (size_t i = 1; i < m_layers.size(); ++i)
	{
		m_layers[i].head(m_sizes[i]) = (m_weights[i - 1] * m_layers[i - 1]).unaryExpr(&sigmoid);
	}
}

void NeuralNetwork::back_propagate(const Eigen::VectorXf& output)
{
    if (output.size() != m_sizes[m_num_layers-1])
        throw std::invalid_argument("The output vector must be of size <" + std::to_string(m_sizes[m_num_layers - 1]) + ">");

    Eigen::VectorXf error = output - m_layers[m_num_layers - 1];
	Eigen::VectorXf delta_o = error.array() * (m_layers[m_num_layers - 1].unaryExpr(&sigmoid_prime)).array();
	m_deltas[m_deltas.size() - 1] = delta_o;

	int delta_size = m_deltas.size();
	for (int delta_index = delta_size - 2; delta_index >= 0; delta_index--)
	{
		int layer_index = delta_index + 1;
		Eigen::VectorXf derivative = m_layers[layer_index].head(m_sizes[layer_index]).unaryExpr(&sigmoid_prime);
		Eigen::VectorXf err = (m_weights[delta_index + 1].transpose() * m_deltas[delta_index + 1]).head(m_sizes[layer_index]);

		Eigen::VectorXf delta = derivative.array() * err.array();
		
		m_deltas[delta_index] = delta;
	}

	int weights_size = m_weights.size();
	for (int i = 0; i < weights_size; ++i)
	{
		m_weights[i] += m_learning_factor * (m_deltas[i] * m_layers[i].transpose());
	}
}

Eigen::VectorXf NeuralNetwork::test(const Eigen::VectorXf& input, const Eigen::VectorXf& output)
{
    forward_propagate(input);
    return output - m_layers[m_num_layers - 1];
}

int NeuralNetwork::classify(const Eigen::VectorXf& input)
{
    float max_val = -1;
    int max_index = -1;

    forward_propagate(input);

    for (int i = 0; i < m_sizes[m_num_layers - 1]; ++i)
    {
        if (max_val < m_layers[m_num_layers - 1][i])
        {
            max_val = m_layers[m_num_layers - 1][i];
            max_index = i;
        }
    }

    return max_index;
}

std::vector<std::pair<int, float>> NeuralNetwork::classification(const Eigen::VectorXf& input)
{
	std::vector<std::pair<int, float>> classification_vector(m_sizes[m_num_layers - 1]);

	forward_propagate(input);

	for (int i = 0; i < m_sizes[m_num_layers - 1]; i++)
	{
		classification_vector.push_back({ i, m_layers[m_num_layers - 1][i] });
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
	os.write((char*)&m_learning_factor, sizeof(m_learning_factor));

	os.write((char *)&m_num_layers, sizeof(m_num_layers));

	for (int size : m_sizes)
	{
		os.write((char *)&size, sizeof(size));
	}
	
	for (const auto & weight_matrix : m_weights)
	{
		for (int r = 0; r < weight_matrix.rows(); r++)
		{
			for (int c = 0; c < weight_matrix.cols(); c++)
			{
				os.write((char *)&weight_matrix(r, c), sizeof(float));
			}
		}
	}
}

int NeuralNetwork::get_num_inputs() const
{
    return m_sizes[0];
}

int NeuralNetwork::get_num_outputs() const
{
    return m_sizes[m_num_layers - 1];
}

void NeuralNetwork::set_learning_factor(float learning_factor)
{
	m_learning_factor = learning_factor;
}

Eigen::VectorXf NeuralNetwork::get_output() const
{
	return m_layers[m_num_layers - 1];
}

const Eigen::MatrixXf& NeuralNetwork::get_weights_ih() const
{
    return m_weights[0];
}

const Eigen::MatrixXf& NeuralNetwork::get_weights_ho() const
{
    return m_weights[m_weights.size() - 1];
}
