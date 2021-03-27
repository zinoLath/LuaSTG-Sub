#include "Graphic/Device.h"
#include <string>
#include <Windows.h>
#include <VersionHelpers.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <d3d11_4.h>

namespace slow::Graphic
{
    using f_CreateDXGIFactory1 = HRESULT (WINAPI *)(
        REFIID riid,
        void** ppFactory
    );
    using f_D3D11CreateDevice = HRESULT (WINAPI *)(
        IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE DriverType,
        HMODULE Software,
        UINT Flags,
        CONST D3D_FEATURE_LEVEL* pFeatureLevels,
        UINT FeatureLevels,
        UINT SDKVersion,
        ID3D11Device** ppDevice,
        D3D_FEATURE_LEVEL* pFeatureLevel,
        ID3D11DeviceContext** ppImmediateContext
    );
}

namespace slow::Graphic
{
    using Microsoft::WRL::ComPtr;
    
    struct Device::Implement
    {
        // window
        HWND                           window             = NULL;
        // dll
        HMODULE                        dxgi               = NULL;
        HMODULE                        d3d11              = NULL;
        f_CreateDXGIFactory1           CreateDXGIFactory1 = NULL;
        f_D3D11CreateDevice            D3D11CreateDevice  = NULL;
        // DXGI
        ComPtr<IDXGIFactory1>          dxgiFactory1;
        ComPtr<IDXGIFactory2>          dxgiFactory2;
        ComPtr<IDXGISwapChain>         dxgiSwapChain;
        ComPtr<IDXGISwapChain1>        dxgiSwapChain1;
        // Direct3D11
        ComPtr<ID3D11Device>           d3d11Device;
        ComPtr<ID3D11Device1>          d3d11Device1;
        ComPtr<ID3D11DeviceContext>    d3d11DeviceContext;
        ComPtr<ID3D11DeviceContext1>   d3d11DeviceContext1;
        ComPtr<ID3D11RenderTargetView> d3d11BackBuffer;
        ComPtr<ID3D11DepthStencilView> d3d11DepthStencil;
    };
    
    #define self (*implememt)
    
    handle_t Device::getDeviceHandle()
    {
        return (handle_t)self.d3d11Device.Get();
    };
    
    bool Device::autoResizeSwapChain()
    {
        // check
        if (!self.dxgiSwapChain)
        {
            return false;
        }
        
        // get window size
        RECT rect_ = {};
        if (FALSE == ::GetClientRect(self.window, &rect_))
        {
            return false;
        }
        UINT new_width_ = rect_.right - rect_.left;
        UINT new_height_ = rect_.bottom - rect_.top;
        new_width_ = (new_width_ > 0) ? new_width_ : 1;
        new_height_ = (new_height_ > 0) ? new_height_ : 1;
        
        HRESULT hr = 0;
        
        // get size
        UINT old_width_ = 0;
        UINT old_height_ = 0;
        if (self.dxgiSwapChain1)
        {
            DXGI_SWAP_CHAIN_DESC1 lastinfo_ = {};
            hr = self.dxgiSwapChain1->GetDesc1(&lastinfo_);
            if (hr != S_OK)
            {
                return false;
            }
            old_width_ = lastinfo_.Width;
            old_height_ = lastinfo_.Height;
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC lastinfo_ = {};
            hr = self.dxgiSwapChain->GetDesc(&lastinfo_);
            if (hr != S_OK)
            {
                return false;
            }
            old_width_ = lastinfo_.BufferDesc.Width;
            old_height_ = lastinfo_.BufferDesc.Height;
        }
        
        // resize
        if (new_width_ != old_width_ || new_height_ != old_height_)
        {
            return resizeSwapChain(new_width_, new_height_);
        }
        
        return true;
    };
    bool Device::resizeSwapChain(uint32_t width, uint32_t height)
    {
        // check
        if (width == 0 || height == 0)
        {
            return false;
        }
        if (!self.dxgiSwapChain)
        {
            return false;
        }
        
        // clear
        if (self.d3d11DeviceContext)
        {
            self.d3d11DeviceContext->ClearState();
        }
        self.d3d11BackBuffer.Reset();
        self.d3d11DepthStencil.Reset();
        
        HRESULT hr = 0;
        
        // resize
        if (self.dxgiSwapChain1)
        {
            DXGI_SWAP_CHAIN_DESC1 lastinfo_ = {};
            hr = self.dxgiSwapChain1->GetDesc1(&lastinfo_);
            if (hr != S_OK)
            {
                return false;
            }
            hr = self.dxgiSwapChain1->ResizeBuffers(lastinfo_.BufferCount, width, height, lastinfo_.Format, lastinfo_.Flags);
            if (hr != S_OK)
            {
                return false;
            }
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC lastinfo_ = {};
            hr = self.dxgiSwapChain->GetDesc(&lastinfo_);
            if (hr != S_OK)
            {
                return false;
            }
            hr = self.dxgiSwapChain->ResizeBuffers(lastinfo_.BufferCount, width, height, lastinfo_.BufferDesc.Format, lastinfo_.Flags);
            if (hr != S_OK)
            {
                return false;
            }
        }
        
        // create backbuffer
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer_;
        hr = self.dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(backbuffer_.GetAddressOf()));
        if (hr != S_OK)
        {
            return false;
        }
        hr = self.d3d11Device->CreateRenderTargetView(backbuffer_.Get(), NULL, self.d3d11BackBuffer.GetAddressOf());
        if (hr != S_OK)
        {
            return false;
        }
        
