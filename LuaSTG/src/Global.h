﻿/// @file Global.h
/// @brief 全局定义文件
#pragma once

// 版本控制
//#define LDEVVERSION

// CRTDBG
#include <crtdbg.h>

// C
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

// STL
#include <functional>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <regex>
#include <array>
#include <limits>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

// fancy2d
#include <fcyIO/fcyStream.h>
#include <fcyIO/fcyBinaryHelper.h>
#include <fcyParser/fcyPathParser.h>
#include <fcyParser/fcyIni.h>
#include <fcyMisc/fcyStopWatch.h>
#include <fcyMisc/fcyStringHelper.h>
#include <fcyMisc/fcyRandom.h>
#include <fcyOS/fcyMemPool.h>
#include <f2d.h>

// luajit
#include <lua.hpp>

// 日志系统
#include "LogSystem.h"

// 配置文件
#include "Config.h"

// 一些全局范围的宏
#define LVERSION L"luaSTG v0.10.1"
#define LVERSION_LUA LUAJIT_VERSION

// 全局文件
#define LLOGFILE L"log.txt"

// CLASS中存放的回调函数的下标
#define LGOBJ_CC_INIT 1
#define LGOBJ_CC_DEL 2
#define LGOBJ_CC_FRAME 3
#define LGOBJ_CC_RENDER 4
#define LGOBJ_CC_COLLI 5
#define LGOBJ_CC_KILL 6

// 数学常量
#define DBL_HALF_MAX (DBL_MAX / 2.0) //双精度浮点的半大值
#define LRAD2DEGREE (180.0/3.141592653589793) // 弧度到角度
#define LDEGREE2RAD (1.0/LRAD2DEGREE) // 角度到弧度
#define LPI_FULL (3.1415926535897932384626433832795) // PI
#define LPI_HALF (LPI_FULL / 2)  // PI*0.5

#define LNOEXCEPT noexcept // throw()
#define LNOINLINE __declspec(noinline)
#define LNOUSE(x) static_cast<void>(x)

#define LAPP (LuaSTGPlus::AppFrame::GetInstance())
#define LLOGGER (LuaSTGPlus::LogSystem::GetInstance())
#define LPOOL (LAPP.GetGameObjectPool())
#define LRES (LAPP.GetResourceMgr())
#define LFMGR (LAPP.GetFileManager())

#define LSOUNDGLOBALFOCUS  true

// 调试辅助
#ifdef _DEBUG
#define LDEBUG
#endif

// #define LSHOWFONTBASELINE  // 显示文字基线
#define LPERFORMANCEUPDATETIMER 0.25f  // 刷新一次计数器（间隔：秒）

#define LWIDE_(x) L ## x
#define LWIDE(x) LWIDE_(x)
#define LERROR(info, ...) LLOGGER.Log(LuaSTGPlus::LogType::Error, L##info, __VA_ARGS__)
#define LWARNING(info, ...) LLOGGER.Log(LuaSTGPlus::LogType::Warning, L##info, __VA_ARGS__)
#define LINFO(info, ...) LLOGGER.Log(LuaSTGPlus::LogType::Information, L##info, __VA_ARGS__)

#ifdef LDEBUG
#define LASSERT(cond) \
	if (!(cond)) \
	{ \
		LERROR("调试断言失败 于文件 '%s' 函数 '%s' 行 %d: %s", LWIDE(__FILE__), LWIDE(__FUNCTION__), __LINE__, L#cond); \
		_wassert(L#cond, LWIDE(__FILE__), __LINE__); \
	}
#else
#define LASSERT(cond)
#endif

namespace LuaSTGPlus
{
	class AppFrame;
}
