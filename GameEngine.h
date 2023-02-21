#pragma once
#include "League.h"
#include "Dynamic_array.h"
#include "FileManager.h"

class GameEngine
{
private:
	bool running;
	League *running_league;
	Dynamic_array<Player*> player_database;
	Player *selected_player;

	Player *search_name(char* name);
	void add_player_to_running_league(Player* pl);
public:
	void recall_players();
	void recall_league();
	GameEngine();
	~GameEngine();
	void run();
	void run(int argc,char* argv[]);
	void print_menu();
	void register_player();
	void login_player();
	void league_service();
	void join_league();
	void create_league(int type);
	void play_computer();
	void print_leaderboard();

};