#include "Surface.h"

Surface::Surface( string fileName, bool colorKey ) {
	//Load image onto surface
	SDL_Surface *tmpSurface = IMG_Load( fileName.c_str() );
	
	if( tmpSurface != NULL ) { 
		this->sdlSurface = SDL_DisplayFormat(tmpSurface);

		SDL_FreeSurface(tmpSurface);

		if( this->sdlSurface == NULL ) { 
			SDL_FreeSurface ( this->sdlSurface ); 
			this->fileLoaded = false; 
		}

		if( colorKey ) {
			// Add color key for transparent pixels
			Uint32 iColorKey = SDL_MapRGB( this->sdlSurface->format, 0, 0, 255 );
			SDL_SetColorKey( this->sdlSurface, SDL_SRCCOLORKEY, iColorKey );
		}

		this->fileLoaded = true;

	} else { 
		this->fileLoaded = false; 
	}

}

Surface::~Surface( void ) {
	SDL_FreeSurface( this->sdlSurface );
}

SDL_Surface *Surface::get( void ) {
	return this->sdlSurface;
}

bool Surface::loaded( void ) {
	return this->fileLoaded;
}

void Surface::draw( SDL_Surface *destination, int x, int y) {
	SDL_Rect tmp;
	tmp.x = x;
	tmp.y = y;
	SDL_BlitSurface( this->sdlSurface, NULL, destination, &tmp );
}