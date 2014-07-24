#ifndef GAMESTATE_H
#define GAMESTATE_H

const int GAME_OFF = 0;
const int GAME_ON = 1;
const int GAME_PAUSE = 2;

class GameState {
public:
	GameState( int gameState );
	~GameState( void );

	int get( void );
	void set( int gameState );

private:
	int state;
};

#endif