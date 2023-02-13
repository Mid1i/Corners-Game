#include "map.h"
#include "Engine.h"
#include "GrafficInterface.h"
#include "EngineBot.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 700), "Corners game");

	Map map;

	Engine eng;
	GrafficInterface gui;
	EngineBot engbot;

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed) && !gui.isPaused)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (gui.gameStatus == 1) engbot.changeTurn();
					else eng.changeTurn();
				}

				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (gui.gameStatus == 1) engbot.cancellMove();
					else eng.cancellMove();
				}
			}
		}

		gui.startGame(window, event, eng, engbot);

		window.clear(sf::Color(255, 165, 47));

		map.draw(window);
		map.drawLines(window);

		if (gui.gameStatus == 1)
		{
			engbot.evalFunc();
			engbot.mouseStep(window, event);
			engbot.win();
			engbot.draw(window);
		}
		else
		{
			eng.mouseStep(window, event);
			eng.win();
			eng.draw(window);
		}

		Sleep(65);

		//window.display();
	}
	return 0;
}