#include <torch/csrc/api/include/torch/torch.h>
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HMODULE torchCudaDll = LoadLibraryA("torch_cuda.dll");
	if (torchCudaDll == NULL) 
	{
		std::cerr << "Failed to load torch_cuda.dll. Error code: " << GetLastError() << std::endl;

	}
	else 
	{
		std::cout << "Successfully loaded torch_cuda.dll" << std::endl;
	}


	torch::manual_seed(42);

	// Pick device (CUDA if available)
	torch::Device device = torch::cuda::is_available() ? torch::kCUDA : torch::kCPU;
	cout << "Using device: " << (device.is_cuda() ? "CUDA" : "CPU") << endl;

	const int64_t batch = 4;
	const int64_t in_f = 5;
	const int64_t out_f = 3;

	auto x = torch::randn({ batch, in_f }).to(device);

	torch::nn::Linear fc(in_f, out_f);
	fc->to(device);

	torch::nn::init::kaiming_uniform_(fc->weight, /*a=*/ sqrt(5.0));
	torch::nn::init::zeros_(fc->bias);

	auto z = fc->forward(x); // [batch, out_f]
	auto y = torch::relu(z); // activation

	cout << "Input shape: " << x.sizes() << endl;
	cout << "Logits shape: " << z.sizes() << endl;
	cout << "Output shape: " << y.sizes() << endl;

	cout << "Output sample: " << endl << y.slice(/*dim=*/0, 0, 2) << endl;
	

	/*if (torchCudaDll != NULL)
	{
		FreeLibrary(torchCudaDll);
	}*/

	return 0;
}