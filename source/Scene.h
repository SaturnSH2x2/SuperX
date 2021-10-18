#ifndef SCENE_H
#define SCENE_H

typedef struct {
	// NOTE TO SELF: actualTileWidth/actualTileHeight values take
	// priority in the json data for these values
	unsigned int width;
	unsigned int height;
	
	int* tileData;

	// parallax speed spanning entire layer
	float parallaxFactorX;
	float parallaxFactorY;

	// for psuedo-3D parallax and other such scanline-based deformation(x-axis only)
	float* scanlineParallaxFactor;

	// TODO: on 3DS, generate a tile/swizzle hash so that it doesn't have to be
	// recalculated each time
} TileLayer;

typedef struct {
	char tsName[0x100];
	u8 spriteIndex;
	int spacing;
	int maxTiles;
} Tileset;

extern u16 layerCount;

extern Tileset sceneTileset;
extern TileLayer* sceneLayers;

extern u16 cameraPosX;
extern u16 cameraPosY;

extern char sceneName[255];

int LoadScene(const char* sceneName);
void FreeScene();
int LoadTileset(const char* name);

void DrawLayer(int layer);

// for moving the camera from within scripts
inline int GetCameraPosX() {
	return cameraPosX;
}

inline int GetCameraPosY() {
	return cameraPosY;
}

inline void OffsetCamera(int x, int y) {
	cameraPosX += x;
	cameraPosY += y;
}

#endif
