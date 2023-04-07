#ifndef GameEngine_H
#define GameEngine_H

#define cell 56
#define cellCenter 67

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//Класс, отвечающий за игру 2-ч игроков
class GameEngine {
	public:

		sf::Texture whiteTexture;
		sf::Texture *wt;

		sf::Texture blackTexture;
		sf::Texture *bt;

		typedef struct {
			bool white;
			sf::CircleShape shape;
			sf::Vector2i pos;
		} table_checkers_t;

		table_checkers_t** mainArray;			//массив с шашками

		int eCounter;							//счетчик
		int arraySize;							//размер массива

		bool isSelect;							//выбрана шашка или нет
		bool isWhite;							//ход белых
		bool isBlack;							//ход черных

		int index;								//индекс выбранной шашки

		int x_pos;								//позиция шашки по оси х
		int y_pos;								//позиция шашки по оси у

		int temp_x;								//хранение временной позиции шашки по оси х
		int temp_y;								//хранение временной позиции шашки по оси у

		void defaultSet();					//расстановка шашек
		void whiteSet();					//расстановка белых шашек
		void blackSet();					//расстановка черных шашек

		GameEngine();
		~GameEngine();

		void keyStep();						//ход с помощью клавиатуры
		void changeTurn();					//другой ход
		void cancellMove();					//отмена хода

		bool whiteWin();					//победа белых
		bool blackWin();					//победа черных
		void win();							//победа

		void gameToNull();					//обнуление игры

		bool canStay(int number, int index, int x_pos, int y_pos);	//может игрок сходить или нет
		int checking(int x_pos, int y_pos);							//проверка на правильность хода

		void draw(sf::RenderWindow &window);						//отрисовка шашек

		void mouseStep(sf::RenderWindow &window, sf::Event &event);	//ход с помощью мышки
};

#endif