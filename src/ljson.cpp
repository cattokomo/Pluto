#include "lauxlib.h"
#include "lualib.h"

#ifdef PLUTO_USE_SOUP

#include "ljson.hpp"

static int encode(lua_State* L) {
	auto root = checkJson(L, 1);
	if (lua_gettop(L) >= 2 && lua_toboolean(L, 2))
	{
		lua_pushstring(L, root->encodePretty());
	}
	else
	{
		lua_pushstring(L, root->encode());
	}
	return 1;
}

static int decode(lua_State* L)
{
	auto root = soup::json::decodeForDedicatedVariable(luaL_checkstring(L, 1));
	pushFromJson(L, *root);
	return 1;
}

static const luaL_Reg funcs[] = {
	{"encode", encode},
	{"decode", decode},
	{nullptr, nullptr}
};

LUA_API int luaopen_json(lua_State *L) {
	luaL_newlib(L, funcs);
	return 1;
}

#endif