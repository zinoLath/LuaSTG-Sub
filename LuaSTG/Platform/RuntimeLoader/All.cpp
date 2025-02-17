#include "Platform/Shared.hpp"

#include "Platform/RuntimeLoader/DXGI.hpp"

namespace Platform::RuntimeLoader
{
	HRESULT DXGI::CreateFactory(REFIID riid, void** ppFactory)
	{
		if (api_CreateDXGIFactory2)
		{
			UINT flags = 0;
		#ifdef _DEBUG
			flags |= DXGI_CREATE_FACTORY_DEBUG;
		#endif
			return api_CreateDXGIFactory2(flags, riid, ppFactory);
		}
		else if (api_CreateDXGIFactory1)
		{
			return api_CreateDXGIFactory1(riid, ppFactory);
		}
		else if (api_CreateDXGIFactory)
		{
			return api_CreateDXGIFactory(riid, ppFactory);
		}
		else
		{
			return E_NOTIMPL;
		}
	}

	DXGI::DXGI()
	{
		dll_dxgi = LoadLibraryW(L"dxgi.dll");
		if (dll_dxgi)
		{
			api_CreateDXGIFactory = (decltype(api_CreateDXGIFactory))
				GetProcAddress(dll_dxgi, "CreateDXGIFactory");
			api_CreateDXGIFactory1 = (decltype(api_CreateDXGIFactory1))
				GetProcAddress(dll_dxgi, "CreateDXGIFactory1");
			api_CreateDXGIFactory2 = (decltype(api_CreateDXGIFactory2))
				GetProcAddress(dll_dxgi, "CreateDXGIFactory2");
		}
	}
	DXGI::~DXGI()
	{
		if (dll_dxgi)
		{
			FreeLibrary(dll_dxgi);
		}
		dll_dxgi = NULL;
		api_CreateDXGIFactory = NULL;
		api_CreateDXGIFactory1 = NULL;
		api_CreateDXGIFactory2 = NULL;
	}
}

#include "Platform/RuntimeLoader/Direct3D11.hpp"

