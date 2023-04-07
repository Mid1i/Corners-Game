#include "./Includes/GUI.h"

//Конструктор класса с графической составляющей игры
GUI::GUI() {
	isMenu = true;
	isPaused = false;

	gameStatus = 0;

	font.loadFromFile("C:\\Programming\\C++\\sfml\\src\\Fonts\\MultiroundPro.otf");

	menuBlock();
	gameBlock();
	pauseBlock();
}

//Блок меню
void GUI::menuBlock() {
	PvsB = "1 player";
	PvsP = "2 players";
	rules = "Rules";
	exit = "Exit";

	PvsBtext.setString(PvsB);
	PvsBtext.setFont(font);
	PvsBtext.setCharacterSize(30);
	PvsBtext.setPosition(350, 200);

	PvsPtext.setString(PvsP);
	PvsPtext.setFont(font);
	PvsPtext.setCharacterSize(30);
	PvsPtext.setPosition(350, 250);

	rulestext.setString(rules);
	rulestext.setFont(font);
	rulestext.setCharacterSize(30);
	rulestext.setPosition(350, 300);

	exittext.setString(exit);
	exittext.setFont(font);
	exittext.setCharacterSize(30);
	exittext.setPosition(350, 350);
}

//Блок игры
void GUI::gameBlock() {
	title = "Corners";
	restart = "Restart";
	pause = "Pause";

	titleText.setString(title);
	titleText.setFont(font);
	titleText.setCharacterSize(50);
	titleText.setPosition(600, 100);

	restartText.setString(restart);
	restartText.setFont(font);
	restartText.setCharacterSize(30);
	restartText.setPosition(650, 200);

	pauseText.setString(pause);
	pauseText.setFont(font);
	pauseText.setCharacterSize(30);
	pauseText.setPosition(650, 250);
}

//Блок паузы
void GUI::pauseBlock() {
	pauseMenu = "Press space to continue";

	pauseMenuText.setString(pauseMenu);
	pauseMenuText.setFont(font);
	pauseMenuText.setCharacterSize(30);
	pauseMenuText.setPosition(200, 300);

}

//Запуск игры
void GUI::startGame(sf::RenderWindow &window, sf::Event &event, GameEngine &engine, AI &ai_engine) {
	if (isMenu) {
		window.clear(sf::Color(255, 165, 47));

		window.draw(PvsBtext);
		window.draw(PvsPtext);
		window.draw(rulestext);
		window.draw(exittext);

		menuBlockFunctions(window, event);
	}

	if (isPaused) {
		window.clear(sf::Color(255, 165, 47));

		window.draw(pauseMenuText);

		pauseBlockFunctions(event);
	}

	if ((!isMenu) && (!isPaused)) {
		window.draw(titleText);
		window.draw(restartText);
		window.draw(pauseText);

		gameBlockFunctions(window, event, engine, ai_engine);
	}

	window.display();
}

//Кнопки во время паузы
void GUI::pauseBlockFunctions(sf::Event &event) {
	if (event.key.code == sf::Keyboard::Space) {
		isPaused = false;
	}
}

//Кнопки во время игры
void GUI::gameBlockFunctions(sf::RenderWindow &window, sf::Event &event, GameEngine &engine, AI &ai_engine) {
	if (sf::IntRect(650, 200, 210, 30).contains(sf::Mouse::getPosition(window))) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				if (gameStatus == 1) {
					ai_engine.gameToNull();
				} else {
					engine.gameToNull();
				}
				gameStatus = 0;
				isMenu = true;
			}
		}
	}

	if (sf::IntRect(650, 250, 150, 30).contains(sf::Mouse::getPosition(window))) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				isPaused = true;
			}
		}
	}
}

//Кнопки во время меню
void GUI::menuBlockFunctions(sf::RenderWindow &window, sf::Event &event) {

	if (sf::IntRect(350, 200, 240, 30).contains(sf::Mouse::getPosition(window))) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				isMenu = false;
				gameStatus = 1;
			}
		}
	}

	if (sf::IntRect(350, 250, 240, 30).contains(sf::Mouse::getPosition(window))) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				isMenu = false;
				gameStatus = 2;
			}
		}
	}

	if (sf::IntRect(350, 350, 240, 30).contains(sf::Mouse::getPosition(window))) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				window.close();
			}
		}
	}
}

//Отрисовывает шашки
void GUI::circles() {
	blackImage.loadFromFile("C:\\C++\\sfml\\src\\Textures\\black_checker.png");
	blackTexture.loadFromImage(blackImage);
	bt = &blackTexture;

	whiteImage.loadFromFile("C:\\C++\\sfml\\src\\Textures\\white_checker.png");
	whiteTexture.loadFromImage(whiteImage);
	wt = &whiteTexture;

	blackCircle.setTexture(bt);
	whiteCircle.setTexture(wt);

	blackCircle.setPosition(600, 600);
	whiteCircle.setPosition(600, 700);
}