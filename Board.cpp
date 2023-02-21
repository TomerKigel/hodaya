#include "Board.h"
#include <iostream>

using std::cout;
using std::endl;

Board::Board()
{
	size_ = 8;
	for (int i = 0; i < size_; i++)
	{
		Dynamic_array<char> row;
		game_board.add(row);
		for (int j = 0; j < size_; j++)
		{
			char val = '.';
			game_board[i].add(val);
		}
	}
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			game_board[i][j] = '.';
		}
	}
	player_a_pieces_count = 2;
	player_b_pieces_count = 2;
	game_board[size_ / 2][size_ / 2] = 'O';
	game_board[size_ / 2][size_ / 2 - 1] = 'O';
	game_board[size_ / 2 - 1][size_ / 2] = 'X';
	game_board[size_ / 2 - 1][size_ / 2 - 1] = 'X';
}

Board::Board(int size)
{
	size_ = size;
	for (int i = 0; i < size_; i++)
	{
		Dynamic_array<char> row;
		game_board.add(row);
		for (int j = 0; j < size_; j++)
		{
			char val = '.';
			game_board[i].add(val); 
		}
	}
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			game_board[i][j] = '.';
		}
	}
	player_a_pieces_count = 2;
	player_b_pieces_count = 2;
	game_board[size_ / 2][size_ / 2] = 'X';
	game_board[size_ / 2][size_ / 2 - 1] = 'O';
	game_board[size_ / 2 - 1][size_ / 2] = 'O';
	game_board[size_ / 2 - 1][size_ / 2 - 1] = 'X';
}

Board::Board(Board& cpy)
{
	size_ = cpy.size();
	for (int i = 0; i < size_; i++)
	{
		Dynamic_array<char> row;
		game_board.add(row);
		for (int j = 0; j < size_; j++)
		{
			game_board[i].add(cpy.game_board[i][j]);
			game_board[i][j] = cpy.game_board[i][j];
		}
	}
}


Board::~Board()
{

}

void Board::print()
{
	cout << "Amount of X's on the board:" << player_a_pieces_count << endl;
	cout << "Amount of O's on the board:" << player_b_pieces_count << endl << endl;
	cout << "Board:\n\t";
	for (int i = 0; i < size_; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < size_; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < size_; j++)
		{
			cout << game_board[i][j] << "\t";
		}
		cout << endl;
	}
}

char Board::get_leader() const
{
	if (player_a_pieces_count > player_b_pieces_count)
	{
		return 'X';
	}
	return 'O';
}

bool Board::is_board_full()
{
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			if (game_board[i][j] == '.')
				return false;
		}
	}
	return true;
}


int Board::place_piece(int row, int column, char type)
{
	int colored_count = 0;
	if (is_valid_move(row, column, type)) {
		game_board[row][column] = type;
		if (check_row_to_the_left(row, column, type))
			colored_count += color_left(row, column, type);
		if (check_row_to_the_right(row, column, type))
			colored_count += color_right(row, column, type);
		if(check_column_to_the_bottom(row, column, type))
			colored_count += color_bottom(row, column, type);
		if(check_column_to_the_top(row, column, type) )
			colored_count += color_top(row, column, type);
		if(check_diagonal_left_up(row, column, type) )
			colored_count += color_left_up(row, column, type);
		if(check_diagonal_left_down(row, column, type)) 
			colored_count += color_left_down(row, column, type);
		if(check_diagonal_right_up(row, column, type) )
			colored_count += color_right_up(row, column, type);
		if(check_diagonal_right_down(row, column, type))
			colored_count += color_right_down(row, column, type);

		if (type == 'X')
		{
			player_a_pieces_count += 1 + colored_count;
			player_b_pieces_count -= colored_count;
		}
		else
		{
			player_b_pieces_count += 1 + colored_count;
			player_a_pieces_count -= colored_count;
		}

		return colored_count;
	}
	return 0;
}

int Board::check_place_piece(int row, int column, char type)
{
	int colored_count = 0;
	if (is_valid_move(row, column, type)) {
		if (check_row_to_the_left(row, column, type))
			colored_count += color_left(row, column, type,true);
		if (check_row_to_the_right(row, column, type))
			colored_count += color_right(row, column, type, true);
		if (check_column_to_the_bottom(row, column, type))
			colored_count += color_bottom(row, column, type, true);
		if (check_column_to_the_top(row, column, type))
			colored_count += color_top(row, column, type, true);
		if (check_diagonal_left_up(row, column, type))
			colored_count += color_left_up(row, column, type, true);
		if (check_diagonal_left_down(row, column, type))
			colored_count += color_left_down(row, column, type, true);
		if (check_diagonal_right_up(row, column, type))
			colored_count += color_right_up(row, column, type, true);
		if (check_diagonal_right_down(row, column, type))
			colored_count += color_right_down(row, column, type, true);
		return colored_count;
	}
	return 0;
}


