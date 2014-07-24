#include "SDL.h"
#include <new>
#include "GameState.h"
#include "InputManager.h"
#include "SDLManager.h"
#include "TileMap.h"
#include "Surface.h"

bool checkBound( int x, int y, int xmin, int xmax, int ymin, int ymax ) {
	if( x >= xmin && x <= xmax && y >= ymin && y <= ymax ) {
		return true;
	} else {
		return false;
	}
}

int main( int argc, char **argv ) {

	bool leftBlockUpdated = false;
	bool rightBlockUpdated = false;

	//Initialise everything
	SDLManager sdlManager( 640, 480, 32, "RPG Engine" );
	GameState gameState( GAME_OFF );
	InputManager inputManager;
	TileMap tileMap( "map.txt" );
	Surface selector( "selector.png", true );
	
	if( sdlManager.isInitialised() ) {
		gameState.set( GAME_ON );
	}

	while( gameState.get() != GAME_OFF ) {

		inputManager.pollEvents();
		if( inputManager.isKeyDown( SDLK_ESCAPE ) ) {
			gameState.set( GAME_OFF );
		} else if ( inputManager.getWindowQuit() ) {
			gameState.set( GAME_OFF );
		}

		if( inputManager.getMouse().leftButtonDown && !leftBlockUpdated ) {
			int tileType = 0;
			int tileX;
			int tileY;
			mouseInfo m = inputManager.getMouse();

			for( int y = 0; y < MAP_HEIGHT; y++ ) {
				for( int x = 0; x < MAP_WIDTH; x++ ) {
					if( checkBound( m.x, m.y, x*TILE_WIDTH, TILE_WIDTH*( x + 1), y*TILE_HEIGHT, TILE_HEIGHT*( y + 1 ) ) ) {
						tileX = x;
						tileY = y;
					}
				}
			}

			tileType = tileMap.getTileInfo( tileX, tileY ).type + 1;

			if( tileType > MAX_TILES ) {
				tileMap.setTileInfo( tileX, tileY, 0, true );
			} else {
				tileMap.setTileInfo( tileX, tileY, tileType, true );
			}

			leftBlockUpdated = true;

		} else if( !inputManager.getMouse().leftButtonDown && leftBlockUpdated ) {
			leftBlockUpdated = false;
		} else if ( inputManager.getMouse().rightButtonDown && !rightBlockUpdated ) {
			int tileType = 0;
			int tileX;
			int tileY;
			mouseInfo m = inputManager.getMouse();

			for( int y = 0; y < MAP_HEIGHT; y++ ) {
				for( int x = 0; x < MAP_WIDTH; x++ ) {
					if( checkBound( m.x, m.y, x*TILE_WIDTH, TILE_WIDTH*( x + 1), y*TILE_HEIGHT, TILE_HEIGHT*( y + 1 ) ) ) {
						tileX = x;
						tileY = y;
					}
				}
			}

			tileType = tileMap.getTileInfo( tileX, tileY ).type - 1;

			if( tileType < 0 ) {
				tileMap.setTileInfo( tileX, tileY, MAX_TILES, true );
			} else {
				tileMap.setTileInfo( tileX, tileY, tileType, true );
			}

			rightBlockUpdated = true;

		} else if ( !inputManager.getMouse().rightButtonDown && rightBlockUpdated ) {
			rightBlockUpdated = false;
		}

		// ================================================================ Pre Frame
		sdlManager.preFrame();
		
		// ================================================================ Render Scene
		tileMap.display( sdlManager.getScreen() );

		// ================================================================ Post Frame
		if( sdlManager.postFrame() == -1 ) {
			gameState.set( GAME_OFF );
		}

	}

	return 0;
}