#include "Barracuda.h"

Barracuda::Barracuda(char* name, char* passcode) : Player(name, passcode) {}

int Barracuda::get_type()
{
	return 8;
}