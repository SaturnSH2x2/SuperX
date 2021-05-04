#ifndef USERDATA_H
#define USERDATA_H

#define DEFAULT_INTERNALSIZEX 424
#define DEFAULT_INTERNALSIZEY 240
#define DEFAULT_SCREENSIZEX   1600
#define DEFAULT_SCREENSIZEY   900

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

int LoadGameConfig();

#endif
