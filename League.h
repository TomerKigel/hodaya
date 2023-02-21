#pragma once
#include "Player.h"
#include "Dynamic_array.h"

class League
{
private:
	int type_;
	Dynamic_array<Player*> list_of_Players;
public:
	League(int type);
	~League();
	bool add_player(Player *pl);
	int get_type();
};