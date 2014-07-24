#include "SDLManager.h"

// Constructor
SDLManager::SDLManager( int width, int height, int bitsPerPixel, string windowTitle ) {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );
	SDL_WM_SetCaption( windowTitle.c_str(), NULL );
	screen = SDL_SetVideoMode( width, height, bitsPerPixel, SDL_SWSURFACE );
	this->background = new Surface( "background.png", false );
	
	if( screen == NULL ) {
		//Log some error here
		this->initialised = false;
	} else {
		this->initialised = true;
	}

	this->initialised = this->background->loaded();
}

// Destructor
SDLManager::~SDLManager( void ) {
	SDL_FreeSurface(screen);
	delete this->background;
	SDL_Quit();
}

bool SDLManager::isInitialised( void ) {
	return this->initialised;
}

SDL_Surface *SDLManager::getScreen( void ) {
	return this->screen;
}

void SDLManager::preFrame( void ) {
	Uint32 color = SDL_MapRGB( this->screen->format, 81, 162, 255 );
	SDL_FillRect( this->screen, NULL, color );
	this->background->draw( this->screen, 0, 0 );
}

int SDLManager::postFrame( void ) {
	return SDL_Flip( this->screen ); //0 success | -1 Failure
}