#ifndef SURFACE_H
#define SURFACE_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;

// Represents a single surface
class Surface {
public:
	Surface( string fileName, bool colorKey );
	~Surface( void );
	bool loaded( void );
	SDL_Surface *get( void );
	void draw( SDL_Surface *destination, int x, int y );
private:
	SDL_Surface *sdlSurface;
	bool fileLoaded;
};

#endif