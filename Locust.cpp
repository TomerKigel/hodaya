#include "Locust.h"

Locust::Locust(char* name, char* passcode) : Player(name, passcode) {}

int Locust::get_type()
{
	return 2;
}