#pragma once

#include "Layer.h"

class MultiLayerPerceptron
{
public:
	MultiLayerPerceptron(const std::vector<int>& layerSizes, double learningRate);

	Eigen::MatrixXd Forward(const Eigen::MatrixXd& input);

	void Train(const Eigen::MatrixXd& X, const Eigen::MatrixXd& y, int numEpochs);

	Eigen::MatrixXd Predict(const Eigen::MatrixXd& X);

private:
	std::vector<Layer> m_layers;
	double m_learningRate{ 0.01 };
};