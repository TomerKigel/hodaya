#pragma once
#include "Player.h"

class Dolphine : public Player
{
private:

public:
	Dolphine(char* name, char* passcode);
	~Dolphine();
	int get_type();

};
