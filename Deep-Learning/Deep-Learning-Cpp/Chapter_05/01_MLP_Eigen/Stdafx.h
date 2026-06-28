#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

// Windows headers
#include <windows.h>
#include <wrl.h>
#include <comdef.h>

// Standard library
#include <cmath>
#include <iostream>
#include <vector>

// LibTorch headers
#include <torch/csrc/api/include/torch/torch.h>

// Eigen headers
#include <Eigen/Dense>