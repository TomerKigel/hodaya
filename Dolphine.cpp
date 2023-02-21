#include "Dolphine.h"

Dolphine::Dolphine(char* name, char* passcode) : Player(name, passcode) {}

int Dolphine::get_type()
{
	return 2;
}