#pragma once
#include "Player.h"

class Cat : public Player
{
private:

public:
	Cat(char* name, char* passcode);
	~Cat();
	int get_type();

};
