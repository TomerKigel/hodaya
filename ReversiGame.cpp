#include "ReversiGame.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

ReversiGame::ReversiGame(int difficulty, int board_size)
{
	game_field = new Board(board_size);
	A = nullptr;
	B = nullptr;
	difficulty_ = difficulty;
}


ReversiGame::ReversiGame(Player* a,int difficulty,int board_size)
{
	game_field = new Board(board_size);
	A = a;
	B = nullptr;
	random_swap(&A, &B);
	difficulty_ = difficulty;
}
ReversiGame::ReversiGame(Player* a, Player* b, int board_size)
{
	game_field = new Board(board_size);
	A = a;
	B = b; 
	random_swap(&A, &B);
	difficulty_ = 0;
}

void ReversiGame::random_swap(Player** a, Player** b)
{
	int shuffles = rand() % 6;
	while (shuffles > 0)
	{
			shuffles--;
			Player** temp = a;
			a = b;
			b = temp;
	}
}


ReversiGame::~ReversiGame()
{
	delete game_field;
}
void ReversiGame::start_game()
{
	while (!game_field->is_board_full())
	{
		game_field->print();
		Dynamic_array<int> valid_moves = get_valid_turns('X');
		if (valid_moves.size() == 0)
			break;
		if (A == nullptr)
		{
			if (difficulty_ == 1)
			{
				easy_computer_turn('X');
			}
			else if(difficulty_ == 2)
			{
				medium_computer_turn('X');
			}
			else
			{
				hard_computer_turn('X');
			}
		}
		else
		{
			human_turn(A);
		}

		game_field->print(); 
		valid_moves = get_valid_turns('O');
		if (valid_moves.size() == 0)
			break;
		if (B == nullptr)
		{
			if (difficulty_ == 1)
			{
				easy_computer_turn('O');
			}
			else if (difficulty_ == 2)
			{
				medium_computer_turn('O');
			}
			else
			{
				hard_computer_turn('O');
			}
		}
		else
		{
			human_turn(B);
		}
	}

	game_field->print();
	char winner = game_field->get_leader();
	if (winner == 'X')
	{
		if (A == nullptr)
			cout << "Winner is: Computer!" << endl;
		else
		{
			cout << "Winner is: " << A->name() << endl;
			A->increase_score(); // change to correct
		}

	}
	else
	{
		if(B == nullptr)
			cout << "Winner is: Computer!" << endl;
		else
		{
			cout << "Winner is: " << B->name() << endl;
			B->increase_score(); // change to correct
		}
	}

}

Dynamic_array<int> ReversiGame::get_valid_turns(char type)
{
	Dynamic_array<int> valid_moves;
	int loc = 0;
	for (int i = 0; i < game_field->size(); i++)
	{
		for (int j = 0; j < game_field->size(); j++)
		{
			if (game_field->is_valid_move(i, j, type)) {
				valid_moves.add(i);
				valid_moves.add(j);
				valid_moves[loc++] = i;
				valid_moves[loc++] = j;
			}
		}
	}
	return valid_moves;
}

void ReversiGame::easy_computer_turn(char type)
{

	cout << "Computer is playing." << endl;
	Dynamic_array<int> valid_moves = get_valid_turns(type);
	int random_pick = rand() % (valid_moves.size()/2);
	if (valid_moves.size() != 0)
		game_field->place_piece(valid_moves[random_pick*2], valid_moves[random_pick*2+1], type);
	cout << "Computer played:" << valid_moves[random_pick * 2] << " , " << valid_moves[random_pick * 2 + 1] << endl;

}

void ReversiGame::medium_computer_turn(char type)
{

	cout << "Computer is playing." << endl;
	Dynamic_array<int> valid_moves = get_valid_turns(type);
	int best_move = 0, best_val = 0;
	for (int i = 0; i < valid_moves.size()/2; i++)
	{
		int val = game_field->check_place_piece(valid_moves[i*2], valid_moves[i*2+1], type);
		if (val > best_val)
		{
			best_val = val;
			best_move = i;
		}
	}
	if(valid_moves.size() != 0)
		game_field->place_piece(valid_moves[best_move*2], valid_moves[best_move*2+1], type);

	cout << "Computer played:" << valid_moves[best_move*2] << " , " << valid_moves[best_move*2 + 1] << endl;
}

void ReversiGame::hard_computer_turn(char type)
{
	cout << "Computer is playing." << endl;
	Dynamic_array<int> valid_moves = get_valid_turns(type);
	int best_move = 0, best_val = 0;
	for (int i = 0; i < valid_moves.size() / 2; i++)
	{
		int val = game_field->check_place_piece(valid_moves[i * 2], valid_moves[i * 2 + 1], type);
		if (val > best_val)
		{
			best_val = val;
			best_move = i;
		}
	}
	if (valid_moves.size() != 0)
		game_field->place_piece(valid_moves[best_move * 2], valid_moves[best_move * 2 + 1], type);

	cout << "Computer played:" << valid_moves[best_move * 2] << " , " << valid_moves[best_move * 2 + 1] << endl;
}

void ReversiGame::human_turn(Player *pl)
{
	char type;
	if (pl == A)
		type = 'X';
	else
		type = 'O';

	int row,column;
	do {
		cout << A->name() << " it is your turn. you are placing:" << type << "\nPick a row and column to place a piece." << endl;
		cout << "row:";
		cin >> row;
		cout << "column:";
		cin >> column;
		if (!game_field->is_valid_move(row, column, type))
			cout << "Invalid move!" << endl;
	} while (!game_field->place_piece(row, column, type));
}