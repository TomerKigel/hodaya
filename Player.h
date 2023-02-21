#pragma once

class Player
{
private:
	char *UserName_;
	char *Password_;
	int score_;
public:
	char* name() const;
	char* pass() const;
	int score() const;
	void increase_score();
	virtual int get_type();
	Player();
	Player(char* name, char* passcode);
	~Player();
};

