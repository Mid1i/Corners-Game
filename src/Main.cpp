#include "./Includes/AI.h"
#include "./Includes/GUI.h"
#include "./Includes/Map.h"
#include "./Includes/GameEngine.h"

#include <windows.h>

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 700), "Corners game");

	Map map;

	GameEngine engine;
	GUI gui;
	AI ai_engine;

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed) && !gui.isPaused) {
				if (event.key.code == sf::Keyboard::Enter) {
					if (gui.gameStatus == 1) {
						ai_engine.changeTurn();
					} else {
						engine.changeTurn();
					}
				}

				if (event.key.code == sf::Keyboard::BackSpace) {
					if (gui.gameStatus == 1) {
						ai_engine.cancellMove();
					} else {
						engine.cancellMove();
					}
				}
			}
		}

		gui.startGame(window, event, engine, ai_engine);

		window.clear(sf::Color(255, 165, 47));

		map.draw(window);
		map.drawLines(window);

		if (gui.gameStatus == 1) {
			ai_engine.evalFunc();
			ai_engine.mouseStep(window, event);
			ai_engine.win();
			ai_engine.draw(window);
		} else {
			engine.mouseStep(window, event);
			engine.win();
			engine.draw(window);
		}

		Sleep(65);
	}
	return 0;
}