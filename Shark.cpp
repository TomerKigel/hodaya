#include "Shark.h"

Shark::Shark(char* name, char* passcode) : Player(name, passcode) {}

int Shark::get_type()
{
	return 2;
}