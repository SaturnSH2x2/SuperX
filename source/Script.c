#include "SuperX.h"

lua_State* objs[SPRITE_LAYER_COUNT][MAX_OBJECTS] = { NULL };

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

static int l_loadSSFromGIF(lua_State* L) {
	const char* fPath = luaL_checkstring(L, 1);
	int paletteSlot   = luaL_checkinteger(L, 2);
	int loadPalette   = (int) luaL_checkboolean(L, 3);

	u8 sheetIndex = 0;
	if (LoadSpriteSheetFromGIF(fPath, &sheetIndex, paletteSlot, loadPalette) != 0) {
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
static int l_clearScreen(lua_State* L) {
	int color = luaL_checkinteger(L, 1);
	ClearScreen(color);

	return 0;
}

static int l_drawSprite(lua_State* L) {
	int sid = luaL_checkinteger(L, 1);
	int x   = luaL_checkinteger(L, 2);
	int y   = luaL_checkinteger(L, 3);
	int sx  = luaL_checkinteger(L, 4);
	int sy  = luaL_checkinteger(L, 5);
	int w   = luaL_checkinteger(L, 6);
	int h   = luaL_checkinteger(L, 7);
	SpriteFlipFlag f = (SpriteFlipFlag) luaL_checkinteger(L, 8);

	DrawSprite(sid, x, y, sx, sy, w, h, f);

	return 0;
}

static int l_drawRect(lua_State* L) {
	int x = luaL_checkinteger(L, 1);
	int y = luaL_checkinteger(L, 2);
	int w = luaL_checkinteger(L, 3);
	int h = luaL_checkinteger(L, 4);
	u32 col = (u32) luaL_checkinteger(L, 5);

	DrawRectangle(x, y, w, h, col);

	return 0;
}

static int l_drawText(lua_State* L) {
	const char* s = luaL_checkstring(L, 1);
	int x         = luaL_checkinteger(L, 2);
	int y         = luaL_checkinteger(L, 3);
	u32 color     = (u32) luaL_checkinteger(L, 4);

	DrawText(x, y, color, -1, s);
	return 0;
}

static int l_buildColor(lua_State* L) {
	u32 r = (u32) luaL_checkinteger(L, 1);
	u32 g = (u32) luaL_checkinteger(L, 2) << 8;
	u32 b = (u32) luaL_checkinteger(L, 3) << 16;
	u32 a = (u32) 0xff << 24;

	u32 builtColor = a | b | g | r;
	lua_pushnumber(L, builtColor);

	return 1;
}

// palette
static int l_setPaletteEntry(lua_State* L) {
	int palette = luaL_checkinteger(L, 1);
	int index   = luaL_checkinteger(L, 2);
	u32 color   = (u32) luaL_checkinteger(L, 3);

	SetPaletteEntry(color, palette, index);
	return 0;
}

static int l_setTransparentColor(lua_State* L) {
	int palIndex = luaL_checkinteger(L, 1);
	char colIndex = luaL_checkinteger(L, 2);

	if (palIndex < 0 || palIndex >= 4) {
		lua_pushstring(L, "palette index should be 0-3");
		lua_error(L);
	}

	SetTransparentColor(colIndex, palIndex);
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
	{ "LoadFromGIF"		  , l_loadSSFromGIF },
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
	{ "ClearScreen",	l_clearScreen },
	{ "DrawSprite",		l_drawSprite },
	{ "DrawRectangle",	l_drawRect },
	{ "DrawText",		l_drawText },
	{ "BuildColor",		l_buildColor },
	{ NULL,			NULL }
};

static const struct luaL_reg SuperXPalette [] = {
	{ "SetPaletteEntry",		l_setPaletteEntry     },
	{ "SetTransparentColor",	l_setTransparentColor },
	{ NULL,				NULL	  	      }
};

void SetupAPI(lua_State* L) {
	lua_newtable(L);
	luaL_setfuncs(L, SuperXDebug, 0);
	lua_setglobal(L, "Debug");

	lua_newtable(L);
	lua_pushnumber(L, BUTTON_B);
	lua_setfield(L, -2, "B");
	lua_pushnumber(L, BUTTON_A);
	lua_setfield(L, -2, "A");
	lua_pushnumber(L, BUTTON_X);
	lua_setfield(L, -2, "X");
	lua_pushnumber(L, BUTTON_Y);
	lua_setfield(L, -2, "Y");
	lua_pushnumber(L, BUTTON_L);
	lua_setfield(L, -2, "L");
	lua_pushnumber(L, BUTTON_R);
	lua_setfield(L, -2, "R");
	lua_pushnumber(L, BUTTON_START);
	lua_setfield(L, -2, "Start");
	lua_pushnumber(L, BUTTON_SELECT);
	lua_setfield(L, -2, "Select");
	lua_pushnumber(L, BUTTON_UP);
	lua_setfield(L, -2, "Up");
	lua_pushnumber(L, BUTTON_DOWN);
	lua_setfield(L, -2, "Down");
	lua_pushnumber(L, BUTTON_LEFT);
	lua_setfield(L, -2, "Left");
	lua_pushnumber(L, BUTTON_RIGHT);
	lua_setfield(L, -2, "Right");
	luaL_setfuncs(L, SuperXInput, 0);
	lua_setglobal(L, "Input");

	lua_newtable(L);
	luaL_setfuncs(L, SuperXSprite, 0);
	lua_setglobal(L, "Sprite");

	lua_newtable(L);
	luaL_setfuncs(L, SuperXAudio, 0);
	lua_setglobal(L, "Audio");

	lua_newtable(L);
	lua_pushnumber(L,  (int) NOFLIP);
	lua_setfield(L, -2, "NOFLIP");
	lua_pushnumber(L, (int) XFLIP);
	lua_setfield(L, -2, "XFLIP");
	lua_pushnumber(L, (int) YFLIP);
	lua_setfield(L, -2, "YFLIP");
	lua_pushnumber(L, (int) XYFLIP);
	lua_setfield(L, -2, "XYFLIP");
	lua_pushnumber(L, screenWidth);
	lua_setfield(L, -2, "SCREENWIDTH");
	lua_pushnumber(L, screenHeight);
	lua_setfield(L, -2, "SCREENHEIGHT");
	luaL_setfuncs(L, SuperXRender, 0);
	lua_setglobal(L, "Render");

	lua_newtable(L);
	luaL_setfuncs(L, SuperXPalette, 0);
	lua_setglobal(L, "Palette");
}

// --- end Lua library definitions ---
int InitObject(const char* scriptName, int sLayer) {
	int i = -1;
	for (int x = 0; x < MAX_OBJECTS; x++) {
		if (objs[sLayer][x] == NULL) {
			i = x;
			break;
		}
	}

	if (i == -1) {
		PrintLog("ERROR: object count of %d reached\n", MAX_OBJECTS);
		return 1;
	}

	objs[sLayer][i] = luaL_newstate();
	luaL_openlibs(objs[sLayer][i]);
	
	if (luaL_loadfile(objs[sLayer][i], scriptName)) {
		engineState = SUPERX_SCRIPTERROR;
		DisplayScriptError(i, sLayer);
		return 1;
	}

	SetupAPI(objs[sLayer][i]);

	if (lua_pcall(objs[sLayer][i], 0, 0, 0)) {
		engineState = SUPERX_SCRIPTERROR;
		DisplayScriptError(i, sLayer);
		return 1;
	}
	// the script may not necessarily have an init function so 
	// we don't throw an error for this
	lua_getglobal(objs[sLayer][i], "init");
	if (lua_pcall(objs[sLayer][i], 0, 0, 0)) {
		lua_getglobal(objs[sLayer][i], "init");
		if (lua_isfunction(objs[sLayer][i], -1)) {
			engineState = SUPERX_SCRIPTERROR;
			DisplayScriptError(i, sLayer);
		}
	}

	return 0;
}

void FreeObject(int objID, int sLayer) {
	lua_close(objs[sLayer][objID]);
	objs[sLayer][objID] = NULL;
}

void FreeAllObjects() {
	for (int j = 0; j < SPRITE_LAYER_COUNT; j++) {
		for (int i = 0; i < MAX_OBJECTS; i++) {
			if (objs[j][i] != NULL) {
				lua_close(objs[j][i]);
				objs[j][i] = NULL;
			}
		}
	}
}

void UpdateObjects(int sLayer) {
	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (objs[sLayer][i] == NULL)
			continue;

		lua_getglobal(objs[sLayer][i], "update");
		if (lua_pcall(objs[sLayer][i], 0, 0, 0)) {
			lua_getglobal(objs[sLayer][i], "update");
			if (!lua_isfunction(objs[sLayer][i], -1))
				continue;

			engineState = SUPERX_SCRIPTERROR;
			DisplayScriptError(i, sLayer);
		}
	}
}

