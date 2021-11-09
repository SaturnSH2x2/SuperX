#include "SuperX.h"

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

static int l_getPaletteEntry(lua_State* L) {
	int palette = luaL_checkinteger(L, 1);
	int index   = luaL_checkinteger(L, 2);

	lua_pushnumber(L, GetPaletteEntry(palette, index));
	return 1;
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

// scene
static int l_getCameraPosX(lua_State* L) {
	lua_pushnumber(L, GetCameraPosX());
	return 1;
}

static int l_getCameraPosY(lua_State* L) {
	lua_pushnumber(L, GetCameraPosY());
	return 1;
}

static int l_offsetCamera(lua_State* L) {
	int x = luaL_checkinteger(L, 1);
	int y = luaL_checkinteger(L, 2);

	OffsetCamera(x, y);
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
	{ "GetPaletteEntry",		l_getPaletteEntry     },
	{ "SetTransparentColor",	l_setTransparentColor },
	{ NULL,				NULL	  	      }
};

static const struct luaL_reg SuperXScene [] = {
	{ "GetCameraPosX",		l_getCameraPosX },
	{ "GetCameraPosY",		l_getCameraPosY },
	{ "OffsetCamera",		l_offsetCamera  },
	{ NULL,				NULL 		}
};

// TODO: add frame rate to this so that scripts can adjust to 50Hz PAL Dreamcast systems
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

	lua_newtable(L);
	luaL_setfuncs(L, SuperXScene, 0);
	lua_setglobal(L, "Scene");
}

void SetupBasicObjectAttributes(lua_State* L, float x, float y, int activeOffscreen) {
	lua_newtable(L);
	lua_pushnumber(L, x);
	lua_setfield(L, -2, "x");
	lua_pushnumber(L, y);
	lua_setfield(L, -2, "y");
	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "widthRadius");
	lua_pushnumber(L, 0);
	lua_setfield(L, -2, "heightRadius");
	lua_pushboolean(L, activeOffscreen);
	lua_setfield(L, -2, "activeOffscreen");
	lua_setglobal(L, "Self");
}

// --- end Lua library definitions ---
int InitObject(const char* scriptName, int sLayer, float x, float y, int activeOffscreen) {
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

	File f;
	if (LoadFile(&f, scriptName, "r") || BufferFile(&f)) {
		PrintLog("ERROR: could not load object %s\n", scriptName);
		return 1;
	}

	objs[i] = luaL_newstate();
	luaL_openlibs(objs[i]);
	
	if (luaL_loadbuffer(objs[i], (const char*) f.buffer, f.size, scriptName)) {
		engineState = SUPERX_SCRIPTERROR;
		DisplayScriptError(objs[i]);
		return 1;
	}

	SetupAPI(objs[i]);
	SetupBasicObjectAttributes(objs[i], x, y, activeOffscreen);

	if (lua_pcall(objs[i], 0, 0, 0)) {
		engineState = SUPERX_SCRIPTERROR;
		DisplayScriptError(objs[i]);
		return 1;
	}

	// the script may not necessarily have an init function so 
	// we don't throw an error for this
	lua_getglobal(objs[i], "init");
	if (lua_pcall(objs[i], 0, 0, 0)) {
		lua_getglobal(objs[i], "init");
		if (lua_isfunction(objs[i], -1)) {
			engineState = SUPERX_SCRIPTERROR;
			DisplayScriptError(objs[i]);
		}
	}

	if (!sceneLayers[sLayer].objects) {
		PrintLog("NOTE: object data for layer %d not allocated, ignoring assignment\n", sLayer);
		return 0;
	}

	for (int y = 0; y < MAX_OBJECTS; y++) {
		if (sceneLayers[sLayer].objects[y] == NULL) {
			sceneLayers[sLayer].objects[y] = objs[i];
			break;
		}
	}

	CloseFile(&f);

	return 0;
}

void FreeObject(int objID) {
	lua_close(objs[objID]);
	objs[objID] = NULL;
}

void FreeAllObjects() {
	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (objs[i] != NULL)
			FreeObject(i);
	}
}

void UpdateObjects(int sLayer) {
	if (!sceneLayers[sLayer].objects)
		return;

	for (int i = 0; i < MAX_OBJECTS; i++) {
		if (!sceneLayers[sLayer].objects[i])
			continue;


		lua_getglobal(sceneLayers[sLayer].objects[i], "update");
		if (lua_pcall(sceneLayers[sLayer].objects[i], 0, 0, 0)) {
			lua_getglobal(objs[i], "update");
			if (!lua_isfunction(sceneLayers[sLayer].objects[i], -1))
				continue;

			engineState = SUPERX_SCRIPTERROR;
			DisplayScriptError(sceneLayers[sLayer].objects[i]);
		}
	}
}

