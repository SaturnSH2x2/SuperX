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

#endif
