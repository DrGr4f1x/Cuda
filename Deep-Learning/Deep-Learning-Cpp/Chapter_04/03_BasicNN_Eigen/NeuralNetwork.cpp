#include "Stdafx.h"

#include "NeuralNetwork.h"

using namespace Eigen;

NeuralNetwork::NeuralNetwork(int inputSize, int hiddenSize, int outputSize, double lr)
	: m_learningRate{ lr }
{
	// Random init (for teaching; in practice consider Xavier/He)
	m_weightsInputHidden = MatrixXd::Random(hiddenSize, inputSize);
	m_weightsHiddenOutput = MatrixXd::Random(outputSize, hiddenSize);
	m_biasHidden = VectorXd::Random(hiddenSize);
	m_biasOutput = VectorXd::Random(outputSize);
}

VectorXd NeuralNetwork::Forward(const VectorXd& input) const
{
	// Hidden layer: z1 = W1*x + b1; a1 = Sigmoid(z1)
	VectorXd hiddenInput = m_weightsInputHidden * input + m_biasHidden;
	VectorXd hiddenOutput = Sigmoid(hiddenInput);

	// Output layer: z2 = W2*a1 + b2; a2 = Sigmoid(z2)
	VectorXd finalInput = m_weightsHiddenOutput * hiddenOutput + m_biasOutput;
	VectorXd finalOutput = Sigmoid(finalInput);

	return finalOutput;
}

void NeuralNetwork::Train(const VectorXd& input, const VectorXd& target)
{
	// 1) Forward
	VectorXd hiddenInput = m_weightsInputHidden * input + m_biasHidden;
	VectorXd hiddenOutput = Sigmoid(hiddenInput);

	VectorXd finalInput = m_weightsHiddenOutput * hiddenOutput + m_biasOutput;
	VectorXd finalOutput = Sigmoid(finalInput);

	// 2) Error (MSE-style)
	VectorXd outputError = target - finalOutput;

	// 3) Backprop deltas (use deltas, not raw error)
	VectorXd outputDelta = SigmoidDerivative(finalOutput).cwiseProduct(outputError);
	VectorXd hiddenError = m_weightsHiddenOutput.transpose() * outputDelta;
	VectorXd hiddenDelta = SigmoidDerivative(hiddenOutput).cwiseProduct(hiddenError);

	// 4) SGD updates (+= because delta uses (target - output))
	m_weightsHiddenOutput += m_learningRate * (outputDelta * hiddenOutput.transpose());
	m_biasOutput += m_learningRate * outputDelta;

	m_weightsInputHidden += m_learningRate * (hiddenDelta * input.transpose());
	m_biasHidden += m_learningRate * hiddenDelta;

}