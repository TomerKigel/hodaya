#pragma once
#include "Player.h"

class Wasp : public Player
{
private:

public:
	Wasp(char* name, char* passcode);
	~Wasp();
	int get_type();

};
