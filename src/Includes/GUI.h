#ifndef GUI_H
#define GUI_H

#include "GameEngine.h"
#include "AI.h"

#include <SFML/Graphics.hpp>

//Класс графической составляющей игры
class GUI
{
	private:

		sf::Font font;

		std::string PvsP;
		std::string PvsB;
		std::string rules;
		std::string exit;

		sf::Text PvsPtext;
		sf::Text PvsBtext;
		sf::Text rulestext;
		sf::Text exittext;

		sf::Image whiteImage;
		sf::Texture whiteTexture;
		sf::Texture *wt;

		sf::Image blackImage;
		sf::Texture blackTexture;
		sf::Texture *bt;

		sf::CircleShape whiteCircle;
		sf::CircleShape blackCircle;

		std::string title;
		std::string restart;
		std::string pause;

		sf::Text titleText;
		sf::Text restartText;
		sf::Text pauseText;

		std::string pauseMenu;

		sf::Text pauseMenuText;

	public:

		bool isPaused;					//Игра на паузе или нет
		bool isMenu;					//Меню или нет

		int gameStatus;					//Статус игры (с ботом или 2 игрока)

		GUI();

		void circles();					//Отрисовывает шашки

		void menuBlock();				//Отрисовывает блок меню
		void gameBlock();				//Отрисовывает блок игры
		void pauseBlock();				//Отрисовывает блок паузы

		void pauseBlockFunctions(sf::Event &event);																	//Кнопки во время паузы
		void gameBlockFunctions(sf::RenderWindow &window, sf::Event &event, GameEngine &engine, AI &ai_engine);		//Кнопки во время игры
		void menuBlockFunctions(sf::RenderWindow &window, sf::Event &event);										//Кнопки во время меню

		void startGame(sf::RenderWindow &window, sf::Event &event, GameEngine &eng, AI &ai_engine);					//Запуск игры
};

#endif