namespace Platform::RuntimeLoader
{
	HRESULT Direct3D11::CreateDevice(
		D3D_DRIVER_TYPE DriverType,
		UINT Flags,
		D3D_FEATURE_LEVEL TargetFeatureLevel,
		ID3D11Device** ppDevice,
		D3D_FEATURE_LEVEL* pFeatureLevel,
		ID3D11DeviceContext** ppImmediateContext)
	{
		if (api_D3D11CreateDevice)
		{
		#ifdef _DEBUG
			Flags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif
			HRESULT hr = S_OK;
			D3D_FEATURE_LEVEL const d3d_feature_level_list[9] = {
				//D3D_FEATURE_LEVEL_12_2, // no longer supported
				D3D_FEATURE_LEVEL_12_1,
				D3D_FEATURE_LEVEL_12_0,
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};
			UINT const d3d_feature_level_size = 9;
			D3D_FEATURE_LEVEL d3d_feature_level = D3D_FEATURE_LEVEL_9_1;
			for (UINT offset = 0; offset < d3d_feature_level_size; offset += 1)
			{
				hr = api_D3D11CreateDevice(
					NULL,
					DriverType,
					NULL,
					Flags,
					d3d_feature_level_list + offset,
					d3d_feature_level_size - offset,
					D3D11_SDK_VERSION,
					NULL,
					&d3d_feature_level,
					NULL);
				if (SUCCEEDED(hr))
				{
					if ((UINT)d3d_feature_level >= (UINT)TargetFeatureLevel)
					{
						return api_D3D11CreateDevice(
							NULL,
							DriverType,
							NULL,
							Flags,
							d3d_feature_level_list + offset,
							d3d_feature_level_size - offset,
							D3D11_SDK_VERSION,
							ppDevice,
							pFeatureLevel,
							ppImmediateContext);
					}
					else
					{
						return E_NOTIMPL;
					}
				}
			}
			return hr;
		}
		else
		{
			return E_NOTIMPL;
		}
	}
	HRESULT Direct3D11::CreateDevice(
		IDXGIAdapter* pAdapter,
		UINT Flags,
		D3D_FEATURE_LEVEL TargetFeatureLevel,
		ID3D11Device** ppDevice,
		D3D_FEATURE_LEVEL* pFeatureLevel,
		ID3D11DeviceContext** ppImmediateContext)
	{
		if (api_D3D11CreateDevice)
		{
		#ifdef _DEBUG
			Flags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif
			HRESULT hr = S_OK;
			D3D_FEATURE_LEVEL const d3d_feature_level_list[9] = {
				//D3D_FEATURE_LEVEL_12_2, // no longer supported
				D3D_FEATURE_LEVEL_12_1,
				D3D_FEATURE_LEVEL_12_0,
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};
			UINT const d3d_feature_level_size = 9;
			D3D_FEATURE_LEVEL d3d_feature_level = D3D_FEATURE_LEVEL_9_1;
			for (UINT offset = 0; offset < d3d_feature_level_size; offset += 1)
			{
				hr = api_D3D11CreateDevice(
					pAdapter,
					D3D_DRIVER_TYPE_UNKNOWN,
					NULL,
					Flags,
					d3d_feature_level_list + offset,
					d3d_feature_level_size - offset,
					D3D11_SDK_VERSION,
					NULL,
					&d3d_feature_level,
					NULL);
				if (SUCCEEDED(hr))
				{
					if ((UINT)d3d_feature_level >= (UINT)TargetFeatureLevel)
					{
						return api_D3D11CreateDevice(
							pAdapter,
							D3D_DRIVER_TYPE_UNKNOWN,
							NULL,
							Flags,
							d3d_feature_level_list + offset,
							d3d_feature_level_size - offset,
							D3D11_SDK_VERSION,
							ppDevice,
							pFeatureLevel,
							ppImmediateContext);
					}
					else
					{
						return E_NOTIMPL;
					}
				}
			}
			return hr;
		}
		else
		{
			return E_NOTIMPL;
		}
	}

	Direct3D11::Direct3D11()
	{
		dll_d3d11 = LoadLibraryW(L"d3d11.dll");
		if (dll_d3d11)
		{
			api_D3D11CreateDevice = (decltype(api_D3D11CreateDevice))
				GetProcAddress(dll_d3d11, "D3D11CreateDevice");
		}
	}
	Direct3D11::~Direct3D11()
	{
		if (dll_d3d11)
		{
			FreeLibrary(dll_d3d11);
		}
		dll_d3d11 = NULL;
		api_D3D11CreateDevice = NULL;
	}
}

#include "Platform/RuntimeLoader/DirectComposition.hpp"

namespace Platform::RuntimeLoader
{
	HRESULT DirectComposition::CreateDevice(IUnknown* renderingDevice, REFIID iid, void** dcompositionDevice)
	{
		if (api_DCompositionCreateDevice3)
		{
			return api_DCompositionCreateDevice3(renderingDevice, iid, dcompositionDevice);
		}
		else if (api_DCompositionCreateDevice2)
		{
			return api_DCompositionCreateDevice2(renderingDevice, iid, dcompositionDevice);
		}
		else if (api_DCompositionCreateDevice)
		{
			HRESULT hr = S_OK;
			IDXGIDevice* dxgiDevice = NULL;
			hr = renderingDevice->QueryInterface(&dxgiDevice);
			if (FAILED(hr)) return hr;
			hr = api_DCompositionCreateDevice(dxgiDevice, iid, dcompositionDevice);
			dxgiDevice->Release();
			return hr;
		}
		else
		{
			return E_NOTIMPL;
		}
	}

