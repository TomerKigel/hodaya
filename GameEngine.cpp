//bool running;
//League running_league;

#include "GameEngine.h"
#include "PlayerFactory.h"
#include "ReversiGame.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

GameEngine::GameEngine()
{
	running = true;
	running_league = nullptr;
	selected_player = nullptr;
	recall_players();
	recall_league();
}

void GameEngine::recall_players()
{
	FileManager players("players.txt");
	Dynamic_array<char*> data = players.read_lines_from_file();
	char player_data[6][100];
	int a = 0,datum = 0,loc = 0;
		
	for (int i = 0; i < data.size(); i++)
	{
		while (data[i][a] != '\0' && data[i][a] != ',')
		{
			player_data[datum][loc] = data[i][a];
			a++;
			loc++;
		}
		player_data[datum][loc] = '\0';
		datum++;
		loc = 0;
		a = 0;
	}
	Player *p = PlayerFactory::createPlayer(atoi(player_data[2]), player_data[0], player_data[1]);
	for (size_t i = 0; i < atoi(player_data[3]); i++)
	{
		p->increase_score();
	}
	player_database.add(p);
}

void GameEngine::recall_league()
{
	FileManager league("league.txt");
	Dynamic_array<char*> data = league.read_lines_from_file();
	if (data.size() != 0) {
		create_league(atoi(data[0]));
		for (int i = 1; i < data.size(); i++)
		{
			for (int j = 0; j < player_database.size(); j++)
			{
				if (strcmp(data[i], player_database[j]->name()) == 0)
				{
					add_player_to_running_league(player_database[j]);
				}
			}
		}
	}
}


GameEngine::~GameEngine()
{
	delete running_league;
}

void GameEngine::print_menu()
{
	if (selected_player != nullptr)
		cout << "Currently logged-in player:" << selected_player->name() << endl << endl;
	if(running_league != nullptr)
		cout << "There is an active league." << endl << endl;
	else
		cout << "There is no active league." << endl << endl;

	cout << "Menu:" << endl;
	cout << "Select one of the following options:" << endl;
	cout << "\t1)Register" << endl;
	cout << "\t2)Log-in " << endl;
	cout << "\t3)Create or join an active league" << endl;
	cout << "\t4)Play computer" << endl;
	cout << "\t5)Print Leaderboard" << endl;
	cout << "\t0)Quit" << endl;
}



void GameEngine::run()
{
	char input = 0;
	while (running)
	{
		print_menu();
		cin >> input;
		switch (input)
		{
		case '0':
			running = false;
			break;
		case '1':
			register_player();
			break;
		case '2':
			login_player();
			break;
		case '3':
			league_service();
			break;
		case '4':
			play_computer();
			break;
		case '5':
			print_leaderboard();
			break;
		default:
			cout << "invalid option, please insert a number between 0 and 5." << endl;
		}
	}
}

void GameEngine::run(int argc,char *argv[])
{
	if (argc == 1)
	{
		run();
	}
	else
	{
		//make a test run here
	}
}

void GameEngine::register_player()
{
	cout << "Register a new player." << endl;
	cout << "\tPick a unique name:";
	char name[100], passcode[100];
	cin >> name;
	while (search_name(name) != nullptr)
	{
		cout << "Username already exists please choose a different name!" << endl;
		cout << "\tPick a unique name:";
		cin >> name;
	}
	cout << "\tPick a password:";
	cin >> passcode;

	int type;
	do
	{
		cout << "\tPick an animal from the list below:" << endl;
		cout << "\tMammels:" << endl;
		cout << "\t\t1.Dolphine" << endl;
		cout << "\t\t2.Dog" << endl;
		cout << "\t\t3.Cat" << endl;
		cout << "\tFish:" << endl;
		cout << "\t\t4.Shark" << endl;
		cout << "\t\t5.Barracuda" << endl;
		cout << "\tInsects:" << endl;
		cout << "\t\t6.Ant" << endl;
		cout << "\t\t7.Locust" << endl;
		cout << "\t\t8.Wasp" << endl;
		cin >> type;
	} while (type < 1 && type > 8);
		
	
	Player *new_player = PlayerFactory::createPlayer(type,name,passcode);
	player_database.add(new_player);
	FileManager players("players.txt");
	players.write_to_file(name,strlen(name));
	players.write_to_file(passcode, strlen(passcode));
	char buffer[100];
	_itoa_s(type, buffer, 10);
	players.write_to_file(buffer, strlen(buffer));
	char score[100];
	score[0] = '0';
	score[1] = '\0';
	players.write_to_file(score, 1);
	players.write_to_file_new_entry();
	cout << "Registered successfuly!" << endl << endl;
	selected_player = new_player;
}


