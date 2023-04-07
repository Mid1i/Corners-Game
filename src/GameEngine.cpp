#include "./Includes/GameEngine.h"

//Конструктор для класса движка игры
GameEngine::GameEngine() {
	arraySize = 18;
	index = 0;

	isSelect = false;
	isWhite = true;
	isBlack = false;

	mainArray = new table_checkers_t*[arraySize];

	blackTexture.loadFromFile("Textures/black_checker.png");
	bt = &blackTexture;

	whiteTexture.loadFromFile("C:\\Programming\\C++\\sfml\\src\\Textures\\white_checker.png");
	wt = &whiteTexture;

	defaultSet();
	whiteSet();
	blackSet();
}

/*
	Обнуление игры. Зануляется массив с шашками, отменяется выбор
	шашек, ход белых, ход черных, заново создаются шашки.
*/
void GameEngine::gameToNull() {
	for (int i = 0; i < arraySize; i++) {
		delete mainArray[i];
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
void GameEngine::defaultSet() {
	for (int i = 0; i < arraySize; i++) {
		mainArray[i] = new table_checkers_t;
	}

	for (int i = 0; i < arraySize; i++) {
		mainArray[i]->shape.setRadius(18);

		if (i < 9) {
			mainArray[i]->white = true;
		} else {
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
void GameEngine::whiteSet() {
	x_pos = cellCenter;
	y_pos = cellCenter;

	for (int i = 0; i < 9; i++) {
		if ((i % 3 == 0) && (i != 0)) {
			x_pos = cellCenter;
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
void GameEngine::blackSet() {
	x_pos = 347;
	y_pos = 347;

	for (int i = 9; i < arraySize; i++) {
		if ((i % 3 == 0) && (i != 9)) {
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
void GameEngine::draw(sf::RenderWindow &window) {
	for (int i = 0; i < arraySize; i++) {
		window.draw(mainArray[i]->shape);
	}
}

/*
	Функция для смены хода. Отменяется выбор шашки,
	цвет шашки становится предыдущим, меняются ход
	белых и ход черных.
*/
void GameEngine::changeTurn() {
	if (isSelect) {
		isSelect = false;
		mainArray[index]->shape.setFillColor(sf::Color::White);
		std::swap(isWhite, isBlack);
	}
}

/*
	Функция отмены хода. Шашка возвращается на свое
	место, отменяется выбор шашки.
*/
void GameEngine::cancellMove() {
	isSelect = false;
	mainArray[index]->pos.x = temp_x;
	mainArray[index]->pos.y = temp_y;
	mainArray[index]->shape.setFillColor(sf::Color::White);
	mainArray[index]->shape.setPosition(mainArray[index]->pos.x, mainArray[index]->pos.y);
}

//Функция для проверки есть ли шашка в данной клетке
int GameEngine::checking(int x_pos, int y_pos) {
	for (int i = 0; i < arraySize; i++) {
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
bool GameEngine::canStay(int number, int index, int x_pos, int y_pos) {
	if (number != -1) {
		return false;
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == cell) && (abs(mainArray[index]->pos.y - (y_pos)) == 0)) {
		return true;
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == 0) && (abs(mainArray[index]->pos.y - (y_pos)) == cell)) {
		return true;
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == cell * 2) && (abs(mainArray[index]->pos.y - (y_pos)) == 0)) {
		if ((checking(x_pos - cell, y_pos) != -1) || (checking(x_pos + cell, y_pos) != -1)) {
			return true;
		}
	}

	if ((abs(mainArray[index]->pos.x - (x_pos)) == 0) && (abs(mainArray[index]->pos.y - (y_pos)) == cell * 2)) {
		if ((checking(x_pos, y_pos - cell) != -1) || (checking(x_pos, y_pos + cell) != -1)) {
			return true;
		}
	}

	return false;
}

/*
	Функция для хода игрока. Проверяет наведен ли
	курсор мышки на шашку и выбрана ли она. При
	последующем нажатии шашка передвигается. Также
	во время хода цвет шашки становится зеленым для
	удобства.
*/
void GameEngine::mouseStep(sf::RenderWindow &window, sf::Event &event) {
	int j = 0;

	for (int i = 0; i < 64; i++) {
		int shift_x = cell * ((i % 8) + 1);
		int shift_y = cell * (j + 1);

		int new_cell_x = cellCenter + cell * (i % 8);
		int new_cell_y = cellCenter + cell * j;

		if ((i % 8 == 0) && (i != 0)) {
			j += 1;
		}

		if (sf::IntRect(shift_x, shift_y, cell, cell).contains(sf::Mouse::getPosition(window))) {
			int number = checking(new_cell_x, new_cell_y);

			if (event.type == sf::Event::MouseButtonPressed) {
				if ((event.mouseButton.button == sf::Mouse::Button::Left) && (not isSelect)) {
					if (((0 <= number) && (number <= 8) && isWhite) || ((9 <= number) && (number <= 17) && isBlack)) {
						isSelect = true;
						index = number;

						mainArray[index]->shape.setFillColor(sf::Color::Green);

						temp_x = mainArray[index]->pos.x;
						temp_y = mainArray[index]->pos.y;
					}
				}

				if (event.mouseButton.button == sf::Mouse::Button::Left  && isSelect) {
					if (canStay(number, index, new_cell_x, new_cell_y)) {
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
bool GameEngine::whiteWin() {
	for (int i = 0; i < arraySize; i++) {
		if ((mainArray[i]->pos.x < 347) || (mainArray[i]->pos.y < 347)) return false;
	}
	return true;
}

//Функция проверки на победу черных шашек
bool GameEngine::blackWin() {
	for (int i = 9; i < arraySize; i++) {
		if ((mainArray[i]->pos.x > 179) || (mainArray[i]->pos.y > 179)) return false;
	}
	return true;
}

//Функция проверки на победу
void GameEngine::win() {
	if (whiteWin()) {
		std::cout << "White Win!" << std::endl;
	}
	if (blackWin()) {
		std::cout << "Black Win!" << std::endl;
	}
}

//Деструктор класса движка игры
GameEngine::~GameEngine() {
	for (int i = 0; i < arraySize; i++) {
		delete mainArray[i];
	}

	delete [] mainArray;
}