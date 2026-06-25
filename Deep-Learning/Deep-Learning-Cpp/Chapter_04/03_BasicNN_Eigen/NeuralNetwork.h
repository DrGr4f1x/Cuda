#pragma once

#include <Eigen/Dense>
#include <cmath>

class NeuralNetwork
{
public:
	NeuralNetwork(int inputSize, int hiddenSize, int outputSize, double lr);

	Eigen::VectorXd Forward(const Eigen::VectorXd& input) const;

	void Train(const Eigen::VectorXd& input, const Eigen::VectorXd& target);
private:
	Eigen::VectorXd Sigmoid(const Eigen::VectorXd& x) const
	{
		return 1.0 / (1.0 + (-x.array()).exp());
	}

	Eigen::VectorXd SigmoidDerivative(const Eigen::VectorXd& y) const
	{
		return y.array() * (1.0 - y.array());
	}

private:
	Eigen::MatrixXd m_weightsInputHidden;
	Eigen::MatrixXd m_weightsHiddenOutput;
	Eigen::VectorXd m_biasHidden;
	Eigen::VectorXd m_biasOutput;
	double m_learningRate{ 0.01 };
};