void GameEngine::login_player()
{
	cout << "Login." << endl;
	cout << "\tUsername:";
	char name[100], passcode[100];
	cin >> name;
	Player *tplayer = search_name(name);
	if (tplayer == nullptr)
	{
		cout << "Username doesn't exist.\nPick option 1 in the menu to register with that username." << endl << endl;
		return;
	}
	cout << "\tPassword:";
	cin >> passcode;
	if (strcmp(tplayer->pass(), passcode) != 0) {
		cout << "Wrong password.\nExiting to main menu." << endl << endl;
		return;
	}
	cout << "Logged in sucessfuly!" << endl << endl;
	selected_player = tplayer;
}
		

void GameEngine::league_service()
{
	cout << "League menu:" << endl;
	cout << "\tChoose an option:" << endl;
	if(running_league == nullptr)
		cout << "\t\t1.Create a new league." << endl;
	else
		cout << "\t\t1.Join a running league." << endl;
	cout << "\t\t2.return to main menu." << endl;
	char input;
	while (true) {
		cin >> input;
		switch (input)
		{
		case '1':
			if (running_league == nullptr)
			{
				char leaguetype[2];
				do
				{
					cout << "\tChoose a league type:" << endl;
					cout << "\t\t1.Mammel League" << endl;
					cout << "\t\t2.Dolphine League" << endl;
					cout << "\t\t3.Dog League" << endl;
					cout << "\t\t4.Cat League" << endl;
					cout << "\t\t5.Fish League" << endl;
					cout << "\t\t6.Shark League" << endl;
					cout << "\t\t7.Barracuda League" << endl;
					cout << "\t\t8.Insect League" << endl;
					cout << "\t\t9.Ant League" << endl;
					cout << "\t\t10.Locust League" << endl;
					cout << "\t\t11.Wasp League" << endl;
					cout << "\t\t12.Open League" << endl;
					cin >> leaguetype;
				} while (atoi(leaguetype) > 12 && atoi(leaguetype) < 0);
				create_league(atoi(leaguetype));
				cout << "League created!" << endl << endl;
				return;
			}
			else
			{
				join_league();
				return;
			}
		case '2':
			return;
		default:
			cout << "Invalid choice!" << endl;
			}
	}
}


void GameEngine::join_league()
{
	if (running_league != nullptr) {
		if (selected_player != nullptr) {
			if (!running_league->add_player(selected_player)) {
				cout << "Player already registered to the league!" << endl;
				return;
			}
			else if (selected_player->get_type() != running_league->get_type())
			{
				cout << "Logged-in player is of a type that doesn't match the league.\nPlease wait for the league to end or play a computer instead." << endl;
				return;
			}
			cout << "Logged in player joined league." << endl;
			FileManager league("league.txt");
			league.write_to_file(selected_player->name(), strlen(selected_player->name()));
			league.write_to_file_new_entry();
		}
	}
}

void GameEngine::create_league(int type)
{
	if (running_league == nullptr)
	{
		running_league = new League(type);
		FileManager league("league.txt");
		char buffer[100];
		_itoa_s(type, buffer, 10);
		league.write_to_file(buffer, strlen(buffer));
		league.write_to_file_new_entry();
	}
}

void GameEngine::add_player_to_running_league(Player *pl)
{
	if(running_league != nullptr)
		running_league->add_player(pl);
}



void GameEngine::play_computer()
{
	cout << "Pick a difficulty:" << endl;
	cout << "\t1)Easy." << endl;
	cout << "\t2)Medium." << endl;
	cout << "\t3)Hard." << endl;
	int diff;
	cin >> diff;
	cout << "Insert a board size:";
	int size;
	cin >> size;
	ReversiGame game(diff,size);
	game.start_game();
}

/* Printing leaderboard
* champs frist
* gold next
* silver next
* bronze next
* score last 
*/
void GameEngine::print_leaderboard()
{
	Player **p_array = new Player*[player_database.size()];
	int i;
	for (i = 0; i < player_database.size(); i++)
	{
		if (i == 0)
			p_array[0] = player_database[0];
		else
		{
			Player *insertion_player = player_database[i];
			for (int j = 0; j < i; j++)
			{
				if (insertion_player->score() > p_array[j]->score())
				{
					Player *temp = p_array[j];
					p_array[j] = insertion_player;
					insertion_player = temp;
				}
			}
			p_array[i] = insertion_player;
		}
	}
	cout << "Leaderboard:" << endl;
	for (int u = 0; u < i; u++)
	{
		cout << u+1 << "." << endl;
		cout << "name:" << p_array[u]->name() << endl;
		cout << "score:" << p_array[u]->score() << endl;
	}
}

Player *GameEngine::search_name(char* name)
{
	for(int i = 0; i < player_database.size(); i++)
		if(strcmp(player_database[i]->name(), name) == 0)
			return player_database[i];
	return nullptr;
}
