#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_INTERNALSIZEX 424
#define DEFAULT_INTERNALSIZEY 240
#define DEFAULT_SCREENSIZEX   1600
#define DEFAULT_SCREENSIZEY   900

#define MAX_PATHSIZE 255

extern char useDataFolder;

extern char gameName[256];
extern char gameVersion[16];
extern char** sceneTree;

typedef struct {
	char treeName[16];
	char** sceneList;
} SceneCategory;

inline void AssignValueInt(json_t* js, const char* key, int* val) {
	json_t* temp = json_object_get(js, key);
	if (json_is_integer(temp)) {
		*val = (int) json_number_value(temp);
	}

	json_decref(temp);
}

inline void AssignValueBool(json_t* js, const char* key, char* val) {
	json_t* temp = json_object_get(js, key);
	if (json_is_boolean(temp)) {
		*val = (char) json_boolean_value(temp);
	}

	json_decref(temp);
}

inline void AssignValueStr(json_t* js, const char* key, char* val, int size) {
	json_t* temp = json_object_get(js, key);
	if (json_is_string(temp)) {
		const char* tempStr = json_string_value(temp);
		strncpy(val, tempStr, size);
	}

	json_decref(temp);
}

int LoadUserConfig();
int LoadGameConfig();

#endif
