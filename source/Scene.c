#include "SuperX.h"

// god i hate dealing with json files in c

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
	json_t* tilesets;
	json_t* tileset1;
	json_t* tileset1Source;
	json_error_t error;

	int actualWidth;
	int pathLength;

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

	// load tileset
	tilesets = json_object_get(root, "tilesets");
	if (!json_is_array(tilesets)) {
		PrintLog("ERROR: parsing %s; could not read tilesets as array\n", sceneName);
		json_decref(tilesets);
		json_decref(root);
		return 1;
	}

	tileset1 = json_array_get(tilesets, 0);
	if (!json_is_object(tileset1)) {
		PrintLog("ERROR: parsing %s; could not load tileset in index 1\n", sceneName);
		json_decref(tileset1);
		json_decref(tilesets);
		json_decref(root);
		return 1;
	}

	tileset1Source = json_object_get(tileset1, "source");
	if (!json_is_string(tileset1Source)) {
		PrintLog("ERROR: parsing %s; filename parameter for tileset not a string\n", sceneName);
		json_decref(tileset1Source);
		json_decref(tileset1);
		json_decref(tilesets);
		json_decref(root);
		return 1;
	}

	// copy path into memory, then load later
	pathLength = json_string_length(tileset1Source);
	strncpy(sceneTileset.tsName, json_string_value(tileset1Source), 
			(pathLength > 0x100) ? 0x99 : pathLength);
	json_decref(tileset1Source);
	json_decref(tileset1);
	json_decref(tilesets);

	layerArray = json_object_get(root, "layers");
	if (!json_is_array(layerArray)) {
		PrintLog("ERROR: parsing %s; could not read scene layers as array\n", sceneName);
		json_decref(layerArray);
		json_decref(root);
		return 1;
	}

	layerCount = (u16) json_array_size(layerArray);
	sceneLayers = (TileLayer*) malloc(layerCount * sizeof(TileLayer));
	memset(sceneLayers, 0, layerCount * sizeof(TileLayer));
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
		sceneLayers[i].tileData = (int*) malloc(sceneLayers[i].width * sceneLayers[i].height * 
				sizeof(int));
		memset(sceneLayers[i].tileData, 0, sceneLayers[i].width * sceneLayers[i].height *
				sizeof(int));
		if (!sceneLayers[i].tileData) {
			PrintLog("ERROR: failed to allocate memory for tile layer %d\n", i);
			json_decref(layerProperties);
			json_decref(layerJs);
			json_decref(layerArray);
			json_decref(root);
			return 1;
		}

		// copy layer data
		// NOTE: currently, only CSV data is supported, might add support for
		// uncompressed base64 eventually but eh
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

	if (LoadTileset(sceneTileset.tsName)) {
		PrintLog("ERROR: could not load tileset\n");
		return 1;
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
	json_t* tsRoot;
	json_t* property;
	json_error_t error;

	char imgPath[0x100];
	int pathLength;

	tsRoot = json_load_file(name, 0, &error);
	if (!tsRoot) {
		PrintLog("ERROR: parsing %s, line %d %s\n", name, error.line, error.text);
		return 1;
	}

	if (!json_is_object(tsRoot)) {
		PrintLog("ERROR: parsing %s: tileset root is not an object\n", name);
		json_decref(tsRoot);
		return 1;
	}

	// check total tile count
	AssignValueInt(tsRoot, "tilecount", &sceneTileset.maxTiles);

	// look for file name and load it into memory
	property = json_object_get(tsRoot, "image");	
	if (!json_is_string(property)) {
		PrintLog("ERROR: expected string for property \"image\"\n");
		json_decref(property);
		json_decref(tsRoot);
		return 1;
	}

	// check extension of file
	pathLength = json_string_length(property);
	if (pathLength > 0x100) {
		PrintLog("ERROR: path given for property \"image\" exceeds 255 characters\n");
		json_decref(property);
		json_decref(tsRoot);
		return 1;
	}

	strncpy(imgPath, json_string_value(property), (pathLength >= 0x100) ? 0x99 : pathLength);
	if ( 	
			(imgPath[pathLength - 3] == 'g' || imgPath[pathLength - 3] == 'G') && 
	     		(imgPath[pathLength - 2] == 'i' || imgPath[pathLength - 2] == 'I') &&
			(imgPath[pathLength - 1] == 'f' || imgPath[pathLength - 1] == 'F')
	   ) {
		if (LoadSpriteSheetFromGIF(imgPath, &sceneTileset.spriteIndex, 0, 0)) {
			PrintLog("ERROR: could not load tileset graphic\n");
			json_decref(property);
			json_decref(tsRoot);
			return 1;
		}
	} else if (
			(imgPath[pathLength - 3] == 'p' || imgPath[pathLength - 2] == 'P') &&
			(imgPath[pathLength - 2] == 'n' || imgPath[pathLength - 2] == 'N') &&
			(imgPath[pathLength - 1] == 'g' || imgPath[pathLength - 1] == 'G')
		  ) {
		if (LoadSpriteSheetFromPNG(imgPath, &sceneTileset.spriteIndex)) {
			PrintLog("ERROR: could not load tileset graphic\n");
			json_decref(property);
			json_decref(tsRoot);
			return 1;
		}
	}

	PrintLog("Scene tileset is loaded into sprite slot %d\n", sceneTileset.spriteIndex);

	json_decref(property);
	json_decref(tsRoot);

	return 0;
}

void DrawLayer(int layer) {
	int startingPosX = cameraPosX;
	int startingPosY = cameraPosY;

	int xSpacing = startingPosX - ((startingPosX / 16) * 16);

	SpriteSheet* ss = &spriteSheetTable[sceneTileset.spriteIndex];
	int* tile;

	for (int y = startingPosY; y < startingPosY + screenHeight + 16; y += 16) {
		int drawY = y - startingPosY;
		int xCount = (startingPosX) % (sceneLayers[layer].width * 16);
		if (xCount < 0)
			xCount = (startingPosX - 16 + sceneLayers[layer].width * 16) % (sceneLayers[layer].width * 16);
		tile = &sceneLayers[layer].tileData[
				(y / 16)            * sceneLayers[layer].width + 
				(startingPosX / 16) % sceneLayers[layer].width
		];	

		for (int x = startingPosX; x < startingPosX + screenWidth + 16; x+= 16) {
			int drawX = x - startingPosX - xSpacing;
			xCount += 16;

			if (drawX <= 0)
				xCount -= 16;

			// loop layer horizontally
			if (xCount >= (int) sceneLayers[layer].width * 16) {
				tile = &sceneLayers[layer].tileData[
					(y / 16) * sceneLayers[layer].width
				];
				xCount = 0;
			}

			if (*tile <= 0 || *tile > sceneTileset.maxTiles) {
				PrintLog("Invalid tile ID: %d\n", *tile - 1);
				tile++;
				continue;
			}

			int sx = ((*tile - 1) * 16) % ss->width;
			int sy = ((*tile - 1) * 16) / ss->width * 16;
			//PrintLog("x: %d, y: %d, sx: %d, sy: %d, tile id: %d\n",
			//		x, y, sx, sy, *tile - 1);

			DrawSprite(sceneTileset.spriteIndex, drawX, drawY, 
					sx, sy, 16, 16, NOFLIP);	

			tile++;
		}

	}
}
