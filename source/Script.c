#include "SuperX.h"

int objectCount;
lua_State* objs[MAX_OBJECTS] = { NULL };

// --- begin Lua wrapper functions ---

// debug
static int l_PrintLog(lua_State* L) {
	const char* s = luaL_checkstring(L, 1);
	PrintLog("SCRIPT: %s\n", s);
	return 0;
}

// sprite
static int l_loadSSFromPNG(lua_State* L) {
	const char* fPath = luaL_checkstring(L, 1);
	u8 sheetIndex = 0;
	if (LoadSpriteSheetFromPNG(fPath, &sheetIndex) != 0) {
		lua_pushnumber(L, -1);
	} else {
		lua_pushnumber(L, (int) sheetIndex);
	}

	return 1;
}

// render
static int l_clearFrameBuffer(lua_State* L) {
	u32 color = (u32) luaL_checkinteger(L, 1);
	if (renderType == SUPERX_SW_RENDER)
		ClearFrameBuffer(color);
	else
		PrintLog("NOTE: unimplemented draw call (ClearFrameBuffer)\n");

	return 0;
}

static int l_drawSprite(lua_State* L) {
	int argcount = lua_gettop(L);
	if (argcount < 8) {
		PrintLog("ERROR: too few arguments to DrawSprite\n");
		return 0;
	}

	int sid = luaL_checkinteger(L, 1);
	int x   = luaL_checkinteger(L, 2);
	int y   = luaL_checkinteger(L, 3);
	int sx  = luaL_checkinteger(L, 4);
	int sy  = luaL_checkinteger(L, 5);
	int w   = luaL_checkinteger(L, 6);
	int h   = luaL_checkinteger(L, 7);
	SpriteFlipFlag f = (SpriteFlipFlag) luaL_checkinteger(L, 8);

	if (renderType == SUPERX_SW_RENDER)
		DrawSpriteSW(sid, x, y, sx, sy, w, h, f);
	else
		PrintLog("NOTE: unimplemented draw call (DrawSprite)\n");

	return 0;
}

// --- end Lua wrapper functions ---

// --- begin Lua library definitions ---
static const struct luaL_reg SuperXDebug [] = {
	{ "PrintLog", l_PrintLog },
	{ NULL,       NULL       }
};

static const struct luaL_reg SuperXSprite [] = {
	{ "LoadFromPNG"           , l_loadSSFromPNG },
	{ NULL	                  , NULL            }
};

static const struct luaL_reg SuperXRender [] = {
	{ "ClearScreen",	l_clearFrameBuffer },
	{ "DrawSprite",		l_drawSprite },
	{ NULL,			NULL }
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

	lua_newtable(objs[i]);
	luaL_setfuncs(objs[i], SuperXSprite, 0);
	lua_setglobal(objs[i], "Sprite");

	lua_newtable(objs[i]);
	luaL_setfuncs(objs[i], SuperXRender, 0);
	lua_setglobal(objs[i], "Render");

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


