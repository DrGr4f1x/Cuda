#include "Stdafx.h"

#include "MultilayerPerceptron.h"

using namespace Eigen;
using namespace std;

MultiLayerPerceptron::MultiLayerPerceptron(const vector<int>& inputSizes, double learningRate)
	: m_learningRate{ learningRate }
{
	for (auto i = 0; i < inputSizes.size() - 1; ++i)
	{
		m_layers.emplace_back(inputSizes[i], inputSizes[i + 1]);
	}
}

MatrixXd MultiLayerPerceptron::Forward(const MatrixXd& input)
{
	auto currentInput = input;
	for (auto& layer : m_layers)
	{
		currentInput = layer.Forward(currentInput);
	}

	return currentInput;
}

void MultiLayerPerceptron::Train(const MatrixXd& X, const MatrixXd& y, int numEpochs)
{
	for (int epoch = 0; epoch < numEpochs; ++epoch)
	{
		// Forward pass
		auto y_pred = Forward(X);

		// Calculate loss (MSE)
		double loss = (y_pred - y).array().square().mean();

		if (epoch % 100 == 0)
		{
			cout << "Epoch: " << epoch << ", loss: " << loss << endl;
		}

		// Backpropagation
		MatrixXd grad = 2.0 * (y_pred - y) / y.cols(); // MSE derivative

		// Backward pass through all the layers in reverse
		for (auto i = m_layers.size() - 1; i >= 0; --i)
		{
			grad = m_layers[i].Backward(grad, m_learningRate);
		}
	}
}

MatrixXd MultiLayerPerceptron::Predict(const MatrixXd& X)
{
	return Forward(X)
}