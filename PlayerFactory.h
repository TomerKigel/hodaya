#pragma once
#include "Dolphine.h"
#include "Cat.h"
#include "Dog.h"
#include "Shark.h"
#include "Barracuda.h"
#include "Ant.h"
#include "Locust.h"
#include "Wasp.h"
class PlayerFactory
{
public:
	static Player* createPlayer(int type,char *name, char* pass)
	{
		switch (type)
		{
		case 1:
			return  new Dolphine(name, pass);
		case 2:
			return new Cat(name, pass);
		case 3:
			return new Dog(name, pass);
		case 4:
			return new Shark(name, pass);
		case 5:
			return new Barracuda(name, pass);
		case 6:
			return new Ant(name, pass);
		case 7:
			return new Locust(name, pass);
		case 8:
			return new Wasp(name, pass);
		default:
			return nullptr;
		}
	}
};