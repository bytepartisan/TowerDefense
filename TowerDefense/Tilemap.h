#ifndef TILEMAP_H
#define TILEMAP_H

#include "SDL.h"
#include "SDL_image.h"
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;
using std::ifstream;
using std::ofstream;
using std::endl;

const int TILE_MAP_WIDTH = 8;
const int TILE_MAP_HEIGHT = 8;
const int MAX_TILES = 64;
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 30;
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

struct tileInfo_s {
	int type; // 0 - 64 where 0 is blank and 1 to 64 index into image/tiles
	bool solid;
	SDL_Rect clip;
	string data;
};

class TileMap {
public:
	TileMap( string fileName );
	~TileMap( void );

	void display( SDL_Surface *destination );
	bool isMapLoaded( void );
	tileInfo_s getTileInfo( int x, int y );
	void setTileInfo( int x, int y, int type, bool solid );
private:
	tileInfo_s tileMapInfo[MAP_HEIGHT][MAP_WIDTH]; //[rows][columns]
	SDL_Rect tileMapClips[MAX_TILES];
	SDL_Surface *imageSurface;
	bool mapLoaded;

	bool loadImageMap( string fileName );
};

#endif