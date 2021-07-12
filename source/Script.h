#ifndef SCRIPT_H
#define SCRIPT_H

#define MAX_OBJECTS        (50)
#define SPRITE_LAYER_COUNT (7)
#define luaL_reg luaL_Reg

extern lua_State* objs[SPRITE_LAYER_COUNT][MAX_OBJECTS];

int InitObject(const char* scriptName, int sLayer);
void FreeObject(int objID, int sLayer);
void FreeAllObjects();
void UpdateObjects(int sLayer);

// i'm sure there's totally a great reason as to why this function
// doesn't exist in the base library
inline int luaL_checkboolean(lua_State* L, int pos) {
	if (lua_isboolean(L, pos))
		return (int) lua_toboolean(L, pos);
	else {
		lua_pushstring(L, "argument should be boolean");
		lua_error(L);
		return 0;
	}
}

#endif