	DirectComposition::DirectComposition()
	{
		dll_dcomp = LoadLibraryExW(L"dcomp.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
		if (dll_dcomp)
		{
			api_DCompositionCreateDevice = (decltype(api_DCompositionCreateDevice))
				GetProcAddress(dll_dcomp, "DCompositionCreateDevice");
			api_DCompositionCreateDevice2 = (decltype(api_DCompositionCreateDevice2))
				GetProcAddress(dll_dcomp, "DCompositionCreateDevice2");
			api_DCompositionCreateDevice3 = (decltype(api_DCompositionCreateDevice3))
				GetProcAddress(dll_dcomp, "DCompositionCreateDevice3");
		}
	}
	DirectComposition::~DirectComposition()
	{
		if (dll_dcomp)
		{
			FreeLibrary(dll_dcomp);
		}
		dll_dcomp = NULL;
		api_DCompositionCreateDevice = NULL;
		api_DCompositionCreateDevice2 = NULL;
		api_DCompositionCreateDevice3 = NULL;
	}
}

#include "Platform/RuntimeLoader/Direct2D1.hpp"

namespace Platform::RuntimeLoader
{
	HRESULT Direct2D1::CreateFactory(
		D2D1_FACTORY_TYPE factoryType,
		REFIID riid,
		void** ppIFactory)
	{
		if (api_D2D1CreateFactory)
		{
			D2D1_FACTORY_OPTIONS options = {
			#ifdef _DEBUG
				.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION
			#else
				.debugLevel = D2D1_DEBUG_LEVEL_NONE
			#endif
			};
			return api_D2D1CreateFactory(
				factoryType,
				riid,
				&options,
				ppIFactory);
		}
		return E_NOTIMPL;
	}
	HRESULT Direct2D1::CreateDevice(
		IDXGIDevice* dxgiDevice,
		BOOL multiThread,
		ID2D1Device** d2dDevice)
	{
		if (api_D2D1CreateDevice)
		{
			D2D1_CREATION_PROPERTIES prop = {
				.threadingMode = multiThread
					? D2D1_THREADING_MODE_MULTI_THREADED
					: D2D1_THREADING_MODE_SINGLE_THREADED,
			#ifdef _DEBUG
				.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION,
			#else
				.debugLevel = D2D1_DEBUG_LEVEL_NONE,
			#endif
				.options = multiThread
					? D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS
					: D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			};
			return api_D2D1CreateDevice(dxgiDevice, &prop, d2dDevice);
		}
		return E_NOTIMPL;
	}
	HRESULT Direct2D1::CreateDevice(
		IDXGIDevice* dxgiDevice,
		BOOL multiThread,
		ID2D1Device** d2dDevice,
		ID2D1DeviceContext** d2dDeviceContext)
	{
		if (api_D2D1CreateDevice)
		{
			D2D1_CREATION_PROPERTIES prop = {
				.threadingMode = multiThread
					? D2D1_THREADING_MODE_MULTI_THREADED
					: D2D1_THREADING_MODE_SINGLE_THREADED,
			#ifdef _DEBUG
				.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION,
			#else
				.debugLevel = D2D1_DEBUG_LEVEL_NONE,
			#endif
				.options = multiThread
					? D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS
					: D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			};
			HRESULT hr = api_D2D1CreateDevice(dxgiDevice, &prop, d2dDevice);
			if (FAILED(hr)) return hr;
			return (*d2dDevice)->CreateDeviceContext(
				multiThread
				? D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS
				: D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
				d2dDeviceContext);
		}
		return E_NOTIMPL;
	}

	Direct2D1::Direct2D1()
	{
		dll_d2d1 = LoadLibraryW(L"d2d1.dll");
		if (dll_d2d1)
		{
			api_D2D1CreateFactory = (decltype(api_D2D1CreateFactory))
				GetProcAddress(dll_d2d1, "D2D1CreateFactory");
			api_D2D1CreateDevice = (decltype(api_D2D1CreateDevice))
				GetProcAddress(dll_d2d1, "D2D1CreateDevice");
		}
	}
	Direct2D1::~Direct2D1()
	{
		if (dll_d2d1)
		{
			FreeLibrary(dll_d2d1);
		}
		dll_d2d1 = NULL;
		api_D2D1CreateFactory = NULL;
		api_D2D1CreateDevice = NULL;
	}
}

#include "Platform/RuntimeLoader/DirectWrite.hpp"

namespace Platform::RuntimeLoader
{
	HRESULT DirectWrite::CreateFactory(
		DWRITE_FACTORY_TYPE factoryType,
		REFIID iid,
		void** factory)
	{
		if (api_DWriteCreateFactory)
		{
			return api_DWriteCreateFactory(
				factoryType,
				iid,
				(IUnknown**)factory);
		}
		return E_NOTIMPL;
	}

