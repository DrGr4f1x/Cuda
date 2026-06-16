#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

static inline double sigmoid(double z)
{
	return 1.0 / (1.0 + exp(-z));
}

void LinearRegression()
{
	mt19937 rng(42);
	uniform_real_distribution<double> U(0.0, 1.0);
	normal_distribution<double> N(0.0, 0.2);

	// Synthetic data - a line defined by y = 2.5*x + 0.7
	const int n = 200;
	const double target_w = 2.5;
	const double target_b = 0.7;
	vector<double> x(n), y(n);
	for (int i = 0; i < n; ++i)
	{
		x[i] = U(rng);
		y[i] = target_w * x[i] + target_b + N(rng);
	}

	// Simple linear regression
	double w = 0.0;
	double b = 0.0;
	double lr = 0.1;
	const int epochs = 1000;

	// Gradient descent for linear regression
	for (int i = 0; i < n; ++i)
	{
		double y_hat = w * x[i] + b;
		double resid = y_hat - y[i];
		w -= lr * (2.0 * resid * x[i]);
		b -= lr * (2.0 * resid);
	}

	// Print results
	cout << "Linear regression:" << endl;
	cout << "  w: " << w << ", target_w: " << target_w << endl;
	cout << "  b: " << b << ", target_b: " << target_b << endl;
}

void SingleLogisticNeuron()
{
	cout << "Single logistic neuron:" << endl;

	mt19937 rng(123);
	normal_distribution<double> N0x(-2.0, 1.0), N0y(-2.0, 1.0);
	normal_distribution<double> N1x(2.0, 1.0), N1y(2.0, 1.0);

	const int n_per = 200;
	vector<array<double, 2>> X;
	vector<int> y;
	X.reserve(2 * n_per);
	y.reserve(2 * n_per);

	for (int i = 0; i < n_per; ++i)
	{
		X.push_back({ N0x(rng), N0y(rng) }); y.push_back(0);
		X.push_back({ N1x(rng), N1y(rng) }); y.push_back(1);
	}
	const int n = (int)X.size();

	double w1 = 0.0;
	double w2 = 0.0;
	double b = 0.0;
	const int epochs = 3000;
	const double lr = 0.1;

	for (int epoch = 1; epoch <= epochs; ++epoch)
	{
		double gw1 = 0.0;
		double gw2 = 0.0;
		double gb = 0.0;

		for (int i = 0; i < n; ++i)
		{
			double z = w1 * X[i][0] + w2 * X[i][1] + b; // Linear score
			double p = sigmoid(z);						// probability
			double diff = (p - y[i]);

			gw1 += diff * X[i][0] / n;
			gw2 += diff * X[i][1] / n;
			gb += diff / n;
		}

		w1 -= lr * gw1;
		w2 -= lr * gw2;
		b -= lr * gb;

		// Monitor training with BCE
		if (epoch % 500 == 0)
		{
			double loss = 0.0f;
			for (int i = 0; i < n; ++i)
			{
				double p = sigmoid(w1 * X[i][0] + w2 * X[i][1] + b);
				p = clamp(p, 1e-12, 1.0 - 1e-12);
				loss += -(y[i] * log(p) + (1.0 - y[i]) * log(1.0 - p));
			}
			loss /= n;
			cout << "Epoch " << epoch << "  BCE = " << loss
				<< "  w = [ " << w1 << ", " << w2 << " ]  b = " << b << endl;
		}
	}

	int correct = 0;
	for (int i = 0; i < n; ++i)
	{
		double p = sigmoid(w1 * X[i][0] + w2 * X[i][1] + b);
		int pred = (p >= 0.5) ? 1 : 0;
		if (pred == y[i])
		{
			++correct;
		}
	}
	
	cout << endl << "Accuracy: " << (100.0 * correct) / n << "%" << endl;
}

int main()
{
	LinearRegression();

	cout << endl;

	SingleLogisticNeuron();

	return 0;
}