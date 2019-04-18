#pragma once

#include <array>
#include <vector>
#include <cmath>

#include <Eigen/Dense>

class NeuralNetwork
{
public:
	static inline float sigmoid(float x) { return 1 / (1 + std::exp(-x)); }
	static inline float sigmoid_prime(float x) { return x * (1 - x); }

public:
	NeuralNetwork(int num_inputs, int num_hidden, int num_outputs);

	void forward_propagate(const Eigen::VectorXf& input);
	void back_propagate(const Eigen::VectorXf& output);

	void train(const std::vector<std::pair<Eigen::VectorXf, Eigen::VectorXf>> & test_data);
	void train(const Eigen::VectorXf& input, const Eigen::VectorXf& output);
	Eigen::VectorXf test(const Eigen::VectorXf& input, const Eigen::VectorXf& output);
	int classify(const Eigen::VectorXf& input);

	Eigen::VectorXf get_output() const;
	const Eigen::MatrixXf & get_weights_ih() const;
	const Eigen::MatrixXf & get_weights_ho() const;


protected:

private:
	int m_num_inputs, m_num_hidden, m_num_outputs;
	float m_learning_factor;

	Eigen::MatrixXf m_weights_input_hidden;
	Eigen::MatrixXf m_weights_hidden_outputs;

	// Includes a '1' for bias input
	Eigen::VectorXf m_input, m_hidden, m_output;
	Eigen::VectorXf m_delta_h, m_delta_o;
};
