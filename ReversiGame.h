#pragma once
#include "Board.h"
#include "Player.h"

class ReversiGame
{
private:
	Board *game_field;
	Player *A, *B;
	void random_swap(Player** a, Player** b);
	int difficulty_;

	void easy_computer_turn(char type);
	void medium_computer_turn(char type);
	void hard_computer_turn(char type);
	void human_turn(Player* pl);
	Dynamic_array<int> get_valid_turns(char type);
public:
	ReversiGame(int difficulty, int board_size);
	ReversiGame(Player* a,int difficulty, int board_size);
	ReversiGame(Player *a,Player *b, int board_size);
	~ReversiGame();
	void start_game();
};

