#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SDL.h"

struct mouseInfo {
	int x;
	int y;
	bool leftButtonDown;
	bool rightButtonDown;
};


class InputManager {
public:
	InputManager( void );
	~InputManager( void );
	void pollEvents( void );
	bool isKeyDown( int key );
	bool getWindowQuit( void );
	mouseInfo getMouse( void );
private:
	SDL_Event sdlEvent;
	bool keyPressed[324];
	bool windowQuit;
	mouseInfo mouse;
};

#endif