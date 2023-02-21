#include "Cat.h"

Cat::Cat(char* name, char* passcode) : Player(name, passcode) {}

int Cat::get_type()
{
	return 3;
}