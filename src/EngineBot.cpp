#include "EngineBot.h"

#include <iostream>
#include <cmath>

//Конструктор для класса движка игры
EngineBot::EngineBot()
{
	botTurn = new bot_map*[500];

	for (int i = 0; i < 500; i++)
	{
		botTurn[i] = new bot_map;
	}

	for (int i = 0; i < 500; i++)
	{
		botTurn[i] = 0;
	}

	arraySize = 18;
	index = 0;

	isSelect = false;
	isWhite = true;
	isBlack = false;

	mainArray = new table_checkers_t*[arraySize];

	blackImage.loadFromFile("C:\\C++\\sfml\\src\\Images\\black_checker.png");
	blackTexture.loadFromImage(blackImage);
	bt = &blackTexture;

	whiteImage.loadFromFile("C:\\C++\\sfml\\src\\Images\\white_checker.png");
	whiteTexture.loadFromImage(whiteImage);
	wt = &whiteTexture;

	defaultSet();
	whiteSet();
	blackSet();
}

/*
	Обнуление игры. Зануляется массив с шашками, отменяется выбор
	шашек, ход белых, ход черных, заново создаются шашки.
*/
void EngineBot::gameToNull()
{
	for (int i = 0; i < arraySize; i++)
	{
		mainArray[i] = 0;
	}

	isSelect = false;
	isWhite = true;
	isBlack = false;

	defaultSet();
	whiteSet();
	blackSet();
}

/*
	Настройки по умолчанию. Создается массив для шашек, заполняется
	белыми и черными.
*/
void EngineBot::defaultSet()
{
	for (int i = 0; i < arraySize; i++)
	{
		mainArray[i] = new table_checkers_t;
	}

	for (int i = 0; i < arraySize; i++)
	{
		mainArray[i]->shape.setRadius(18);

		if (i < 9)
		{
			mainArray[i]->white = true;
		}
		else
		{
			mainArray[i]->white = false;
		}
	}
}

/*
	Создает белые шашки и расставляет их по полю.
	Координаты начинаются с (67, 67) - центра 1-ой
	клетки и дальше прибавляет по 56 - длина одной
	клетки.
*/
void EngineBot::whiteSet()
{
	x_pos = centre;
	y_pos = centre;

	for (int i = 0; i < 9; i++)
	{
		if ((i % 3 == 0) && (i != 0))
		{
			x_pos = centre;
			y_pos += cell;
		}

		mainArray[i]->pos.x = x_pos;
		mainArray[i]->pos.y = y_pos;

		mainArray[i]->shape.setPosition(mainArray[i]->pos.x, mainArray[i]->pos.y);
		mainArray[i]->shape.setTexture(wt);

		x_pos += cell;
	}
}

/*
	Создает черные шашки и расставляет их по полю.
	Координаты начинаются с (347, 347) - центра 1-ой
	клетки и дальше прибавляет по 56 - длина одной
	клетки.
*/
void EngineBot::blackSet()
{
	x_pos = 347;
	y_pos = 347;

	for (int i = 9; i < arraySize; i++)
	{
		if ((i % 3 == 0) && (i != 9))
		{
			x_pos = 347;
			y_pos += cell;
		}

		mainArray[i]->pos.x = x_pos;
		mainArray[i]->pos.y = y_pos;

		mainArray[i]->shape.setPosition(mainArray[i]->pos.x, mainArray[i]->pos.y);
		mainArray[i]->shape.setTexture(bt);

		x_pos += cell;
	}
}

//Функция для отрисовки шашек
void EngineBot::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < arraySize; i++)
	{
		window.draw(mainArray[i]->shape);
	}
}

/*
	Функция для смены хода. Отменяется выбор шашки,
	цвет шашки становится предыдущим, меняются ход
	белых и ход черных.
*/
void EngineBot::changeTurn()
{
	if (isSelect)
	{
		isSelect = false;
		mainArray[index]->shape.setFillColor(sf::Color::White);
		std::swap(isWhite, isBlack);
	}
}

/*
	Функция отмены хода. Шашка возвращается на свое
	место, отменяется выбор шашки.
*/
void EngineBot::cancellMove()
{
	isSelect = false;
	mainArray[index]->pos.x = temp_x;
	mainArray[index]->pos.y = temp_y;
	mainArray[index]->shape.setFillColor(sf::Color::White);
	mainArray[index]->shape.setPosition(mainArray[index]->pos.x, mainArray[index]->pos.y);
}

//Функция для проверки есть ли шашка в данной клетке
int EngineBot::checking(int x_pos, int y_pos)
{
	for (int i = 0; i < arraySize; i++)
	{
		if ((mainArray[i]->pos.x == x_pos) && (mainArray[i]->pos.y == y_pos)) return i;
	}
	return -1;
}