        // create depth stencil
        Microsoft::WRL::ComPtr<ID3D11Texture2D> dsbuffer_;
        D3D11_TEXTURE2D_DESC dsinfo_ = {}; {
            dsinfo_.Width = width;
            dsinfo_.Height = height;
            dsinfo_.MipLevels = 1;
            dsinfo_.ArraySize = 1;
            dsinfo_.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
            dsinfo_.SampleDesc.Count = 1;
            dsinfo_.SampleDesc.Quality = 0;
            dsinfo_.Usage = D3D11_USAGE_DEFAULT;
            dsinfo_.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            dsinfo_.CPUAccessFlags = 0;
            dsinfo_.MiscFlags = 0;
        };
        hr = self.d3d11Device->CreateTexture2D(&dsinfo_, NULL, dsbuffer_.GetAddressOf());
        if (hr != S_OK)
        {
            return false;
        }
        hr = self.d3d11Device->CreateDepthStencilView(dsbuffer_.Get(), NULL, self.d3d11DepthStencil.GetAddressOf());
        if (hr != S_OK)
        {
            return false;
        }
        
        return true;
    };
    void Device::setSwapChain()
    {
        if (self.d3d11DeviceContext)
        {
            ID3D11RenderTargetView* const rts_[1] = { self.d3d11BackBuffer.Get() };
            self.d3d11DeviceContext->OMSetRenderTargets(1, rts_, self.d3d11DepthStencil.Get());
        }
    };
    void Device::clearRenderTarget(float r, float g, float b, float a)
    {
        if (self.d3d11DeviceContext)
        {
            ID3D11RenderTargetView* rts_[1] = { NULL };
            self.d3d11DeviceContext->OMGetRenderTargets(1, rts_, NULL);
            if (rts_[0])
            {
                const FLOAT color_[4] = { r, g, b, a };
                self.d3d11DeviceContext->ClearRenderTargetView(rts_[0], color_);
                rts_[0]->Release();
            }
        }
    }
    void Device::clearDepthBuffer(float depth, uint8_t stencil)
    {
        if (self.d3d11DeviceContext)
        {
            ID3D11DepthStencilView* ds_ = NULL;
            self.d3d11DeviceContext->OMGetRenderTargets(0, NULL, &ds_);
            if (ds_)
            {
                self.d3d11DeviceContext->ClearDepthStencilView(ds_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
                ds_->Release();
            }
        }
    }
    bool Device::updateSwapChain(bool vsync)
    {
        HRESULT hr = 0;
        
        if (self.dxgiSwapChain)
        {
            hr = self.dxgiSwapChain->Present(vsync ? 1 : 0, 0);
            if (hr != S_OK)
            {
                return false;
            }
        }
        else
        {
            // no swap chain
            return false;
        }
        
        return true;
    };
    
    bool Device::bind(handle_t window)
    {
        unbind();
        
        // setup window
        self.window = (HWND)window;
        
        // load module
        self.dxgi = ::LoadLibraryW(L"dxgi.dll");
        self.d3d11 = ::LoadLibraryW(L"d3d11.dll");
        if (self.dxgi == NULL || self.d3d11 == NULL)
        {
            return false;
        }
        self.CreateDXGIFactory1 = (f_CreateDXGIFactory1)::GetProcAddress(self.dxgi, "CreateDXGIFactory1");
        self.D3D11CreateDevice = (f_D3D11CreateDevice)::GetProcAddress(self.d3d11, "D3D11CreateDevice");
        if (self.CreateDXGIFactory1 == NULL || self.D3D11CreateDevice == NULL)
        {
            return false;
        }
        
        HRESULT hr = 0;
        
        // create dxgi
        hr = self.CreateDXGIFactory1(IID_PPV_ARGS(self.dxgiFactory1.GetAddressOf()));
        if (hr != S_OK)
        {
            return false;
        }
        self.dxgiFactory1.As(&self.dxgiFactory2);
        ComPtr<IDXGIAdapter1> dxgiAdapter1_;
        ComPtr<IDXGIFactory6> dxgiFactory6_;
        self.dxgiFactory1.As(&dxgiFactory6_);
        if (dxgiFactory6_)
        {
            dxgiFactory6_->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(dxgiAdapter1_.GetAddressOf()));
        }
        if (!dxgiAdapter1_)
        {
            hr = self.dxgiFactory1->EnumAdapters1(0, dxgiAdapter1_.GetAddressOf());
            if (hr != S_OK)
            {
                return false;
            }
        }
        if (true)
        {
            DXGI_ADAPTER_DESC1 desc_ = {};
            hr = dxgiAdapter1_->GetDesc1(&desc_);
            std::wstring msg = L"current adapter: ";
                        msg += desc_.Description;
                        msg += L"\n";
            ::OutputDebugStringW(msg.c_str());
        }
        
        // create d3d11
        UINT d3d11Flags_ = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        #ifdef _DEBUG
        d3d11Flags_ |= D3D11_CREATE_DEVICE_DEBUG;
        #endif
        const D3D_FEATURE_LEVEL target_levels_[4] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };
        D3D_FEATURE_LEVEL feature_level_ = D3D_FEATURE_LEVEL_9_1;
        hr = self.D3D11CreateDevice(
            dxgiAdapter1_.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL,
            d3d11Flags_, target_levels_, 4, D3D11_SDK_VERSION,
            self.d3d11Device.GetAddressOf(), &feature_level_, self.d3d11DeviceContext.GetAddressOf());
        if (hr != S_OK)
        {
            hr = self.D3D11CreateDevice(
                dxgiAdapter1_.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL,
                d3d11Flags_, target_levels_ + 1, 3, D3D11_SDK_VERSION,
                self.d3d11Device.GetAddressOf(), &feature_level_, self.d3d11DeviceContext.GetAddressOf());
            if (hr != S_OK)
            {
                return false;
            }
        }
        self.d3d11Device.As(&self.d3d11Device1);
        self.d3d11DeviceContext.As(&self.d3d11DeviceContext1);
        
        // create swapchain
        if (self.dxgiFactory2 && self.d3d11Device1 && self.d3d11DeviceContext1)
        {
            DXGI_SWAP_CHAIN_DESC1 scinfo_ = {}; {
                scinfo_.Width = 1;
                scinfo_.Height = 1;
                scinfo_.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                scinfo_.Stereo = FALSE;
                scinfo_.SampleDesc.Count = 1;
                scinfo_.SampleDesc.Quality = 0;
                scinfo_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                scinfo_.BufferCount = 2;
                scinfo_.Scaling = DXGI_SCALING_STRETCH;
                scinfo_.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                scinfo_.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
                scinfo_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
                //scinfo_.Flags |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
                //scinfo_.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
            };
            hr = self.dxgiFactory2->CreateSwapChainForHwnd(self.d3d11Device1.Get(), self.window, &scinfo_, NULL, NULL, self.dxgiSwapChain1.GetAddressOf());
            if (hr == S_OK)
            {
                hr = self.dxgiSwapChain1.As(&self.dxgiSwapChain);
                if (hr != S_OK)
                {
                    self.dxgiSwapChain1.Reset(); // error?
                }
            }
        }
        if (!self.dxgiSwapChain)
        {
            DXGI_SWAP_CHAIN_DESC scinfo_ = {}; {
                scinfo_.BufferDesc.Width = 1;
                scinfo_.BufferDesc.Height = 1;
                scinfo_.BufferDesc.RefreshRate.Numerator = 0;
                scinfo_.BufferDesc.RefreshRate.Denominator = 1;
                scinfo_.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                scinfo_.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
                scinfo_.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
                scinfo_.SampleDesc.Count = 1;
                scinfo_.SampleDesc.Quality = 0;
                scinfo_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                scinfo_.BufferCount = 2;
                scinfo_.OutputWindow = self.window;
                scinfo_.Windowed = TRUE;
                scinfo_.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                scinfo_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
            };
            hr = self.dxgiFactory1->CreateSwapChain(self.d3d11Device.Get(), &scinfo_, self.dxgiSwapChain.GetAddressOf());
            if (hr != S_OK)
            {
                return false;
            }
        }
        
        return true;
    };
    void Device::unbind()
    {
        // destroy swapchain
        if (self.d3d11DeviceContext)
        {
            self.d3d11DeviceContext->ClearState();
        }
        self.d3d11BackBuffer.Reset();
        self.dxgiSwapChain.Reset();
        self.dxgiSwapChain1.Reset();
        
        // destroy dx
        self.dxgiFactory1.Reset();
        self.dxgiFactory2.Reset();
        self.d3d11Device.Reset();
        self.d3d11Device1.Reset();
        self.d3d11DeviceContext.Reset();
        self.d3d11DeviceContext1.Reset();
        self.d3d11DepthStencil.Reset();
        
        // dll
        if (self.dxgi) ::FreeLibrary(self.dxgi);
        if (self.d3d11) ::FreeLibrary(self.d3d11);
        self.dxgi = NULL;
        self.d3d11 = NULL;
        self.CreateDXGIFactory1 = NULL;
        self.D3D11CreateDevice = NULL;
        
        // window
        self.window = NULL;
    };
    bool Device::validate()
    {
        if (!self.d3d11Device || !self.d3d11DeviceContext || !self.dxgiSwapChain)
        {
            return false;
        }
        return true;
    };
    
    Device::Device()
    {
        implememt = new Implement;
    };
    Device::~Device()
    {
        unbind();
        delete implememt;
    };
    Device& Device::get()
    {
        static Device instance;
        return instance;
    };
};