	DirectWrite::DirectWrite()
	{
		dll_dwrite = LoadLibraryW(L"dwrite.dll");
		if (dll_dwrite)
		{
			api_DWriteCreateFactory = (decltype(api_DWriteCreateFactory))
				GetProcAddress(dll_dwrite, "DWriteCreateFactory");
		}
	}
	DirectWrite::~DirectWrite()
	{
		if (dll_dwrite)
		{
			FreeLibrary(dll_dwrite);
		}
		dll_dwrite = NULL;
		api_DWriteCreateFactory = NULL;
	}
}

#include "Platform/RuntimeLoader/DesktopWindowManager.hpp"

namespace Platform::RuntimeLoader
{
	HRESULT DesktopWindowManager::IsCompositionEnabled(BOOL* pfEnabled)
	{
		if (api_DwmIsCompositionEnabled)
		{
			return api_DwmIsCompositionEnabled(pfEnabled);
		}
		return E_NOTIMPL;
	}
	HRESULT DesktopWindowManager::EnableBlurBehindWindow(HWND hWnd, const DWM_BLURBEHIND* pBlurBehind)
	{
		if (api_DwmEnableBlurBehindWindow)
		{
			return api_DwmEnableBlurBehindWindow(hWnd, pBlurBehind);
		}
		return E_NOTIMPL;
	}
	HRESULT DesktopWindowManager::ExtendFrameIntoClientArea(HWND hWnd, const MARGINS* pMarInset)
	{
		if (api_DwmExtendFrameIntoClientArea)
		{
			return api_DwmExtendFrameIntoClientArea(hWnd, pMarInset);
		}
		return E_NOTIMPL;
	}
	HRESULT DesktopWindowManager::GetColorizationColor(DWORD* pcrColorization, BOOL* pfOpaqueBlend)
	{
		if (api_DwmGetColorizationColor)
		{
			return api_DwmGetColorizationColor(pcrColorization, pfOpaqueBlend);
		}
		return E_NOTIMPL;
	}
	BOOL DesktopWindowManager::DefWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult)
	{
		if (api_DwmDefWindowProc)
		{
			return api_DwmDefWindowProc(hWnd, msg, wParam, lParam, plResult);
		}
		return FALSE;
	}
	HRESULT DesktopWindowManager::SetWindowAttribute(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute)
	{
		if (api_DwmSetWindowAttribute)
		{
			return api_DwmSetWindowAttribute(hwnd, dwAttribute, pvAttribute, cbAttribute);
		}
		return E_NOTIMPL;
	}
	HRESULT DesktopWindowManager::Flush()
	{
		if (api_DwmFlush)
		{
			return api_DwmFlush();
		}
		return E_NOTIMPL;
	}

