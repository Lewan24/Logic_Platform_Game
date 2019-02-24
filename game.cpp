#include "game.h"

RenderWindow window(VideoMode(1280,720),"Logic_Platform",Style::Fullscreen);

Game::Game(void)
{
	state = END;

	if(!font.loadFromFile("Resources/Fonts/Mecha.ttf"))
	{
		MessageBox(NULL,"Font not found!","ERROR",NULL);
		return;
	}

	state = MENU;
}


Game::~Game(void)
{
}


void Game::runGame()
{
	while(state != END)
	{
		switch (state)
		{
		case MENU:
			menu();
			break;
		case SELECT:
			lvl_select();
			break;
        case GAME:
            //...
            break;
		}
	}
}


void Game::menu()
{
	Text title(Title,font,80);
	title.setStyle(Text::Bold);

	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

	const int ile = 3;

	Text tekst[ile];

	string str[] = {"Play","Options","Exit"};
	for(int i=0;i<ile;i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);
	}

	while(state == MENU)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;

		while(window.pollEvent(event))
		{
			//Wci�ni�cie ESC lub przycisk X
			if(event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;

			//klikni�cie EXIT
			else if(tekst[2].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
			else if(tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = SELECT;
			}
		}
		for(int i=0;i<ile;i++)
			if(tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Cyan);
			else tekst[i].setColor(Color::White);

		window.clear();

		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);

		window.display();
	}
}

void Game::lvl_select()
{
    Text title(Title,font,80);
    title.setStyle(Text::Bold);

	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

	const int ile2 = 3;
    Text tekst2[ile2];
    string nazwy[] = {"Tutorial", "Menu", "Exit"};
    for(int i=0;i<ile2;i++)  {
            tekst2[i].setFont(font);
            tekst2[i].setCharacterSize(60);

            tekst2[i].setString(nazwy[i]);
            tekst2[i].setPosition(1280/8.5-tekst2[i].getGlobalBounds().width/2,250+i*120);
	}

    const int ile = 20;

	Text tekst[ile];

	string str[] = {"Level_1","Level_2","Level_3","Level_4",
                    "Level_5","Level_6","Level_7","Level_8",
                    "Level_9","Level_10","Level_11","Level_12",  // pierwsza Strona // Cala zapelniona
                    "Level_13","Level_14","Level_15","Level_16",
                    "Level_17","Level_18","Level_19","Level_20"};
	int temp = 1;
    double a[] = {4, 2.7, 2, 1.6, 1.33};
    int c[] = {250, -230, -710, -1190, -1670};
    int b = 0;

	for(int i=0;i<ile;i++)
	{
        if (temp <= 5) {
            if (temp == 5) {    temp = 1; b++;  }
            if (b >= 5) b = 0;

            tekst[i].setFont(font);
            tekst[i].setCharacterSize(40);

            tekst[i].setString(str[i]);
            tekst[i].setPosition(1280/a[b]-tekst[i].getGlobalBounds().width/2,c[b]+i*120);
        }

        temp++;
	}

	while(state == SELECT)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;

		while(window.pollEvent(event))
		{
            //Wci�ni�cie ESC lub przycisk X
			if(event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			else if(tekst2[1].getGlobalBounds().contains(mouse) &&  // Menu
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = MENU;
			}
			else if(tekst2[2].getGlobalBounds().contains(mouse) &&  // Exit
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
			else if(tekst[0].getGlobalBounds().contains(mouse) &&  // level 1
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				//state = GAME;
				//TODO: Wymyslic jak przeniesc sie na konkretny poziom
				// moze zrobic tak, by zaczynalo sie od tutorialu i kontynuowalo o poziom wyzej
				// w ustawieniach zapisywalo by sie gdzie sie skonczylo, ale jak
				// dodac moc wyboru konkretnego poziomu ?
			}
        }

		for(int i=0;i<ile;i++)
			if(tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Cyan);
			else tekst[i].setColor(Color::White);
        for(int i=0;i<ile2;i++)
			if(tekst2[i].getGlobalBounds().contains(mouse))
				tekst2[i].setColor(Color::Cyan);
			else tekst2[i].setColor(Color::White);

		window.clear();

		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);
        for(int i=0;i<ile2;i++)
			window.draw(tekst2[i]);

		window.display();
	}
}