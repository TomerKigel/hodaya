#pragma once
#include "Player.h"

class Barracuda : public Player
{
private:

public:
	Barracuda(char* name, char* passcode);
	~Barracuda();
	int get_type();

};
