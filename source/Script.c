#include "SuperX.h"

int objectCount;
lua_State* objs[MAX_OBJECTS] = { NULL };

// --- begin Lua wrapper functions ---
static int l_PrintLog(lua_State* L) {
	const char* s = luaL_checkstring(L, 1);
	PrintLog("SCRIPT: %s\n", s);
	return 0;
}
// --- end Lua wrapper functions ---

// --- begin Lua library definitions ---
static const struct luaL_reg SuperXDebug [] = {
	{ "PrintLog", l_PrintLog },
	{ NULL,       NULL       }
};
// --- end Lua library definitions ---

int InitObject(const char* scriptName) {
	int i = -1;
	for (int x = 0; x < MAX_OBJECTS; x++) {
		if (objs[x] == NULL) {
			i = x;
			break;
		}
	}

	if (i == -1) {
		PrintLog("ERROR: object count of %d reached\n", MAX_OBJECTS);
		return 1;
	}

	objs[i] = luaL_newstate();
	luaL_openlibs(objs[i]);

	
	if (luaL_loadfile(objs[i], scriptName)) {
		PrintLog("ERROR: %s\n", lua_tostring(objs[i], -1));
		return 1;
	}

	if (lua_pcall(objs[i], 0, 0, 0)) {
		PrintLog("ERROR: %s\n", lua_tostring(objs[i], -1));
		return 1;
	}

	lua_newtable(objs[i]);
	luaL_setfuncs(objs[i], SuperXDebug, 0);
	lua_setglobal(objs[i], "Debug");

	lua_getglobal(objs[i], "init");
	if (lua_pcall(objs[i], 0, 0, 0)) {
		PrintLog("ERROR: %s\n", lua_tostring(objs[i], -1));
	}

	objectCount++;
	return 0;
}

void FreeObject(int objID) {
	lua_close(objs[objID]);
	objs[objID] = NULL;
}

void FreeAllObjects() {
	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (objs[i] != NULL) {
			lua_close(objs[i]);
			objs[i] = NULL;
		}
	}
}

void UpdateObjects() {
	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (objs[i] == NULL)
			continue;

		lua_getglobal(objs[i], "update");
		if (lua_pcall(objs[i], 0, 0, 0)) {
			PrintLog("ERROR: %s\n", lua_tostring(objs[i], -1));
		}
	}
}


