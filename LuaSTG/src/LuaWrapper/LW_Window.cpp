#include "AppFrame.h"
#include "LuaWrapper.hpp"

#ifdef LAPP
#undef LAPP
#endif
#define LAPP() (LuaSTGPlus::AppFrame::GetInstance())
#define LWIN() (LuaSTGPlus::AppFrame::GetInstance().GetWindow())

#define getwindow(__NAME__)\
    f2dWindow* __NAME__ = LuaSTGPlus::AppFrame::GetInstance().GetWindow();\
    if (!__NAME__) { return luaL_error(L, "lstg.Window is not available"); }

static int lib_setMouseEnable(lua_State* L)
{
    getwindow(window);
    const bool enable = lua_toboolean(L, 1);
    window->HideMouse(!enable);
    return 0;
}
static int lib_setTitle(lua_State* L)
{
    getwindow(window);
    const char* text = luaL_checkstring(L, 1);
    const std::wstring wtext = std::move(fcyStringHelper::MultiByteToWideChar(text, CP_UTF8));;
    window->SetCaption(wtext.c_str());
    return 0;
}
static int lib_setCentered(lua_State* L)
{
    getwindow(window);
    window->MoveToCenter();
    return 0;
}
static int lib_setStyle(lua_State* L)
{
    getwindow(window);
    const F2DWINBORDERTYPE style = (F2DWINBORDERTYPE)luaL_checkinteger(L, 1);
    window->SetBorderType(style);
    return 0;
}
static int lib_setSize(lua_State* L)
{
    getwindow(window);
    const float width = (float)luaL_checkinteger(L, 1);
    const float height = (float)luaL_checkinteger(L, 2);
    const fcyRect rect(0.0f, 0.0f, width, height);
    const fResult result = window->SetClientRect(rect);
    lua_pushboolean(L, result == FCYERR_OK);
    return 1;
}
static int lib_setTopMost(lua_State* L)
{
    getwindow(window);
    const bool topmost = lua_toboolean(L, 1);
    window->SetTopMost(topmost);
    return 0;
}
static int lib_setIMEEnable(lua_State* L)
{
    getwindow(window);
    const bool enable = lua_toboolean(L, 1);
    window->SetIMEEnable(enable);
    return 0;
}

static int lib_setTextInputEnable(lua_State* L)
{
    const bool enable = lua_toboolean(L, 1);
    LAPP().SetTextInputEnable(enable);
    return 0;
}
static int lib_getTextInput(lua_State* L)
{
    try
    {
        fcStrW text = LAPP().GetTextInput();
        std::string u8text = fcyStringHelper::WideCharToMultiByte(text, CP_UTF8);
        lua_pushstring(L, u8text.c_str());
        return 1;
    }
    catch(...)
    {
        lua_pushstring(L, "");
        return 1;
    }
}
static int lib_clearTextInput(lua_State* L)
{
    LAPP().ClearTextInput();
    return 0;
}

static int compat_SetSplash(lua_State* L)
{
    LAPP().SetSplash(lua_toboolean(L, 1));
    return 0;
}
static int compat_SetTitle(lua_State* L)
{
    LAPP().SetTitle(luaL_checkstring(L, 1));
    return 0;
}

#define makefname(__X__) { #__X__ , &lib_##__X__ }

static const luaL_Reg compat[] = {
    { "SetSplash", &compat_SetSplash },
    { "SetTitle" , &compat_SetTitle  },
    {NULL, NULL},
};

static const luaL_Reg lib[] = {
    makefname(setMouseEnable),
    makefname(setTitle),
    makefname(setCentered),
    makefname(setStyle),
    makefname(setSize),
    makefname(setTopMost),
    makefname(setIMEEnable),
    
    makefname(setTextInputEnable),
    makefname(getTextInput),
    makefname(clearTextInput),
    
    {NULL, NULL},
};

void LuaSTGPlus::LuaWrapper::WindowWrapper::Register(lua_State* L) LNOEXCEPT
{
    luaL_register(L, LUASTG_LUA_LIBNAME, compat); // ? t
    lua_pushstring(L, "Window");                  // ? t k
    lua_newtable(L);                              // ? t k t
    luaL_register(L, NULL, lib);                  // ? t k t
    lua_settable(L, -3);                          // ? t
    lua_pop(L, 1);                                // ?
};
