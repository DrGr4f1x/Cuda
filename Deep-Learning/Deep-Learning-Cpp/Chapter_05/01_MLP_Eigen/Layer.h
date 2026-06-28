#pragma once

class Layer
{
public:
	Layer(int inputSize, int outputSize);

	Eigen::MatrixXd Forward(const Eigen::MatrixXd& c);

	Eigen::MatrixXd Backward(const Eigen::MatrixXd& gradOutput, double learningRate);

	Eigen::MatrixXd Relu(const Eigen::MatrixXd& x) const;

	Eigen::MatrixXd ReluDerivative(const Eigen::MatrixXd& x) const;

private:
	Eigen::MatrixXd m_weights;
	Eigen::VectorXd m_biases;
	Eigen::MatrixXd m_activation;
	Eigen::MatrixXd m_input;
	Eigen::MatrixXd m_output;
};