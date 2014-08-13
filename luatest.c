#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>

void
_init_env(lua_State *L) {
	lua_pushglobaltable(L);
	lua_pushnil(L);  /* first key */
	while (lua_next(L, -2) != 0) {
		int keyt = lua_type(L, -2);
		if (keyt != LUA_TSTRING) {
			printf("Invalid config table\n");
			exit(1);
		}
		const char * key = lua_tostring(L,-2);
		if (lua_type(L,-1) == LUA_TBOOLEAN) {
			int b = lua_toboolean(L,-1);
			
		} else {
			const char * value = lua_tostring(L,-1);
			if (value == NULL) {
				printf("Invalid config table key = %s\n", key);
				exit(1);
			}
			printf("config table key = %s value=%s\n", key, value);
		}
		lua_pop(L,1);
	}
	lua_pop(L,1);
}

int main()
{
	printf("1<<8 %d \n", 1<<8);
	lua_State *L=luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L,"./config");
	_init_env(L);
	//int n=lua_gettop(L);
	lua_close(L);
	//printf("%d \n", n);
	
	
	return;
}
