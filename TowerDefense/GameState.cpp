#include "GameState.h"

GameState::GameState( int gameState ) {
	GameState::state = gameState;
}

GameState::~GameState( void ) {

}

int GameState::get( void ) {
	return GameState::state;
}

void GameState::set( int gameState ) {
	this->state = gameState;
}