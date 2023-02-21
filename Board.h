#pragma once
#include "Dynamic_array.h"

class Board
{
private:
	int size_;
	Dynamic_array<Dynamic_array<char>> game_board;

	bool check_row_to_the_left(int row, int column, char type) ;
	bool check_row_to_the_right(int row, int column, char type) ;
	bool check_column_to_the_bottom(int row, int column, char type) ;
	bool check_column_to_the_top(int row, int column, char type);
	bool check_diagonal_left_up(int row, int column, char type);
	bool check_diagonal_left_down(int row, int column, char type);
	bool check_diagonal_right_up(int row, int column, char type);
	bool check_diagonal_right_down(int row, int column, char type);
	int color_left(int row, int column, char type,bool off = false);
	int color_right(int row, int column, char type, bool off = false);
	int color_bottom(int row, int column, char type, bool off = false);
	int color_top(int row, int column, char type, bool off = false);
	int color_left_up(int row, int column, char type, bool off = false);
	int color_left_down(int row, int column, char type, bool off = false);
	int color_right_up(int row, int column, char type, bool off = false);
	int color_right_down(int row, int column, char type, bool off = false);


	int player_a_pieces_count;
	int player_b_pieces_count;
public:
	Board();
	Board(int size);
	Board(Board &cpy);
	~Board();
	void print();
	int place_piece(int row, int column, char type);
	int check_place_piece(int row, int column, char type);
	bool is_valid_move(int row, int column, char type);
	int size() const;
	char get_leader() const;
	bool is_board_full();
};