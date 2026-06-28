#include "Stdafx.h"

#include "Layer.h"

using namespace Eigen;

Layer::Layer(int inputSize, int outputSize)
{
	m_weights = MatrixXd::Random(outputSize, inputSize) * 0.1;
	m_biases = VectorXd::Zero(outputSize);
}

MatrixXd Layer::Forward(const MatrixXd& x)
{
	m_input = x;
	m_activation = (m_weights * m_input) + m_biases.replicate(1, m_input.cols());
	m_output = Relu(m_activation);
	return m_output;
}

MatrixXd Layer::Backward(const MatrixXd& gradOutput, double learningRate)
{
	MatrixXd gradActivation = gradOutput.array() * ReluDerivative(m_activation).array();

	// Calculate gradients
	MatrixXd gradWeights = gradActivation * m_input.transpose();
	VectorXd gradBiases = gradActivation.rowwise().sum();
	MatrixXd gradInput = m_weights.transpose() * gradActivation;

	// Update weights and biases
	m_weights -= learningRate * gradWeights;
	m_biases -= learningRate * gradBiases;

	return gradInput;
}

MatrixXd Layer::Relu(const MatrixXd& x) const
{
	return x.array().max(0.0);
}

MatrixXd Layer::ReluDerivative(const MatrixXd& x) const
{
	return (x.array() > 0.0).cast<double>();
}