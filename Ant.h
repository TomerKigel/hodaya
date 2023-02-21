#pragma once
#include "Player.h"

class Ant : public Player
{
private:

public:
	Ant(char* name, char* passcode);
	~Ant();
	int get_type();

};
