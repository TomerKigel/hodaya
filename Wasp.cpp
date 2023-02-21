#include "Wasp.h"

Wasp::Wasp(char* name, char* passcode) : Player(name, passcode) {}

int Wasp::get_type()
{
	return 2;
}