#include "Dog.h"

Dog::Dog(char* name, char* passcode) : Player(name, passcode) {}

int Dog::get_type()
{
	return 2;
}