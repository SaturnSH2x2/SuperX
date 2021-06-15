#include "SuperX.h"

// TODO: account for base path
int LoadUserConfig() {
	json_t* root;
	json_error_t error;

	json_t* display;

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

		json_dump_file(root, "config.json", 0);
	}

	AssignValueInt(display, "internal-screen-width", &bufferSizeX);
	AssignValueInt(display, "internal-screen-height", &bufferSizeY);
	AssignValueInt(display, "window-width",  &windowSizeX);
	AssignValueInt(display, "window-height", &windowSizeY);
	AssignValueBool(display, "fullscreen", &isFullscreen);

	
	return 0;
}
