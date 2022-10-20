﻿#pragma once
#include "Core/ApplicationModel.hpp"
#include "Core/Graphics/Font.hpp"
#include "GameResource/ResourceMgr.h"
#include "GameObject/GameObjectPool.h"
#include "platform/DirectInput.hpp"

namespace LuaSTGPlus
{
	/// @brief 应用程序状态
	enum class AppStatus
	{
		NotInitialized,
		Initializing,
		Initialized,
		Running,
		Aborted,
		Destroyed,
	};

	enum class DisplaySettingType
	{
		Window, // 窗口
		Fullscreen, // 全屏无边框窗口
		ExclusiveFullscreen, // ExclusiveFullscreen
	};

	struct WindowSetting
	{
		// 窗口、交换链大小
		Core::Vector2I window_size{ 640, 480 };
		// 所在显示器矩形
		Core::RectI monitor_rect{};
		// 垂直同步
		bool vsync{ false };
		// 无边框模式
		bool borderless{ false };
		// 交换链快速交换模式
		bool swapchain_flip{ false };
		// 低延迟呈现
		bool swapchain_low_latency{ false };
	};

	struct FullscreenSetting
	{
		// 窗口大小，一定等于 monitor_rect 的大小
		Core::Vector2I window_size{ 640, 480 };
		// 所在显示器矩形
		Core::RectI monitor_rect{};
		// 垂直同步
		bool vsync{ false };
		// 交换链快速交换模式
		bool swapchain_flip{ false };
		// 低延迟呈现
		bool swapchain_low_latency{ false };
	};

	struct ExclusiveFullscreenSetting
	{
		// 窗口、交换链大小
		Core::Vector2I window_size{ 640, 480 };
		// 刷新率
		Core::Rational refresh_rate{};
		// 垂直同步
		bool vsync{ false };
	};

	struct ApplicationSetting
	{
		// 图形设备
		std::string preferred_gpu;

		// 显示模式
		DisplaySettingType display_setting_type{ DisplaySettingType::Window };
		// 显示模式 - 窗口
		WindowSetting window;
		// 显示模式 - 全屏无边框窗口
		FullscreenSetting fullscreen;
		// 显示模式 - 独占全屏
		ExclusiveFullscreenSetting exclusive_fullscreen;

		// 鼠标指针
		bool show_cursor{ true };

		// 目标帧率
		uint32_t target_fps{ 60 };

		// 窗口标题
		std::string window_title{ LUASTG_INFO };

		// 音量：音效
		float volume_sound_effect{ 1.0f };
		// 音量：背景音乐
		float volume_music{ 1.0f };

		// 内部状态
		DisplaySettingType toggle_between_fullscreen_type{ DisplaySettingType::Window };
	};

