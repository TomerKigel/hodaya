#include "Player.h"

Player::Player() : UserName_(nullptr), Password_(nullptr), score_(0)
{

}
Player::Player(char* name, char* passcode) {
	UserName_ = new char[100];
	Password_ = new char[100];
	int i = 0;
	while(name[i] != '\0')
	{
		this->UserName_[i] = name[i];
		i++;
	}
	this->UserName_[i] = '\0';

	i = 0;
	while (passcode[i] != '\0')
	{
		this->Password_[i] = passcode[i];
		i++;
	}
	this->Password_[i] = '\0';
	score_ = 0;
}

Player::~Player()
{
	if(UserName_ != nullptr)
		delete [] UserName_;
	if (Password_ != nullptr)
		delete [] Password_;
}

char* Player::name() const
{
	return UserName_;
}
char* Player::pass() const
{
	return Password_;
}

int Player::score() const
{
	return score_;
}

void Player::increase_score()
{
	score_++;
}

int Player::get_type()
{
	return 0;
}