	BOOL DesktopWindowManager::IsWindowTransparencySupported()
	{
		// https://github.com/glfw/glfw/blob/master/src/win32_window.c

		if (!IsWindowsVistaOrGreater())
			return FALSE;

		BOOL composition = FALSE;
		if (FAILED(IsCompositionEnabled(&composition)) || !composition)
			return FALSE;

		if (!IsWindows8OrGreater())
		{
			// HACK: Disable framebuffer transparency on Windows 7 when the
			//       colorization color is opaque, because otherwise the window
			//       contents is blended additively with the previous frame instead
			//       of replacing it
			DWORD color = 0x00000000;
			BOOL opaque = FALSE;
			if (FAILED(GetColorizationColor(&color, &opaque)) || opaque)
				return FALSE;
		}

		return TRUE;
	}
	HRESULT DesktopWindowManager::SetWindowTransparency(HWND hWnd, BOOL bEnable)
	{
		if (bEnable && IsWindowTransparencySupported() && api_CreateRectRgn && api_DeleteObject)
		{
			HRGN region = api_CreateRectRgn(0, 0, -1, -1);
			DWM_BLURBEHIND bb = {};
			bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
			bb.fEnable = TRUE;
			bb.hRgnBlur = region;
			HRESULT const hr = EnableBlurBehindWindow(hWnd, &bb);
			api_DeleteObject(region);
			return hr;
		}
		else
		{
			DWM_BLURBEHIND bb = {};
			bb.dwFlags = DWM_BB_ENABLE;
			return EnableBlurBehindWindow(hWnd, &bb);
		}
	}

	DesktopWindowManager::DesktopWindowManager()
	{
		dll_dwmapi = LoadLibraryW(L"dwmapi.dll");
		dll_gdi32 = LoadLibraryW(L"gdi32.dll");
		assert(dll_dwmapi);
		assert(dll_gdi32);
		if (dll_dwmapi)
		{
			api_DwmIsCompositionEnabled = (decltype(api_DwmIsCompositionEnabled))
				GetProcAddress(dll_dwmapi, "DwmIsCompositionEnabled");
			api_DwmEnableBlurBehindWindow = (decltype(api_DwmEnableBlurBehindWindow))
				GetProcAddress(dll_dwmapi, "DwmEnableBlurBehindWindow");
			api_DwmExtendFrameIntoClientArea = (decltype(api_DwmExtendFrameIntoClientArea))
				GetProcAddress(dll_dwmapi, "DwmExtendFrameIntoClientArea");
			api_DwmGetColorizationColor = (decltype(api_DwmGetColorizationColor))
				GetProcAddress(dll_dwmapi, "DwmGetColorizationColor");
			api_DwmDefWindowProc = (decltype(api_DwmDefWindowProc))
				GetProcAddress(dll_dwmapi, "DwmDefWindowProc");
			api_DwmSetWindowAttribute = (decltype(api_DwmSetWindowAttribute))
				GetProcAddress(dll_dwmapi, "DwmSetWindowAttribute");
			api_DwmFlush = (decltype(api_DwmFlush))
				GetProcAddress(dll_dwmapi, "DwmFlush");
			assert(api_DwmIsCompositionEnabled);
			assert(api_DwmEnableBlurBehindWindow);
			assert(api_DwmExtendFrameIntoClientArea);
			assert(api_DwmGetColorizationColor);
			assert(api_DwmDefWindowProc);
			assert(api_DwmSetWindowAttribute);
			assert(api_DwmFlush);
		}
		if (dll_gdi32)
		{
			api_CreateRectRgn = (decltype(api_CreateRectRgn))
				GetProcAddress(dll_gdi32, "CreateRectRgn");
			api_DeleteObject = (decltype(api_DeleteObject))
				GetProcAddress(dll_gdi32, "DeleteObject");
			assert(api_CreateRectRgn);
			assert(api_DeleteObject);
		}
	}
	DesktopWindowManager::~DesktopWindowManager()
	{
		if (dll_dwmapi)
		{
			FreeLibrary(dll_dwmapi);
		}
		if (dll_gdi32)
		{
			FreeLibrary(dll_gdi32);
		}
		dll_dwmapi = NULL;
		dll_gdi32 = NULL;
		api_DwmIsCompositionEnabled = NULL;
		api_DwmEnableBlurBehindWindow = NULL;
		api_DwmExtendFrameIntoClientArea = NULL;
		api_DwmGetColorizationColor = NULL;
		api_DwmDefWindowProc = NULL;
		api_DwmSetWindowAttribute = NULL;
		api_DwmFlush = NULL;
		api_CreateRectRgn = NULL;
		api_DeleteObject = NULL;
	}
}
