#ifndef DEBUG_HPP
#define DEBUG_HPP

#define DEVMENU_MAX_ENTRIES (16)

typedef enum {
	DEV_MAIN_MENU,
	DEV_CATEGORY_SELECT,
	DEV_SCENE_SELECT
} DevMenuState;

typedef enum {
	DEVINPUT_UP,
	DEVINPUT_DOWN,
	DEVINPUT_SELECT
} DevInput;

void PrintLog(const char* str, ...);
void InitDevMenu();
void RunDevMenu();
void DevMenuInput(DevInput stat);
void DisplayScriptError(lua_State* L);

#endif
