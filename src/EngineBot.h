#ifndef EngineBot_H
#define EngineBot_H

#define cell 56								//длина ячейки
#define centre 67							//центр ячейки

#include <SFML/Graphics.hpp>
#include <windows.h>

//Класс, отвечающий за игру с ботом
class EngineBot {
	private:

		sf::Image whiteImage;
		sf::Texture whiteTexture;
		sf::Texture *wt;

		sf::Image blackImage;
		sf::Texture blackTexture;
		sf::Texture *bt;

		typedef struct
		{
			bool white;
			sf::CircleShape shape;
			sf::Vector2i pos;
		} table_checkers_t;

		table_checkers_t** mainArray;		//массив с шашками

		typedef struct
		{
			int index;
			sf::Vector2i pos;
			double distance;
		} bot_map;

		bot_map** botTurn;					//массив с ходами бота

		int botSize;						//кол-во возможных ходов бота

		sf::Vector2i farCellPos;

		int eCounter;						//счетчик
		int arraySize;						//размер массива

		bool isSelect;						//выбрана шашка или нет

		bool isWhite;						//ход белых
		bool isBlack;						//ход черных

		int index;							//индекс выбранной шашки

		int x_pos;							//позиция шашки по оси х
		int y_pos;							//позиция шашки по оси у

		int temp_x;							//хранение временной позиции шашки по оси х
		int temp_y;							//хранение временной позиции шашки по оси у

		void defaultSet();					//расстановка шашек
		void whiteSet();					//расстановка белых шашек
		void blackSet();					//расстановка черных шашек

	public:

		EngineBot();
		~EngineBot();

		void keyStep();						//ход с помощью клавиатуры
		void changeTurn();					//другой ход
		void cancellMove();					//отмена хода

		bool whiteWin();					//победа белых
		bool blackWin();					//победа черных
		void win();							//победа

		void exist();						//сущ. место под массив или нет

		void evalFunc();					//оценочная функция

		void gameToNull();					//обнуление игры

		bool isFarCell(int x_pos, int y_pos);	//определение точки, куда нужно прийти
		void farCell();							//определение точки, куда нужно прийти

		void botCanStay(int index, int x_pos, int y_pos);			//может бот сходить или нет

		bool canStay(int number, int index, int x_pos, int y_pos);	//может игрок сходить или нет
		int checking(int x_pos, int y_pos);							//проверка на правильность хода

		void draw(sf::RenderWindow &window);						//отрисовка шашек

		void mouseStep(sf::RenderWindow &window, sf::Event &event);	//ход с помощью мышки
};

#endif