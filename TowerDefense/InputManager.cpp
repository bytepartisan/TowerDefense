#include "InputManager.h"

// Constructor
InputManager::InputManager( void ) {
	for( int i = 0; i < 324; i++ ) { this->keyPressed[i] = false; }
	this->windowQuit = false;
	this->mouse.leftButtonDown = false;
	this->mouse.rightButtonDown = false;
}

// Destructor
InputManager::~InputManager( void ) {

}

void InputManager::pollEvents( void ) {
	while( SDL_PollEvent(&this->sdlEvent) ) {
		if( this->sdlEvent.type == SDL_KEYDOWN ) {
			this->keyPressed[sdlEvent.key.keysym.sym] = true;
		} else if( this->sdlEvent.type == SDL_KEYDOWN ) {
			this->keyPressed[sdlEvent.key.keysym.sym] = false;
		} else if( this->sdlEvent.type == SDL_QUIT ) {
			this->windowQuit = true;
		} else if( this->sdlEvent.type == SDL_MOUSEMOTION ) {
			this->mouse.x = this->sdlEvent.motion.x;
			this->mouse.y = this->sdlEvent.motion.y;
		} else if( this->sdlEvent.type == SDL_MOUSEBUTTONDOWN ) {
			this->mouse.x = this->sdlEvent.button.x;
			this->mouse.y = this->sdlEvent.button.y;
			if( this->sdlEvent.button.button == SDL_BUTTON_LEFT ) {
				this->mouse.leftButtonDown = true;
			} else if( this->sdlEvent.button.button == SDL_BUTTON_RIGHT ){
				this->mouse.rightButtonDown = true;
			}
		} else if( this->sdlEvent.type == SDL_MOUSEBUTTONUP ) {
			this->mouse.x = this->sdlEvent.button.x;
			this->mouse.y = this->sdlEvent.button.y;
			if( this->sdlEvent.button.button == SDL_BUTTON_LEFT ) {
				this->mouse.leftButtonDown = false;
			} else if( this->sdlEvent.button.button == SDL_BUTTON_RIGHT ){
				this->mouse.rightButtonDown = false;
			}
		}
	}
}

bool InputManager::isKeyDown( int key ) {
	return this->keyPressed[key];
}

bool InputManager::getWindowQuit( void ) {
	return this->windowQuit;
}

mouseInfo InputManager::getMouse( void ) {
	return this->mouse;
}