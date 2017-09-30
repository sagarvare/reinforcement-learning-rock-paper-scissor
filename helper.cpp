#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "Game.h"

using namespace std;
//Constructor
Game::Game(void){
	cout << "Starting a new game" <<"\n\n";
}

void Game::display(void){
	//Display the current board
}

void Game::switchBoards(void){
	//switch the boards
	int * temp;
	temp = &old_board;
	old_board = new_board;
	new_board = temp;
}

void Game::updateBoard(void){
	//Run an update rule
}

void Game::run(int num){
	//Run num number of iterations of the game
	for (int i=0;i<num;i++){
		display();
		switchBoards();
		updateBoard();
	}
}