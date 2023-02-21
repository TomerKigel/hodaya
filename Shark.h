#pragma once
#include "Player.h"

class Shark : public Player
{
private:

public:
	Shark(char* name, char* passcode);
	~Shark();
	int get_type();

};
