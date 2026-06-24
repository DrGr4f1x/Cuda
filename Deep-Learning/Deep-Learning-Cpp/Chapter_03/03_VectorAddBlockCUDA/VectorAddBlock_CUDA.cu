
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

__global__ void add(int n, float* x, float* y)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	for (int i = index; i < n; i += stride)
	{
		y[i] = x[i] + y[i];
	}
}

int main()
{
	const int N = 1 << 20;
	float* x = nullptr;
	float* y = nullptr;
	cudaMallocManaged(&x, N * sizeof(float));
	cudaMallocManaged(&y, N * sizeof(float));
	for (int i = 0; i < N; ++i)
	{
		x[i] = 1.0f;
		y[i] = 2.0f;
	}

	const int blockSize = 256;
	const int numBlocks = (N + blockSize - 1) / blockSize;

	cout << "N: " << N << " blockSize: " << blockSize << " numBlocks: " << numBlocks << endl;

	add<<<numBlocks, blockSize>>>(N, x, y);

	cudaDeviceSynchronize();
	float maxError = 0.0f;
	for (int i = 0; i < N; ++i)
	{
		maxError = fmax(maxError, fabs(y[i] - 3.0f));
	}
	cout << "Max error: " << maxError << endl;
	cudaFree(x);
	cudaFree(y);
	return 0;
}