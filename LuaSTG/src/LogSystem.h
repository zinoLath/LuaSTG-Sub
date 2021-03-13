﻿#pragma once
#include <string>
#include <fstream>

namespace LuaSTGPlus
{
	enum class LogType
	{
		Debug,
		Information,
		Warning,
		Error,
		Fatal,
	};
	
	class LogSystem
	{
	private:
		std::wstring m_LogFileName;
		std::ofstream m_LogFile;
	public:
		static LogSystem& GetInstance();
		void Log(LogType type, const wchar_t* info, ...) noexcept;
	public:
		LogSystem();
		~LogSystem();
	};
};
