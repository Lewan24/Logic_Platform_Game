#include "game.h"
#include <fstream>

RenderWindow window(VideoMode(1280,720),"Logic_Platform",Style::Fullscreen);

/*
    window.setMouseCursorVisible(false);

	sf::View fixed = window.getView();
	sf::Texture cursorTexture;
	if(!cursorTexture.loadFromFile("Resources/Textures/cursor.png"))
    {
        MessageBox(NULL,"Cursor not found! Check: 'Resources/Textures/cursor.png'","ERROR",NULL);
		state = END;
    }
	sf::Sprite cursor(cursorTexture);

    cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))); // przed 'window.clear();'
    window.setView(fixed);
    window.draw(cursor);
*/

Game::Game(void)
{
	state = END;

	/*if(!font.loadFromFile("Resources/Fonts/Mecha.ttf"))
	{
		MessageBox(NULL,"Font not found!","ERROR",NULL);
		return;
	}*/

	if(!font.loadFromFile("Resources/Fonts/Mecha.ttf")) {
        ErrorMsg("Font not found! Check: 'Resources/Fonts/Mecha.ttf'","ERROR");
        return;
    }

	state = MENU;
}


Game::~Game(void)
{
}

void Game::ErrorMsg(string error, string title)
{
    window.close();
    MessageBoxA(NULL, error.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
    state = END;
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
        case L1:
            l1();
            break;
		}
	}
}

void Game::menu()
{
	Text title(Title,font,80);
	title.setStyle(Text::Bold);

	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);
//////////////////////////////////////////////////////////////////////////////
    window.setMouseCursorVisible(false);

	sf::View fixed = window.getView();
	sf::Texture cursorTexture;
	if(!cursorTexture.loadFromFile("Resources/Textures/cursor.png"))// Custon Cursor
		ErrorMsg("Cursor not found! Check: 'Resources/Textures/cursor.png'","ERROR");

	sf::Sprite cursor(cursorTexture);
/////////////////////////////////////////////////////////////////////////////
	const int ile = 3;

	Text tekst[ile];

	string str[] = {"Play","Options","Exit"};
	for(int i=0;i<ile;i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);              // Main Menu, texts and buttons

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);
	}
///////////////////////////////////////////////////////////////////////////////////
	while(state == MENU)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;

		while(window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if(event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;

			//klikniêcie EXIT
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
				tekst[i].setColor(Color::Cyan); // when you will move your mouse on button
			else tekst[i].setColor(Color::White);

        cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))); // for custom cursor

		window.clear();

		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);

        window.setView(fixed);
        window.draw(cursor);
		window.display();
	}
}

void Game::lvl_select()
{
    Text title(Title,font,80);
    title.setStyle(Text::Bold);

	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

    window.setMouseCursorVisible(false);

	sf::View fixed = window.getView();
	sf::Texture cursorTexture;
	if(!cursorTexture.loadFromFile("Resources/Textures/cursor.png"))
        ErrorMsg("Cursor not found! Check: 'Resources/Textures/cursor.png'","ERROR");

	sf::Sprite cursor(cursorTexture);

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
            //Wciœniêcie ESC lub przycisk X
			if(event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = MENU;
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
				state = L1;
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

        cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		window.clear();

		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);
        for(int i=0;i<ile2;i++)
			window.draw(tekst2[i]);

        window.setView(fixed);
        window.draw(cursor);
		window.display();
	}
}

void Game::l1()
{
    Text title(Title,font,50);
	title.setStyle(Text::Bold);
    title.setOutlineColor(sf::Color::Blue);
    title.setOutlineThickness(2);
	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

    window.setMouseCursorVisible(false);

	sf::View fixed = window.getView();
	sf::Texture cursorTexture;
	if(!cursorTexture.loadFromFile("Resources/Textures/cursor.png"))
        ErrorMsg("Cursor not found! Check: 'Resources/Textures/cursor.png'","ERROR");

	sf::Sprite cursor(cursorTexture);

	sf::Texture bg_tex;
    if (!bg_tex.loadFromFile("Resources/Textures/floor.png"))
		ErrorMsg("Some Resources not found! Check: 'Resources/Textures/floor.png'","ERROR");

    sf::Sprite background(bg_tex);

    sf::Texture leverOFFtexture, leverONtexture;
    if (!leverOFFtexture.loadFromFile("Resources/Textures/leverOFF.png"))
        ErrorMsg("Some Resources not found! Check: 'Resources/Textures/leverOFF.png'","ERROR");

    if (!leverONtexture.loadFromFile("Resources/Textures/leverON.png"))
        ErrorMsg("Some Resources not found! Check: 'Resources/Textures/leverON.png'","ERROR");

    sf::Sprite leverOFF(leverOFFtexture), leverOFF2(leverOFFtexture);
    sf::Sprite leverON(leverONtexture), leverON2(leverONtexture);

    leverOFF.setPosition(50,50);
    leverON.setPosition(50,50);

    leverOFF2.setPosition(250,150);
    leverON2.setPosition(250,150);

    bool leverstage1 = 0;
    bool leverstage2 = 0;

    //auto pos = sf::Mouse::getPosition(window);
    //TODO: Odtwarzac dzwiek dxwigni

    fstream file;
    string file_name = "Resources/Game/Levels/Level_1.LEVEL";
    file.open(file_name.c_str(), ios::in);

    if(file.good())
    {
        int i = 0;
        string line;
        int level[576];

        while (getline(file, line, ' '))
        {
            level[i] = atoi(line.c_str());
            i++;
        }

        /*if (i != 576) {
            cout << "Plik z levelem zostal zle edytowany, lub nie istnieje" << endl;
            window.close();
            getch();
            return -1;
        }*/

        TileMap map;
        if (!map.load("Resources/Game/Tileset_Test.png", sf::Vector2u(40, 40), level, 32, 18))
            ErrorMsg("Map not found! Check: 'Resources/Game/Tileset_Test.png'","ERROR");

        while(state == L1)
        {
            Vector2f mouse(Mouse::getPosition());
            Event event;

            while(window.pollEvent(event))
            {
                //Wciœniêcie ESC lub przycisk X
                if(event.type == Event::Closed || event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Escape)
                    state = SELECT;
                if(leverOFF2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                   || leverON2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                {
                    if (leverstage2 == 0)
                        leverstage2 = 1;
                    else
                        leverstage2 = 0;
                }
                if(leverOFF.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                   || leverON.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y) && event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
                {
                    if (leverstage1 == 0)
                        leverstage1 = 1;
                    else
                        leverstage1 = 0;
                }
            }

            cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

            window.clear();

            window.draw(background);
            window.draw(map);
            window.draw(title);

            if (leverstage1 == 0)
                window.draw(leverOFF);
            else if (leverstage1 == 1)
                window.draw(leverON);

            if (leverstage1 == 1)
            {
                if (leverstage2 == 0)
                    window.draw(leverOFF2);
                else if (leverstage2 == 1)
                    window.draw(leverON2);
            }

            window.setView(fixed);
            window.draw(cursor);
            window.display();
	}
	file.close();
    }
    else
        ErrorMsg("Map not found! Check: 'Resources/Game/Levels/Level_1.LEVEL'","ERROR");
}
