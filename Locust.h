#pragma once
#include "Player.h"

class Locust : public Player
{
private:

public:
	Locust(char* name, char* passcode);
	~Locust();
	int get_type();

};