/*
	Функция, проверяющая возможен ход или нет.
	Если в клетке стоит шашка, то возвращает
	-1, если нет, то возвращает true, значит
	ход возможен.
*/
bool EngineBot::canStay(int number, int index, int x_pos, int y_pos)
{
	if (number != -1) return false;

	if ((abs(mainArray[index]->pos.x - (x_pos)) == cell) && (abs(mainArray[index]->pos.y - (y_pos)) == 0))
	{
		return true;
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == 0) && (abs(mainArray[index]->pos.y - (y_pos)) == cell))
	{
		return true;
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == cell * 2) && (abs(mainArray[index]->pos.y - (y_pos)) == 0))
	{
		if ((checking(x_pos - cell, y_pos) != -1) || (checking(x_pos + cell, y_pos) != -1))
		{
			return true;
		}
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == 0) && (abs(mainArray[index]->pos.y - (y_pos)) == cell * 2))
	{
		if ((checking(x_pos, y_pos - cell) != -1) || (checking(x_pos, y_pos + cell) != -1))
		{
			return true;
		}
	}

	return false;
}

/*
	Функция, определяющая конечную клетку.
	Проверяет на наличие шашки в ней и если
	она пустая, то возвращает ее номер.
*/
bool EngineBot::isFarCell(int x_pos, int y_pos)
{
	for (int i = 9; i < arraySize; i++)
	{
		if ((mainArray[i]->pos.x == x_pos) && (mainArray[i]->pos.y == y_pos))
		{
			return false;
		}
	}
	return true;
}

/*
	Функция, определяющая конечную клетку.
	Определяет самую дальнюю незанятую
	игроком клетку.
*/
void EngineBot::farCell()
{
	x_pos = centre;
	y_pos = centre;

	for (int i = 0; i < 9; i++)
	{
		if ((i % 3 == 0) && (i != 0))
		{
			x_pos = centre;
			y_pos += cell;
		}

		if (isFarCell(x_pos, y_pos))
		{
			farCellPos.x = x_pos;
			farCellPos.y = y_pos;
			return;
		}

		x_pos += cell;
	}
}

//Функция, определяющая существует место под массив или нет
void EngineBot::exist()
{
	if (!botTurn[botSize])
	{
		botTurn[botSize] = new bot_map;
	}
}

/*
	Функция, определяющая может ли бот так сходить
	или нет. Записывает в массив ходов бота все его
	возможные ходы, а также расстояния до конечной
	клетки.
*/
void EngineBot::botCanStay(int index, int x_pos, int y_pos)
{
	exist();

	if ((checking(x_pos - cell, y_pos) == -1) && (x_pos - cell > cell) && (y_pos > cell) && (x_pos - cell < 504) && (y_pos < 504))
	{
		botTurn[botSize]->index = index;
		botTurn[botSize]->pos.x = x_pos - cell;
		botTurn[botSize]->pos.y = y_pos;
		botTurn[botSize]->distance = sqrt(pow(botTurn[botSize]->pos.x - farCellPos.x, 2) + pow(botTurn[botSize]->pos.y - farCellPos.y, 2));
		std::cout << botSize << " " << botTurn[botSize]->index << " " << botTurn[botSize]->pos.x << " " << botTurn[botSize]->pos.y << " " << botTurn[botSize]->distance << std::endl;

		botSize ++;

	}

	exist();

	if ((checking(x_pos, y_pos - cell) == -1) && (x_pos > cell) && (y_pos - cell > cell) && (x_pos < 504) && (y_pos - cell < 504))
	{
		botTurn[botSize]->index = index;
		botTurn[botSize]->pos.x = x_pos;
		botTurn[botSize]->pos.y = y_pos - cell;
		botTurn[botSize]->distance = sqrt(pow(botTurn[botSize]->pos.x - farCellPos.x, 2) + pow(botTurn[botSize]->pos.y - farCellPos.y, 2));
		std::cout << botSize << " " << botTurn[botSize]->index << " " << botTurn[botSize]->pos.x << " " << botTurn[botSize]->pos.y << " " << botTurn[botSize]->distance << std::endl;

		botSize ++;
	}

	exist();

	if ((checking(x_pos - 2 * cell, y_pos) == -1) && (x_pos - 2 * cell > 56) && (y_pos > 56) && (x_pos - 2 * cell < 504) && (y_pos < 504))
	{
		if (checking(x_pos - cell, y_pos) != -1)
		{
			botTurn[botSize]->index = index;
			botTurn[botSize]->pos.x = x_pos - cell * 2;
			botTurn[botSize]->pos.y = y_pos;
			botTurn[botSize]->distance = sqrt(pow((botTurn[botSize]->pos.x - farCellPos.x), 2) + pow(botTurn[botSize]->pos.y - farCellPos.y, 2));
			std::cout << botSize << " " << botTurn[botSize]->index << " " << botTurn[botSize]->pos.x << " " << botTurn[botSize]->pos.y << " " << botTurn[botSize]->distance << std::endl;

			botSize ++;
		}
	}

	exist();

	if ((checking(x_pos, y_pos - cell * 2) == -1) && (x_pos > 56) && (y_pos - cell * 2 > 56) && (x_pos < 504) && (y_pos - cell * 2 < 504))
	{
		if (checking(x_pos, y_pos - cell) != -1)
		{
			botTurn[botSize]->index = index;
			botTurn[botSize]->pos.x = x_pos;
			botTurn[botSize]->pos.y = y_pos - cell * 2;
			botTurn[botSize]->distance = sqrt(pow(botTurn[botSize]->pos.x - farCellPos.x, 2) + pow(botTurn[botSize]->pos.y - farCellPos.y, 2));
			std::cout << botSize << " " << botTurn[botSize]->index << " " << botTurn[botSize]->pos.x << " " << botTurn[botSize]->pos.y << " " << botTurn[botSize]->distance << std::endl;

			botSize ++;
		}
	}
}

