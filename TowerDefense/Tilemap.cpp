#include "Tilemap.h"

void log( const char* msg ) {
	ofstream logFile( "log.txt", ios::app );
	logFile << msg << endl;
}

TileMap::TileMap( string filename ) {
	
	int i = 0;
	this->mapLoaded = false;
	char line[128];
	bool imageLoaded = this->loadImageMap( "sheet.png" );

	if( imageLoaded ) {

		for( int j = 0; j < TILE_MAP_HEIGHT; j++ ) {
			for( int k = 0; k < TILE_MAP_WIDTH; k++ ) {
				SDL_Rect rect;
				rect.h = TILE_HEIGHT;
				rect.w = TILE_WIDTH;
				rect.x = k * TILE_WIDTH;
				rect.y = j * TILE_HEIGHT;
				tileMapClips[i] = rect;
				i++;
			}
		}

		ifstream mapFile( filename.c_str(), ios::in );
		if( mapFile ){
			int y=0;

			while( mapFile >> line )
			{
				int x=0;
				char *tokenPtr;

				tokenPtr = strtok(line,",");

				while( tokenPtr != NULL )
				{
					tileInfo_s tmp;
					tmp.data = tokenPtr;

					this->tileMapInfo[y][x] = tmp;

					tokenPtr = strtok( NULL, "," );
					x++;
				}

				y++;
			}

			for( int y = 0; y < MAP_HEIGHT; y++ ) {
				for( int x = 0; x < MAP_WIDTH; x++ ) {
					i = 0;
					char tileData[128];
					char *tokenPtr;
					sprintf(tileData,"%s",tileMapInfo[y][x].data.c_str());
					tokenPtr = strtok(tileData,":");
					while( tokenPtr != NULL ) {
						if( i == 0 ) {
							int iType = atoi(tokenPtr);
							this->tileMapInfo[y][x].type = iType;
							if( iType > 0 ) { this->tileMapInfo[y][x].clip = tileMapClips[iType - 1]; }
						} else if( i == 1 ) {
							if( atoi(tokenPtr) == 0 ) {
								this->tileMapInfo[y][x].solid = false;
							} else {
								this->tileMapInfo[y][x].solid = true;
							}
						}
						i++;
						tokenPtr = strtok( NULL, ":" );
					}
				}
			}

			this->mapLoaded = true;

		} else {
			//generate a blank map
			for( int y = 0; y < MAP_HEIGHT; y++ ) {
				for( int x = 0; x < MAP_WIDTH; x++ ) {
					this->tileMapInfo[y][x].type = 0;
					this->tileMapInfo[y][x].solid = false;
				}
			}
		}

	}
}

TileMap::~TileMap( void ) {
	SDL_FreeSurface( imageSurface );
	string filename = "map.txt";
	ofstream mapFile( filename.c_str(), ios::out );
	if( mapFile ) { 
		for( int y = 0; y < MAP_HEIGHT; y++ ) {
			for( int x = 0; x < MAP_WIDTH; x++ ) {
				mapFile << this->tileMapInfo[y][x].type << ":";

				if( this->tileMapInfo[y][x].solid ) {
					mapFile << "1";
				} else {
					mapFile << "0";
				}				

				if( x < ( MAP_WIDTH - 1 ) ) {
					mapFile << ",";
				} else {
					mapFile << endl;
				}
			}
		}
	}
}

void TileMap::display( SDL_Surface *destination ) {
	for( int y = 0; y < MAP_HEIGHT; y++ ) {
		for( int x = 0; x < MAP_WIDTH; x++ ) {
			if( tileMapInfo[y][x].type > 0 ) {
				SDL_Rect coords;
				coords.x = x*TILE_WIDTH;
				coords.y = y*TILE_HEIGHT;
				SDL_BlitSurface( this->imageSurface, &this->tileMapInfo[y][x].clip, destination, &coords );
			}
		}
	}
}

bool TileMap::isMapLoaded( void ) {
	return this->mapLoaded;
}

bool TileMap::loadImageMap( string fileName ) {
	//Load image onto surface
	SDL_Surface *tmpSurface = IMG_Load( fileName.c_str() );
	if( tmpSurface == NULL ) { return false; }

	this->imageSurface = SDL_DisplayFormat(tmpSurface);

	SDL_FreeSurface(tmpSurface);

	if( this->imageSurface == NULL ) { 
		SDL_FreeSurface ( this->imageSurface ); 
		return false; 
	}

	// Add color key for transparent pixels
	Uint32 colorKey = SDL_MapRGB( this->imageSurface->format, 0, 0, 255 );
	SDL_SetColorKey( this->imageSurface, SDL_SRCCOLORKEY, colorKey );

	return true;

}

tileInfo_s TileMap::getTileInfo( int x, int y ) {
	return this->tileMapInfo[y][x];
}

void TileMap::setTileInfo( int x, int y, int type, bool solid ) {
	
	tileMapInfo[y][x].type = type;
	tileMapInfo[y][x].solid = solid;

	if( type > 0 ) {
		tileMapInfo[y][x].clip = tileMapClips[type - 1];
	}
	
}