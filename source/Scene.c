#include "SuperX.h"

u16 layerCount;

Tileset sceneTileset;
TileLayer* sceneLayers;

u16 cameraPosX;
u16 cameraPosY;

char sceneName[255];

int LoadScene(const char* sceneName) {
	// free the current scene before loading in the new one
	FreeScene();

	json_t* root;
	json_t* layerArray;
	json_t* layerJs;
	json_t* layerProperties;
	json_t* layerData;
	json_t* tileIndex;
	json_t* property;
	json_t* oString;
	json_t* oVal;
	json_error_t error;

	int actualWidth;

	root = json_load_file(sceneName, 0, &error);

	if (!root) {
		PrintLog("ERROR: parsing %s, line %d: %s\n", sceneName, error.line, error.text);
		return 1;
	}

	if (!json_is_object(root)) {
		PrintLog("ERROR: root of config not an object\n");
		json_decref(root);
		return 1;
	}

	layerArray = json_object_get(root, "layers");
	if (!json_is_array(layerArray)) {
		PrintLog("ERROR: parsing %s; could not read scene layers as array\n", sceneName);
		json_decref(layerArray);
		json_decref(root);
		return 1;
	}

	layerCount = (u16) json_array_size(layerArray);
	sceneLayers = (TileLayer*) malloc(layerCount * sizeof(TileLayer));
	if (!sceneLayers) {
		PrintLog("ERROR: failed to allocate memory for scene layers\n");
		json_decref(layerArray);
		json_decref(root);
		return 1;
	}

	for (u16 i = 0; i < layerCount; i++) {
		layerJs = json_array_get(layerArray, i);
		if (!json_is_object(layerJs)) {
			PrintLog("ERROR: parsing %s, layer %d; could not read layer as object\n", sceneName, i);
			json_decref(layerJs);
			continue;
		}

		// fallback values
		AssignValueUnsignedInt(layerJs, "width", &sceneLayers[i].width);
		AssignValueUnsignedInt(layerJs, "height", &sceneLayers[i].height);
		actualWidth = sceneLayers[i].width;

		layerProperties = json_object_get(layerJs, "properties");
		if (json_is_array(layerProperties)) {
			for (u16 p = 0; p < json_array_size(layerProperties); p++) {
				property = json_array_get(layerProperties, p);
				if (!json_is_object(property)) {
					json_decref(property);
					continue;
				}

				oString = json_object_get(property, "name");
				if (!json_is_string(oString)) {
					PrintLog("ERROR: property name given not string\n");
					json_decref(oString);
					json_decref(property);
					continue;
				}

				// tile width
				if (strncmp(json_string_value(oString), "actualTileWidth", 16)) {
					oVal = json_object_get(property, "value");
					if (!json_is_integer(oVal)) {
						PrintLog("ERROR: actualTileWidth value not integer, ignoring\n");
					} else {
						sceneLayers[i].width = json_integer_value(oVal);
					}

					json_decref(oVal);
				}

				if (strncmp(json_string_value(oString), "actualTileHeight", 17)) {
					oVal = json_object_get(property, "value");
					if (!json_is_integer(oVal)) {
						PrintLog("ERROR: actualTileHeight value not integer, ignoring\n");
					} else {
						sceneLayers[i].height = json_integer_value(oVal);
					}

					json_decref(oVal);
				}

				json_decref(oString);
			}
		}

		// allocate memory for tile layer
		sceneLayers[i].tileData = (unsigned int*) malloc(sceneLayers[i].width * sceneLayers[i].height * 
				sizeof(unsigned int));
		if (!sceneLayers[i].tileData) {
			PrintLog("ERROR: failed to allocate memory for tile layer %d\n", i);
			json_decref(layerProperties);
			json_decref(layerJs);
			json_decref(layerArray);
			json_decref(root);
			return 1;
		}

		// copy layer data
		layerData = json_object_get(layerJs, "data");
		if (!json_is_array(layerData)) {
			PrintLog("ERROR: failed to read tile data for layer %d\n", i);
			json_decref(layerProperties);
			json_decref(layerJs);
			continue;
		}

		for (u16 y = 0; y < sceneLayers[i].height; y++) {
			for (u16 x = 0; x < sceneLayers[i].width; x++) {
				tileIndex = json_array_get(layerData, y * actualWidth + x);
				if (!json_is_integer(tileIndex)) {
					PrintLog("ERROR: parsing tile index %d; unexpected element\n", i);
					json_decref(tileIndex);
					continue;
				}

				sceneLayers[i].tileData[y * sceneLayers[i].width + x] = 
					(unsigned int) json_number_value(tileIndex);

				json_decref(tileIndex);
			}
		}

		json_decref(oVal);
		json_decref(oString);
		json_decref(property);
		json_decref(tileIndex);
		json_decref(layerData);
		json_decref(layerProperties);
		json_decref(layerJs);
		json_decref(layerArray);
		json_decref(root);
	}

	return 0;
}

void FreeScene() {
	if (!sceneLayers)
		return;

	for (u16 i = 0; i < layerCount; i++) {
		free(sceneLayers[i].tileData);
	}

	free(sceneLayers);
}

int LoadTileset(const char* name) {
	return 0;
}
