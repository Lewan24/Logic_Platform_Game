#ifndef game_h
#define game_h

#include <SFML/Graphics.hpp>
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
	enum GameState {MENU,SELECT,END,
                    L1}; // {l1, l2, l3, l4...} ???
	GameState state;

private:
	Font font;
    const string Title = "Logic_Platform";
	void menu();
	void lvl_select();
	void l1(); // level 1 ...
};

/*  // Maybe game will be in future without moveable player
class Gracz
{
    public:

    sf::RectangleShape rect;
    float bottom, left, right, top;

    Gracz(sf::Vector2f position, sf::Vector2f size, sf::Color c1, sf::Color c2, int thi)
    {
        rect.setPosition(position);
        rect.setSize(size);
        rect.setFillColor(c1);
        rect.setOutlineColor(c2);
        rect.setOutlineThickness(thi);
    }

    void Update()
    {
        bottom = rect.getPosition().y + rect.getSize().y;
        left = rect.getPosition().x;
        right = rect.getPosition().x + rect.getSize().x;
        top = rect.getPosition().y;
    }

    bool Collision(Gracz p)
    {
        if (right < p.left || left > p.right ||
            top > p.bottom || bottom < p.top)
        {
            return false;
        }
        return true;
    }
};
*/

#endif // game_h
