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

}

int main()
{
	LinearRegression();

	SingleLogisticNeuron();

	return 0;
}