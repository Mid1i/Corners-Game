#ifndef AI_H
#define AI_H

#include "GameEngine.h"

//Класс, отвечающий за игру с ботом
class AI: public GameEngine {
	private:

		typedef struct {
			int index;
			sf::Vector2i pos;
			double distance;
		} ai_map;

		ai_map** aiTurn;					//массив с ходами бота

		int aiSize;							//кол-во возможных ходов бота

		sf::Vector2i farCellPos;

	public:

		AI();

		void keyStep();												//ход с помощью клавиатуры
		void changeTurn();											//другой ход

		void exist();												//сущ. место под массив или нет

		void evalFunc();											//оценочная функция

		bool isFarCell(int x_pos, int y_pos);						//определение точки, куда нужно прийти
		void farCell();												//определение точки, куда нужно прийти

		void aiMovementCell(int x_pos, int y_pos, int index);		//запись координат клетки бота
		void aiMovement(int x_pos, int y_pos, int index);			//может бот сходить или нет
};

#endif