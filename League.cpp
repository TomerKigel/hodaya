#include "League.h"
#include <iostream>

League::League(int type)
{
	type_ = type;
}
League::~League()
{

}

bool League::add_player(Player* pl)
{
	bool player_exists = false;
	for (size_t i = 0; i < list_of_Players.size(); i++)
	{
		if (strcmp(list_of_Players[i]->name(), pl->name()) == 0)
		{
			player_exists = true;
		}
	}
	if (!player_exists)
		this->list_of_Players.add(pl);
	else
		return false;
	return true;
}

int League::get_type()
{
	return type_;
}