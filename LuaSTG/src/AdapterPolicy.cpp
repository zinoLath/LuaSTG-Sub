﻿#include "AdapterPolicy.hpp"
#define NOMINMAX
#include <Windows.h>

// https://developer.download.nvidia.cn/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000000;

// https://gpuopen.com/learn/amdpowerxpressrequesthighperformance/
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000000;

void SetAdapterPolicy(bool enable)
{
    NvOptimusEnablement = enable ? 0x00000001 : 0x00000000;
    AmdPowerXpressRequestHighPerformance = enable ? 0x00000001 : 0x00000000;
}
