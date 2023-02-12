﻿#include "LuaBinding/LuaWrapper.hpp"

////////////////////////////////////////////////////////////////////////////////
/// @brief WELL512随机数算法
/// @note  摘自《游戏编程精粹 7》
////////////////////////////////////////////////////////////////////////////////
class fcyRandomWELL512
{
private:
	uint32_t m_State[16];   ///< @brief 内部状态机
	uint32_t m_Index;       ///< @brief 下标
	uint32_t m_RSeed;       ///< @brief 随机数种子
public:
	/// @brief 获得随机数种子
	uint32_t GetRandSeed() const;
	/// @brief     设置随机数种子
	/// @param[in] Seed 随机数种子
	void SetSeed(uint32_t Seed);
	/// @brief 产生无符号整数
	uint32_t GetRandUInt();
	/// @brief     产生[0, Max]之间的无符号整数
	/// @param[in] Max 最大数
	uint32_t GetRandUInt(uint32_t Max);
	/// @brief 产生[0, 1]之间的随机小数
	float GetRandFloat();
	/// @brief 产生[MinBound, MaxBound]之间的随机小数
	/// @param[in] MinBound 下界
	/// @param[in] MaxBound 上界
	float GetRandFloat(float MinBound, float MaxBound);
public:
	/// @brief 默认构造函数
	/// @note  调用GetTickCount()进行初始化
	fcyRandomWELL512();
	/// @brief 指定种子初始化随机数发生器
	fcyRandomWELL512(uint32_t Seed);
	~fcyRandomWELL512();
};

fcyRandomWELL512::fcyRandomWELL512()
{
	SetSeed(clock());
}

fcyRandomWELL512::fcyRandomWELL512(uint32_t Seed)
{
	SetSeed(Seed);
}

fcyRandomWELL512::~fcyRandomWELL512()
{}

uint32_t fcyRandomWELL512::GetRandSeed() const
{
	return m_RSeed;
}

void fcyRandomWELL512::SetSeed(uint32_t Seed)
{
	m_RSeed = Seed;

	m_Index = 0;

	// 线性同余产生种子
	const unsigned int mask = ~0u;
	m_State[0] = Seed & mask;
	for (unsigned int i = 1; i < 16; ++i)
	{
		m_State[i] = (1812433253UL * (m_State[i - 1] ^ (m_State[i - 1] >> 30)) + i) & mask;
	}
}

uint32_t fcyRandomWELL512::GetRandUInt()
{
	unsigned int a, b, c, d;
	a = m_State[m_Index];
	c = m_State[(m_Index + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = m_State[(m_Index + 9) & 15];
	c ^= (c >> 11);
	a = m_State[m_Index] = b ^ c;
	d = a ^ ((a << 5) & 0xDA442D24UL);
	m_Index = (m_Index + 15) & 15;
	a = m_State[m_Index];
	m_State[m_Index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
	return m_State[m_Index];
}

uint32_t fcyRandomWELL512::GetRandUInt(uint32_t Max)
{
	return GetRandUInt() % (Max + 1);
}

float fcyRandomWELL512::GetRandFloat()
{
	return GetRandUInt(1000000) / 1000000.f;
}

float fcyRandomWELL512::GetRandFloat(float MinBound, float MaxBound)
{
	return GetRandFloat() * (MaxBound - MinBound) + MinBound;
}

namespace LuaSTGPlus::LuaWrapper
{
	template<typename T>
	inline void make_less(T& a, T& b)
	{
		if (a > b)
		{
			std::swap(a, b);
		}
	}

	void RandomizerWrapper::Register(lua_State* L)noexcept
	{
		struct Function
		{
		#define GETUDATA(p, i) fcyRandomWELL512* (p) = static_cast<fcyRandomWELL512*>(luaL_checkudata(L, (i), LUASTG_LUA_TYPENAME_RANDGEN));
			static int Seed(lua_State* L)noexcept
			{
				GETUDATA(p, 1);
				p->SetSeed((uint32_t)luaL_checkinteger(L, 2));
				return 0;
			}
			static int GetSeed(lua_State* L)noexcept
			{
				GETUDATA(p, 1);
				lua_pushinteger(L, (lua_Integer)p->GetRandSeed());
				return 1;
			}
			static int Int(lua_State* L)noexcept
			{
				GETUDATA(p, 1);
				lua_Integer a = luaL_checkinteger(L, 2);
				lua_Integer b = luaL_checkinteger(L, 3);
				make_less(a, b);
				lua_Integer ret = (lua_Integer)p->GetRandUInt((std::max)(static_cast<uint32_t>(b - a), 0U));
				lua_pushinteger(L, a + ret);
				return 1;
			}
			static int Float(lua_State* L)noexcept
			{
				GETUDATA(p, 1);
				float a = (float)luaL_checknumber(L, 2);
				float b = (float)luaL_checknumber(L, 3);
				make_less(a, b);
				lua_pushnumber(L, (lua_Number)p->GetRandFloat(a, b));
				return 1;
			}
			static int Sign(lua_State* L)noexcept
			{
				GETUDATA(p, 1);
				lua_pushinteger(L, (lua_Integer)p->GetRandUInt(1) * 2 - 1);
				return 1;
			}
			static int Meta_ToString(lua_State* L)noexcept
			{
				lua_pushfstring(L, LUASTG_LUA_TYPENAME_RANDGEN);
				return 1;
			}
		#undef GETUDATA
		};

		luaL_Reg tMethods[] =
		{
			{ "Seed", &Function::Seed },
			{ "GetSeed", &Function::GetSeed },
			{ "Int", &Function::Int },
			{ "Float", &Function::Float },
			{ "Sign", &Function::Sign },
			{ NULL, NULL }
		};

		luaL_Reg tMetaTable[] =
		{
			{ "__tostring", &Function::Meta_ToString },
			{ NULL, NULL }
		};

		RegisterClassIntoTable(L, ".Rand", tMethods, LUASTG_LUA_TYPENAME_RANDGEN, tMetaTable);
	}

	void RandomizerWrapper::CreateAndPush(lua_State* L)
	{
		fcyRandomWELL512* p = static_cast<fcyRandomWELL512*>(lua_newuserdata(L, sizeof(fcyRandomWELL512))); // udata
		new(p) fcyRandomWELL512();
		luaL_getmetatable(L, LUASTG_LUA_TYPENAME_RANDGEN); // udata mt
		lua_setmetatable(L, -2); // udata
	}
}