	/// @brief 应用程序框架
	class AppFrame
		: public Core::IApplicationEventListener
		, public Core::Graphics::IWindowEventListener
	{
	private:
		AppStatus m_iStatus = AppStatus::NotInitialized;
		
		// 应用程序框架
		Core::ScopeObject<Core::IApplicationModel> m_pAppModel;
		Core::ScopeObject<Core::Graphics::ITextRenderer> m_pTextRenderer;

		// 资源管理器
		ResourceMgr m_ResourceMgr;
		
		// 对象池
		std::unique_ptr<GameObjectPool> m_GameObjectPool;
		
		// Lua虚拟机
		lua_State* L = nullptr;
		
		// 选项
		ApplicationSetting m_Setting;

		// 测量值
		double m_fFPS = 0.;
		double m_fAvgFPS = 0.;

		// 渲染状态
		bool m_bRenderStarted = false;
		
		// 渲染目标栈
		std::vector<fcyRefPointer<ResTexture>> m_stRenderTargetStack;
		
		// 输入设备
		std::unique_ptr<platform::DirectInput> m_DirectInput;
		
	public:
		/// @brief 保护模式执行脚本
		/// @note 该函数仅限框架调用，为主逻辑最外层调用。若脚本运行时发生错误，该函数负责截获错误发出错误消息。
		bool SafeCallScript(const char* source, size_t len, const char* desc)noexcept;
		
		/// @brief 不保护调用全局函数
		/// @note 该函数仅限框架调用，为主逻辑最外层调用
		bool UnsafeCallGlobalFunction(const char* name, int retc = 0)noexcept;
		
		/// @brief 保护模式调用全局函数
		/// @note 该函数仅限框架调用，为主逻辑最外层调用。若脚本运行时发生错误，该函数负责截获错误发出错误消息。调用者负责维持栈平衡。
		bool SafeCallGlobalFunction(const char* name, int retc = 0)noexcept;
		
		/// @brief 保护模式调用全局函数
		/// @note 该函数仅限框架调用，为主逻辑最外层调用。若脚本运行时发生错误，该函数负责截获错误发出错误消息。调用者负责维持栈平衡。
		bool SafeCallGlobalFunctionB(const char* name, int argc = 0, int retc = 0)noexcept;
		
		/// @brief 执行资源包中的文件
		/// @note 该函数为脚本系统使用
		void LoadScript(const char* path,const char *packname)noexcept;
		
		bool OnOpenLuaEngine();
		bool OnLoadLaunchScriptAndFiles();
		bool OnLoadMainScriptAndFiles();
		
	public:  // 输入系统接口

		void OpenInput();
		void CloseInput();
		void UpdateInput();
		bool WantSwitchFullScreenMode();
		void ResetKeyboardInput();
		void ResetMouseInput();

		//检查按键是否按下
		bool GetKeyState(int VKCode)noexcept;
		
		/// @brief 获得最后一次按键输入
		int GetLastKey()noexcept;
		
		/// @brief 获取鼠标位置（以窗口左下角为原点）
		Core::Vector2F GetMousePosition(bool no_flip = false)noexcept;
		
		/// @brief 获取鼠标滚轮增量
		int32_t GetMouseWheelDelta()noexcept;
		
		/// @brief 检查鼠标是否按下
		bool GetMouseState_legacy(int button) noexcept;
		bool GetMouseState(int button) noexcept;
		
	public: // 脚本调用接口，含义参见API文档

		void SetTitle(const char* v) noexcept;
		void SetPreferenceGPU(const char* v) noexcept;
		void SetSplash(bool v) noexcept;
		void SetSEVolume(float v);
		void SetBGMVolume(float v);
		float GetSEVolume() const noexcept { return m_Setting.volume_sound_effect; }
		float GetBGMVolume() const noexcept { return m_Setting.volume_music; }
		
	public: // 窗口和交换链

		// 以窗口模式显示  
		// 当 monitor_rect 为空矩形时，窗口自动挑选最近的显示器来居中，否则根据显示器矩形选择匹配的显示器居中  
		bool SetDisplayModeWindow(Core::Vector2I window_size, bool vsync, Core::RectI monitor_rect, bool borderless, bool swapchain_flip, bool swapchain_low_latency);

		// 以全屏无边框窗口显示  
		bool SetDisplayModeFullscreen(Core::RectI monitor_rect, bool vsync, bool swapchain_flip, bool swapchain_low_latency);

		// 以独占全屏显示  
		// 当 refresh_rate 为全 0 时，自动选择合适的匹配的刷新率  
		bool SetDisplayModeExclusiveFullscreen(Core::Vector2I window_size, bool vsync, Core::Rational refresh_rate);

		// 获取当前的窗口大小
		Core::Vector2I GetCurrentWindowSize();

		// 更新显示模式
		bool UpdateDisplayMode();

		// 根据上一次设置的显示模式，通过 Ctrl+Enter 快捷键切换独占全屏
		bool ToggleBetweenFullscreen();

		bool InitializationApplySettingStage1();

		bool InitializationApplySettingStage2();

		void SetWindowed(bool v);

		void SetVsync(bool v);

		void SetResolution(uint32_t width, uint32_t height, uint32_t A = 0, uint32_t B = 0);

	public: // 其他框架方法
		
		// 设置目标 FPS
		void SetFPS(uint32_t v) noexcept;
		
		// 获取当前平均 FPS
		double GetFPS() const noexcept { return m_fAvgFPS; }
		
		// 读取资源包中的文本文件
		// 也能读取其他类型的文件，但是会得到无意义的结果
		int LoadTextFile(lua_State* L, const char* path, const char *packname) noexcept;
		
	public: // 渲染器接口
		
		// 应用混合模式
		void updateGraph2DBlendMode(BlendMode m);

		/// @brief 渲染图像
		bool Render(ResSprite* p, float x, float y, float rot = 0, float hscale = 1, float vscale = 1, float z = 0.5)noexcept;
		
		/// @brief 渲染动画
		bool Render(ResAnimation* p, int ani_timer, float x, float y, float rot = 0, float hscale = 1, float vscale = 1)noexcept;
		
		/// @brief 渲染粒子
		bool Render(ResParticle::ParticlePool* p, float hscale = 1, float vscale = 1)noexcept;
		
		/// @brief 渲染图像
		bool Render(const char* name, float x, float y, float rot = 0, float hscale = 1, float vscale = 1, float z = 0.5)noexcept;
		
		/// @brief 渲染动画
		bool RenderAnimation(const char* name, int timer, float x, float y, float rot = 0, float hscale = 1, float vscale = 1)noexcept;
		
		/// @brief 渲染纹理（注：UV 坐标会被归一化）
		bool RenderTexture(ResTexture* tex, BlendMode blend, const Core::Graphics::IRenderer::DrawVertex vertex[])noexcept;
		
		/// @brief 渲染纹理（注：UV 坐标会被归一化）
		bool RenderTexture(const char* name, BlendMode blend, Core::Graphics::IRenderer::DrawVertex vertex[])noexcept;
		
		/// @brief 渲染文字
		bool RenderText(ResFont* p, wchar_t* strBuf, Core::RectF rect, Core::Vector2F scale, ResFont::FontAlignHorizontal halign, ResFont::FontAlignVertical valign, bool bWordBreak)noexcept;
		
		Core::Vector2F CalcuTextSize(ResFont* p, const wchar_t* strBuf, Core::Vector2F scale)noexcept;
		
		bool RenderText(const char* name, const char* str, float x, float y, float scale, ResFont::FontAlignHorizontal halign, ResFont::FontAlignVertical valign)noexcept;
		
		bool RenderTTF(const char* name, const char* str, float left, float right, float bottom, float top, float scale, int format, Core::Color4B c)noexcept;

		void SnapShot(const char* path)noexcept;
		void SaveTexture(const char* tex_name, const char* path)noexcept;

		bool CheckRenderTargetInUse(ResTexture* rt)noexcept;
		bool PushRenderTarget(ResTexture* rt)noexcept;
		bool PopRenderTarget()noexcept;
		Core::Vector2U GetCurrentRenderTargetSize();

		void DebugSetGeometryRenderState();
		void DebugDrawCircle(float x, float y, float r, Core::Color4B color);
		void DebugDrawRect(float x, float y, float a, float b, float rot, Core::Color4B color);
		void DebugDrawEllipse(float x, float y, float a, float b, float rot, Core::Color4B color);

	public:
		// 文字渲染器包装
		bool FontRenderer_SetFontProvider(const char* name);
		void FontRenderer_SetScale(const Core::Vector2F& s);
		
		Core::RectF FontRenderer_MeasureTextBoundary(const char* str, size_t len);
		Core::Vector2F FontRenderer_MeasureTextAdvance(const char* str, size_t len);
		bool FontRenderer_RenderText(const char* str, size_t len, Core::Vector2F& pos, float z, BlendMode blend, Core::Color4B const& color);
		bool FontRenderer_RenderTextInSpace(const char* str, size_t len, Core::Vector3F& pos, Core::Vector3F const& rvec, Core::Vector3F const& dvec, BlendMode blend, Core::Color4B const& color);
		
		float FontRenderer_GetFontLineHeight();
		float FontRenderer_GetFontAscender();
		float FontRenderer_GetFontDescender();
		
	public:
		// 获取框架对象
		lua_State* GetLuaEngine()noexcept { return L; }

		ResourceMgr& GetResourceMgr()noexcept { return m_ResourceMgr; }

		GameObjectPool& GetGameObjectPool()noexcept{ return *m_GameObjectPool; }

		platform::DirectInput* GetDInput()noexcept { return m_DirectInput.get(); }
		
		Core::IApplicationModel* GetAppModel() { return m_pAppModel.get(); }
		Core::Graphics::IRenderer* GetRenderer2D() { return m_pAppModel->getRenderer(); }

	public:
		/// @brief 初始化框架
		/// @note 该函数必须在一开始被调用，且仅能调用一次
		/// @return 失败返回false
		bool Init()noexcept;
		/// @brief 终止框架并回收资源
		/// @note 该函数可以由框架自行调用，且仅能调用一次
		void Shutdown()noexcept;
		
		/// @brief 执行框架，进入游戏循环
		void Run()noexcept;
		
	protected:
		std::atomic_int m_window_active_changed{ 0 };

		void onWindowCreate() override;
		void onWindowDestroy() override;
		void onWindowActive() override;
		void onWindowInactive() override;
		void onDeviceChange() override;

		void onUpdate() override;
		void onRender() override;
	public:
		AppFrame()noexcept;
		~AppFrame()noexcept;
	public:
		static AppFrame& GetInstance();
	};
}

#define LAPP (LuaSTGPlus::AppFrame::GetInstance())
#define LPOOL (LAPP.GetGameObjectPool())
#define LRES (LAPP.GetResourceMgr())
