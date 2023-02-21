#include "Ant.h"

Ant::Ant(char* name, char* passcode) : Player(name,passcode){}

int Ant::get_type()
{
	return 8;
}