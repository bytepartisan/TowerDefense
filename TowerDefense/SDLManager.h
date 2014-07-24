#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include "SDL.h"
#include "Surface.h"
#include <string>
using namespace std;

class SDLManager {
public:
	SDLManager( int width, int height, int bitsPerPixel, string windowTitle );
	~SDLManager( void );

	bool isInitialised( void );
	SDL_Surface *getScreen( void );
	void preFrame( void );
	int postFrame( void );
private:
	Surface *background;
	SDL_Surface *screen;
	bool initialised;
};

#endif