bool Board::is_valid_move(int row, int column, char type)
{
	if (row >= size_ || row < 0 || column < 0 || column >= size_)
		return false;
	if (game_board[row][column] != '.')
		return false;
	if (
		check_row_to_the_left( row,  column,  type) ||
		check_row_to_the_right(row, column, type) ||
		check_column_to_the_bottom(row, column, type) ||
		check_column_to_the_top(row, column, type) ||
		check_diagonal_left_up(row, column, type) ||
		check_diagonal_left_down(row, column, type) ||
		check_diagonal_right_up(row, column, type) ||
		check_diagonal_right_down(row, column, type))
		return true;
	return false;
}

bool Board::check_row_to_the_left(int row, int column, char type)
{
	int i = 1;
	while (column-i > 0){
		if (game_board[row][column-i] == '.') {
			return false;
		}
		if (game_board[row][column - i] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_row_to_the_right(int row, int column, char type) 
{
	int i = 1;
	while (column + i < size_) {
		if (game_board[row][column + i] == '.') {
			return false;
		}
		if (game_board[row][column + i] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_column_to_the_bottom(int row, int column, char type) 
{
	int i = 1;
	while (row+i < size_) {
		if (game_board[row+i][column] == '.') {
			return false;
		}
		if (game_board[row+i][column] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_column_to_the_top(int row, int column, char type) 
{
	int i = 1;
	while (row - i > 0) {
		if (game_board[row-i][column] == '.') {
			return false;
		}
		if (game_board[row-i][column] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_diagonal_left_up(int row, int column, char type) 
{
	int i = 1;
	while (row-i > 0 && column-i > 0) {
		if (game_board[row - i][column-i] == '.') {
			return false;
		}
		if (game_board[row - i][column-i] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_diagonal_left_down(int row, int column, char type) 
{
	int i = 1;
	while (row + i < size_ && column - i > 0) {
		if (game_board[row + i][column - i] == '.') {
			return false;
		}
		if (game_board[row + i][column - i] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_diagonal_right_up(int row, int column, char type) 
{
	int i = 1;
	while (row - i > 0 && column + i < size_) {
		if (game_board[row - i][column + i] == '.') {
			return false;
		}
		if (game_board[row - i][column + i] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
bool Board::check_diagonal_right_down(int row, int column, char type) 
{
	int i = 1;
	while (row + i < size_ && column + i < size_) {
		if (game_board[row + i][column + i] == '.') {
			return false;
		}
		if (game_board[row + i][column + i] == type) {
			if (i == 1)
				return false;
			return true;
		}
		i++;
	}
	return false;
}
int Board::color_left(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row][column - i] != type) {
		if (!off)
		game_board[row][column - i] = type;
		i++;
	}
	return i - 1;
}
int Board::color_right(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row][column + i] != type) {
		if (!off)
		game_board[row][column + i] = type;
		i++;
	}
	return i - 1;
}
int Board::color_bottom(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row+i][column] != type) {
		if (!off)
		game_board[row+i][column] = type;
		i++;
	}
	return i - 1;
}
int Board::color_top(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row-i][column] != type) {
		if (!off)
		game_board[row-i][column] = type;
		i++;
	}
	return i - 1;
}
int Board::color_left_up(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row-i][column - i] != type) {
		if (!off)
		game_board[row-i][column - i] = type;
		i++;
	}
	return i - 1;
}
int Board::color_left_down(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row+i][column - i] != type) {
		if (!off)
		game_board[row+i][column - i] = type;
		i++;
	}
	return i - 1;
}
int Board::color_right_up(int row, int column, char type,bool off)
{
	int i = 1;
	while (game_board[row-i][column + i] != type) {
		if (!off)
		game_board[row-i][column + i] = type;
		i++;
	}
	return i - 1;
}

int Board::color_right_down(int row, int column, char type, bool off)
{
	int i = 1;
	while (game_board[row+i][column + i] != type) {
		if(!off)
		game_board[row+i][column + i] = type;
		i++;
	}
	return i - 1;
}



int Board::size() const
{
	return size_;
}