/*
	Оценочная функция. По расстоянию определяет
	наиболее выгодную шашку для бота. Далее, если
	она может сходить, то бот делает ход, если нет,
	то выбирает следующую шашку.
*/
void EngineBot::evalFunc()
{
	if (isBlack)
	{
		botSize = 0;
		int maxDistance = 0;

		int maxIndex;

		farCell();

		for (int i = 9; i < arraySize; i++)
		{
			exist();
			botTurn[botSize]->index = i;
			botCanStay(i, mainArray[i]->pos.x, mainArray[i]->pos.y);
		}

		for (int j = 0; j < botSize; j++)
		{
			if (botTurn[j]->distance > maxDistance)
			{
				maxDistance = botTurn[j]->distance;
				maxIndex = j;
			}
		}

		std::cout << botTurn[maxIndex]->pos.x << " " << botTurn[maxIndex]->pos.y;

		if (maxDistance == 0)
		{
			std::cout << "I can't move" << std::endl;
		}
		else
		{
			mainArray[botTurn[maxIndex]->index]->pos.x = botTurn[maxIndex]->pos.x;
			mainArray[botTurn[maxIndex]->index]->pos.y = botTurn[maxIndex]->pos.y;
			mainArray[botTurn[maxIndex]->index]->shape.setPosition(mainArray[botTurn[maxIndex]->index]->pos.x, mainArray[botTurn[maxIndex]->index]->pos.y);

			std::swap(isWhite, isBlack);
		}

		for (int i = 0; i < botSize; i++)
		{
			botTurn[i] = 0;
		}
	}
}


/*
	Функция для хода игрока. Проверяет наведен ли
	курсор мышки на шашку и выбрана ли она. При
	последующем нажатии шашка передвигается. Также
	во время хода цвет шашки становится зеленым для
	удобства.
*/
void EngineBot::mouseStep(sf::RenderWindow &window, sf::Event &event)
{
	int j = 0;

	for (int i = 0; i < 64; i++)
	{
		int shift_x = cell * ((i % 8) + 1);
		int shift_y = cell * (j + 1);

		int new_cell_x = centre + cell * (i % 8);
		int new_cell_y = centre + cell * j;

		if ((i % 8 == 0) && (i != 0))
		{
			j += 1;
		}

		if (sf::IntRect(shift_x, shift_y, cell, cell).contains(sf::Mouse::getPosition(window)))
		{
			int number = checking(new_cell_x, new_cell_y);

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if ((event.mouseButton.button == sf::Mouse::Button::Left) && (not isSelect))
				{
					if (((0 <= number) && (number <= 8)) && isWhite)
					{
						isSelect = true;
						index = number;

						mainArray[index]->shape.setFillColor(sf::Color::Green);

						temp_x = mainArray[index]->pos.x;
						temp_y = mainArray[index]->pos.y;
					}
				}

				if (event.mouseButton.button == sf::Mouse::Button::Left  && isSelect)
				{
					if (canStay(number, index, new_cell_x, new_cell_y))
					{
						mainArray[index]->pos.x = new_cell_x;
						mainArray[index]->pos.y = new_cell_y;

						mainArray[index]->shape.setPosition(mainArray[index]->pos.x, mainArray[index]->pos.y);

						window.draw(mainArray[index]->shape);
					}
				}
			}
		}
	}
}

//Функция проверки на победу белых шашек
bool EngineBot::whiteWin()
{
	for (int i = 0; i < arraySize; i++)
	{
		if ((mainArray[i]->pos.x < 347) || (mainArray[i]->pos.y < 347)) return false;
	}
	return true;
}

//Функция проверки на победу черных шашек
bool EngineBot::blackWin()
{
	for (int i = 9; i < arraySize; i++)
	{
		if ((mainArray[i]->pos.x > 179) || (mainArray[i]->pos.y > 179)) return false;
	}
	return true;
}

//Функция проверки на победу
void EngineBot::win()
{
	if (whiteWin()) std::cout << "White Win!" << std::endl;
	if (blackWin()) std::cout << "Black Win!" << std::endl;
}

//Деструктор класса движка игры
EngineBot::~EngineBot()
{
	for (int i = 0; i < arraySize; i++)
	{
		delete mainArray[i];
	}

	delete [] mainArray;
}