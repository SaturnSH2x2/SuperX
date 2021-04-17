#ifndef SCRIPT_H
#define SCRIPT_H

#define MAX_OBJECTS 255
#define luaL_reg luaL_Reg

int InitObject(const char* scriptName);
void FreeObject(int objID);
void FreeAllObjects();
void UpdateObjects();

#endif
