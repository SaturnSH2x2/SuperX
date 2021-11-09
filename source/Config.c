#include "SuperX.h"

char useDataFolder;

// game config variables
char gameName[256];
char gameVersion[16];

SceneCategory* sceneTree;
int categoryCount;

// TODO: account for base path
int LoadUserConfig() {
	json_t* root;
	json_error_t error;

	json_t* display;

	char altered = 0;

	// this file wouldn't be with the rest of the game data, so this is fine
	root = json_load_file("config.json", 0, &error);
	if (!root) {
		if (error.line == -1) {
			root = json_object();
		} else {
			PrintLog("ERROR: parsing config.json, line %d: %s\n", error.line, error.text);
			return 1;
		}
	}

	if (!json_is_object(root)) {
		PrintLog("ERROR: root of config not an object\n");
		json_decref(root);
		return 1;
	}

	// load any input remapping
	LoadKeyMapping(root, &altered);

	// load display settings
	display = json_object_get(root, "display");
	if (!json_is_object(display)) {
		// populate with default display values
		display = json_object();
		json_object_set(display, "internal-screen-width",   json_integer(DEFAULT_INTERNALSIZEX));
		json_object_set(display, "internal-screen-height",  json_integer(DEFAULT_INTERNALSIZEY));
		json_object_set(display, "window-width",            json_integer(DEFAULT_SCREENSIZEX));
		json_object_set(display, "window-height",           json_integer(DEFAULT_SCREENSIZEY));
		json_object_set(display, "fullscreen", json_false());
		json_object_set(root, "display", display);
	}

	
	AssignValueInt(display, "internal-screen-width", &bufferSizeX);
	AssignValueInt(display, "internal-screen-height", &bufferSizeY);
	AssignValueInt(display, "window-width",  &windowSizeX);
	AssignValueInt(display, "window-height", &windowSizeY);
	AssignValueBool(display, "fullscreen", &isFullscreen);

	if (altered) {
		PrintLog("NOTE: writing to config.json\n");
		json_dump_file(root, "config.json", 0);
	}

	json_decref(display);
	json_decref(root);
	
	return 0;
}

int LoadGameConfig() {
	json_t* root;
	json_error_t error;

	json_t* sTreeJS;

	// used for iteration
	const char* key;
	json_t* val;

	File f;

	if (LoadFile(&f, "Data/GameConfig.json", "r") || BufferFile(&f)) {
		PrintLog("ERROR: failed to load GameConfig.json\n");
		CloseFile(&f);
		return 1;
	}

	root = json_loadb((const char*) f.buffer, f.size, 0, &error);

	if (!root) {
		PrintLog("ERROR: parsing GameConfig.json, line %d: %s\n", error.line, error.text);
		return 1;
	}

	AssignValueStr(root, "game-name", gameName, 255);
	AssignValueStr(root, "game-version", gameVersion, 15);

	sTreeJS = json_object_get(root, "scene-tree");
	if (!json_is_object(sTreeJS)) {
		PrintLog("ERROR: parsing GameConfig.json, cannot read scene tree\n");
		return 1;
	}

	categoryCount = json_object_size(sTreeJS);
	sceneTree = (SceneCategory*) malloc(categoryCount * sizeof(SceneCategory));

	void* iter = json_object_iter(sTreeJS);
	int index = 0;
	while (iter) {
		key = json_object_iter_key(iter);
		val = json_object_iter_value(iter);

		if (!json_is_array(val)) {
			PrintLog("NOTE: %s is not a valid scene category, ignoring.\n", key);
			iter = json_object_iter_next(sTreeJS, iter);
			index++;
			continue;
		}

		sceneTree[index].sceneCount = json_array_size(val);
		strncpy(sceneTree[index].categoryName, key, 15);
		sceneTree[index].scenes = (Scene*) malloc(sceneTree[index].sceneCount * sizeof(Scene));

		for (int i = 0; i < sceneTree[index].sceneCount; i++) {
			json_t* temp = json_array_get(val, i);
			if (!json_is_object(temp)) {
				PrintLog("NOTE: could not parse scene at index %d in %s; ignoring\n", i, key);
				continue;
			}

			AssignValueStr(temp, "name", sceneTree[index].scenes[i].sceneName, 15);
			AssignValueStr(temp, "path", sceneTree[index].scenes[i].scenePath, 255);

			json_decref(temp);
		}

		iter = json_object_iter_next(sTreeJS, iter);
		index++;
	}

	json_decref(sTreeJS);
	json_decref(root);

	CloseFile(&f);

	return 0;
}

void CloseGameConfig() {
	for (int i = 0; i < categoryCount; i++) {
		free(sceneTree[i].scenes);
	}

	free(sceneTree);
}
