#ifndef game_h
#define game_h

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

class Game
{
public:
	Game(void);  // konstruktor
	~Game(void);    // destruktor

	void runGame();

protected:
	enum GameState {MENU,GAME,SELECT,END}; // {l1, l2, l3, l4...} ???
	GameState state;

private:
	Font font;
    const string Title = "Logic_Platform";

	void menu();
	void lvl_select();

	//void l1(); // poziom 1 ...
};

#endif // game_h
