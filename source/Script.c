#include "SuperX.h"

int objectCount;
lua_State* objs[MAX_OBJECTS] = { NULL };

// TODO: raise errors on some with two few arguments
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

// input
static int l_getButtonDown(lua_State* L) {
	int port   = luaL_checkinteger(L, 1);
	int button = luaL_checkinteger(L, 2);

	if (GetButtonDown(port, button))
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);
	
	return 1;
}

static int l_getButtonHeld(lua_State* L) {
	int port   = luaL_checkinteger(L, 1);
	int button = luaL_checkinteger(L, 2);

	if (GetButtonHeld(port, button))
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

static int l_getButtonUp(lua_State* L) {
	int port   = luaL_checkinteger(L, 1);
	int button = luaL_checkinteger(L, 2);

	if (GetButtonUp(port, button))
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

// audio
static int l_playMusic(lua_State* L) {
	const char* filename = luaL_checkstring(L, 1);

	if (PlayMusic(filename))
		lua_pushboolean(L, 0);
	else
		lua_pushboolean(L, 1);

	return 1;
}

static int l_closeMusic(lua_State* L) {
	CloseMusic();
	return 0;
}

static int l_pauseMusic(lua_State* L) {
	PauseMusic();
	return 0;
}

static int l_resumeMusic(lua_State* L) {
	ResumeMusic();
	return 0;
}

static int l_loadSoundEffect(lua_State* L) {
	int index;
	const char* filename = luaL_checkstring(L, 1);
	
	LoadSoundEffect(filename, &index);
	lua_pushnumber(L, index);

	return 1;
}

static int l_playSoundEffect(lua_State* L) {
	int index = luaL_checkinteger(L, 1);
	PlaySoundEffect(index);

	return 0;
}

// render
static int l_clearFrameBuffer(lua_State* L) {
	u16 color = (u16) luaL_checkinteger(L, 1);
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

static int l_drawRect(lua_State* L) {
	int argcount = lua_gettop(L);
	if (argcount < 5) {
		PrintLog("ERROR: too few arguments to DrawRectangle\n");
		return 0;
	}

	int x = luaL_checkinteger(L, 1);
	int y = luaL_checkinteger(L, 2);
	int w = luaL_checkinteger(L, 3);
	int h = luaL_checkinteger(L, 4);
	u16 col = (u16) luaL_checkinteger(L, 5);

	if (renderType == SUPERX_SW_RENDER)
		DrawRectangleSW(x, y, w, h, col);
	else
		PrintLog("NOTE: unimplemented draw call (DrawRectangle)\n");

	return 0;
}

static int l_drawText(lua_State* L) {
	const char* s = luaL_checkstring(L, 1);
	int x         = luaL_checkinteger(L, 2);
	int y         = luaL_checkinteger(L, 3);
	u16 color     = (u16) luaL_checkinteger(L, 4);

	DrawText(x, y, color, -1, s);
	return 0;
}

static int l_buildColor(lua_State* L) {
	int r = luaL_checkinteger(L, 1);
	int g = luaL_checkinteger(L, 2);
	int b = luaL_checkinteger(L, 3);
	
	u32 builtColor = ((b << 16) | (g << 8) | (r)) | 0xff000000;
	lua_pushnumber(L, RGBA8_to_RGB565(builtColor));

	return 1;
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

static const struct luaL_reg SuperXInput [] = {
	{ "GetButtonDown",	l_getButtonDown },
	{ "GetButtonHeld",	l_getButtonHeld },
	{ "GetButtonUp",	l_getButtonUp   },
	{ NULL,			NULL		}
};

static const struct luaL_reg SuperXAudio [] = {
	{ "PlayMusic",		l_playMusic       },
	{ "CloseMusic",		l_closeMusic      },
	{ "PauseMusic",		l_pauseMusic      },
	{ "ResumeMusic",	l_resumeMusic 	  },
	{ "LoadSoundEffect",	l_loadSoundEffect },
	{ "PlaySoundEffect",	l_playSoundEffect },
	{ NULL,			NULL	          }
};

static const struct luaL_reg SuperXRender [] = {
	{ "ClearScreen",	l_clearFrameBuffer },
	{ "DrawSprite",		l_drawSprite },
	{ "DrawRectangle",	l_drawRect },
	{ "DrawText",		l_drawText },
	{ "BuildColor",		l_buildColor },
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
		engineState = SUPERX_SCRIPTERROR;
		DisplayScriptError(i);
		return 1;
	}

	if (lua_pcall(objs[i], 0, 0, 0)) {
		engineState = SUPERX_SCRIPTERROR;
		DisplayScriptError(i);
		return 1;
	}

	lua_newtable(objs[i]);
	luaL_setfuncs(objs[i], SuperXDebug, 0);
	lua_setglobal(objs[i], "Debug");

	lua_newtable(objs[i]);
	lua_pushnumber(objs[i], BUTTON_B);
	lua_setfield(objs[i], -2, "B");
	lua_pushnumber(objs[i], BUTTON_A);
	lua_setfield(objs[i], -2, "A");
	lua_pushnumber(objs[i], BUTTON_X);
	lua_setfield(objs[i], -2, "X");
	lua_pushnumber(objs[i], BUTTON_Y);
	lua_setfield(objs[i], -2, "Y");
	lua_pushnumber(objs[i], BUTTON_L);
	lua_setfield(objs[i], -2, "L");
	lua_pushnumber(objs[i], BUTTON_R);
	lua_setfield(objs[i], -2, "R");
	lua_pushnumber(objs[i], BUTTON_START);
	lua_setfield(objs[i], -2, "Start");
	lua_pushnumber(objs[i], BUTTON_SELECT);
	lua_setfield(objs[i], -2, "Select");
	lua_pushnumber(objs[i], BUTTON_UP);
	lua_setfield(objs[i], -2, "Up");
	lua_pushnumber(objs[i], BUTTON_DOWN);
	lua_setfield(objs[i], -2, "Down");
	lua_pushnumber(objs[i], BUTTON_LEFT);
	lua_setfield(objs[i], -2, "Left");
	lua_pushnumber(objs[i], BUTTON_RIGHT);
	lua_setfield(objs[i], -2, "Right");
	luaL_setfuncs(objs[i], SuperXInput, 0);
	lua_setglobal(objs[i], "Input");

	lua_newtable(objs[i]);
	luaL_setfuncs(objs[i], SuperXSprite, 0);
	lua_setglobal(objs[i], "Sprite");

	lua_newtable(objs[i]);
	luaL_setfuncs(objs[i], SuperXAudio, 0);
	lua_setglobal(objs[i], "Audio");

	lua_newtable(objs[i]);
	lua_pushnumber(objs[i],  (int) NOFLIP);
	lua_setfield(objs[i], -2, "NOFLIP");
	lua_pushnumber(objs[i], (int) XFLIP);
	lua_setfield(objs[i], -2, "XFLIP");
	lua_pushnumber(objs[i], (int) YFLIP);
	lua_setfield(objs[i], -2, "YFLIP");
	lua_pushnumber(objs[i], (int) XYFLIP);
	lua_setfield(objs[i], -2, "XYFLIP");
	lua_pushnumber(objs[i], bufferSizeX);
	lua_setfield(objs[i], -2, "SCREENWIDTH");
	lua_pushnumber(objs[i], bufferSizeY);
	lua_setfield(objs[i], -2, "SCREENHEIGHT");
	luaL_setfuncs(objs[i], SuperXRender, 0);
	lua_setglobal(objs[i], "Render");

	// the script may not necessarily have an init function so 
	// we don't throw an error for this
	lua_getglobal(objs[i], "init");
	if (lua_pcall(objs[i], 0, 0, 0)) {
		PrintLog("NOTE: %s\n", lua_tostring(objs[i], -1));
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
			lua_getglobal(objs[i], "update");
			if (!lua_isfunction(objs[i], -1))
				continue;

			engineState = SUPERX_SCRIPTERROR;
			DisplayScriptError(i);
		}
	}
}


