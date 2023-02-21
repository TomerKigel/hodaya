#pragma once
#include "Player.h"

class Dog : public Player
{
private:

public:
	Dog(char* name, char* passcode);
	~Dog();
	int get_type();

};
