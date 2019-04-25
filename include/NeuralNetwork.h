#pragma once

#include <array>
#include <vector>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/StdVector>

class NeuralNetwork
{
    public:
        static inline float sigmoid(float x) { return 1 / (1 + std::exp(-x)); }
        static inline float sigmoid_prime(float x) { return x * (1 - x); }
        
        static NeuralNetwork from_stream(std::istream &is);

    public:
        NeuralNetwork(std::vector<int> layer_sizes, float learning_factor = 0.2f);

        void forward_propagate(const Eigen::VectorXf& input);
        void back_propagate(const Eigen::VectorXf& output);

        Eigen::VectorXf test(const Eigen::VectorXf& input, const Eigen::VectorXf& output);
        int classify(const Eigen::VectorXf& input);

		// ordered list of output_index, output_value
		std::vector<std::pair<int, float>> classification(const Eigen::VectorXf& input);

        void serialize(std::ostream &os) const;

        int get_num_inputs() const;
        int get_num_outputs() const;

        Eigen::VectorXf get_output() const;
        const Eigen::MatrixXf & get_weights_ih() const;
        const Eigen::MatrixXf & get_weights_ho() const;

    protected:

    private:
		int m_num_layers;
		std::vector<int> m_sizes;
		std::vector<Eigen::VectorXf, Eigen::aligned_allocator<Eigen::VectorXf>> m_layers;
		std::vector<Eigen::VectorXf, Eigen::aligned_allocator<Eigen::VectorXf>> m_deltas;
		std::vector<Eigen::MatrixXf, Eigen::aligned_allocator<Eigen::MatrixXf>> m_weights;

        float m_learning_factor;

		int m_output_index;
};
