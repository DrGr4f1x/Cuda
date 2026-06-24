#include <iostream>
#include <algorithm>
#include <cmath>

// Perform element-wis accumulation of two vectors
void vectorAddCPU(int length, float* inputA, float* inputB)
{
	for (int i = 0; i < length; ++i)
	{
		inputB[i] += inputA[i];
	}
}

int main()
{
	const int SIZE = 1 << 20; // 1,048,576 elements

	// Allocate memory on the host (CPU)
	float* vecA = new float[SIZE];
	float* vecB = new float[SIZE];

	// Populate arrays with sample values
	for (int i = 0; i < SIZE; ++i)
	{
		vecA[i] = 0.5f;
		vecB[i] = 2.5f;
	}

	// Execute vector addition
	vectorAddCPU(SIZE, vecA, vecB);

	// Verify correctness
	float largestDeviation = 0.0f;
	for (int i = 0; i < SIZE; ++i)
	{
		float expected = 3.0f;
		largestDeviation = std::max(largestDeviation, std::fabs(vecB[i] - expected));
	}

	std::cout << "Largest deviation: " << largestDeviation << std::endl;

	// Release allocated memory
	delete[] vecA;
	delete[] vecB;
	return 0;
}