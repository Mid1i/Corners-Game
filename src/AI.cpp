#include "./Includes/AI.h"

//Конструктор для класса движка игры
AI::AI() {
	aiTurn = new ai_map*[500];

	for (int i = 0; i < 500; i++) {
		aiTurn[i] = new ai_map;
	}

	for (int i = 0; i < 500; i++) {
		aiTurn[i] = 0;
	}
}

/*
	Функция для смены хода. Отменяется выбор шашки,
	цвет шашки становится предыдущим, меняются ход
	белых и ход черных.
*/
void AI::changeTurn() {
	if (isSelect) {
		isSelect = false;
		mainArray[index]->shape.setFillColor(sf::Color::White);
		std::swap(isWhite, isBlack);
	}
}

/*
	Функция, определяющая конечную клетку.
	Проверяет на наличие шашки в ней и если
	она пустая, то возвращает ее номер.
*/
bool AI::isFarCell(int x_pos, int y_pos) {
	for (int i = 9; i < arraySize; i++) {
		if ((mainArray[i]->pos.x == x_pos) && (mainArray[i]->pos.y == y_pos)) {
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
void AI::farCell() {
	x_pos = cellCenter;
	y_pos = cellCenter;

	for (int i = 0; i < 9; i++) {
		if ((i % 3 == 0) && (i != 0)) {
			x_pos = cellCenter;
			y_pos += cell;
		}

		if (isFarCell(x_pos, y_pos)) {
			farCellPos.x = x_pos;
			farCellPos.y = y_pos;
			return;
		}

		x_pos += cell;
	}
}

//Функция, определяющая существует место под массив или нет
void AI::exist() {
	if (!aiTurn[aiSize]) {
		aiTurn[aiSize] = new ai_map;
	}
}

void AI::aiMovementCell(int x_pos, int y_pos, int index) {
	aiTurn[aiSize]->index = index;
	aiTurn[aiSize]->pos.x = x_pos;
	aiTurn[aiSize]->pos.y = y_pos;
	aiTurn[aiSize]->distance = sqrt(pow(aiTurn[aiSize]->pos.x - farCellPos.x, 2) + pow(aiTurn[aiSize]->pos.y - farCellPos.y, 2));
	aiSize ++;
}
/*
	Функция, определяющая может ли бот так сходить
	или нет. Записывает в массив ходов бота все его
	возможные ходы, а также расстояния до конечной
	клетки.
*/
void AI::aiMovement(int x_pos, int y_pos, int index) {
	exist();

	if ((checking(x_pos - cell, y_pos) == -1) && (x_pos - cell > cell) && (y_pos > cell) && (x_pos - cell < 504) && (y_pos < 504)) {
		aiMovementCell(x_pos - cell, y_pos, index);
	}

	exist();

	if ((checking(x_pos, y_pos - cell) == -1) && (x_pos > cell) && (y_pos - cell > cell) && (x_pos < 504) && (y_pos - cell < 504)) {
		aiMovementCell(x_pos, y_pos - cell, index);
	}

	exist();

	if ((checking(x_pos - 2 * cell, y_pos) == -1) && (x_pos - 2 * cell > 56) && (y_pos > 56) && (x_pos - 2 * cell < 504) && (y_pos < 504)) {
		if (checking(x_pos - cell, y_pos) != -1) {
			aiMovementCell(x_pos - cell * 2, y_pos, index);
		}
	}

	exist();

	if ((checking(x_pos, y_pos - cell * 2) == -1) && (x_pos > 56) && (y_pos - cell * 2 > 56) && (x_pos < 504) && (y_pos - cell * 2 < 504)) {
		if (checking(x_pos, y_pos - cell) != -1) {
			aiMovementCell(x_pos, y_pos - cell * 2, index);
		}
	}
}

/*
	Оценочная функция. По расстоянию определяет
	наиболее выгодную шашку для бота. Далее, если
	она может сходить, то бот делает ход, если нет,
	то выбирает следующую шашку.
*/
void AI::evalFunc() {
	if (isBlack) {
		aiSize = 0;
		int maxDistance = 0;

		int maxIndex;

		farCell();

		for (int i = 9; i < arraySize; i++) {
			exist();
			aiTurn[aiSize]->index = i;
			aiMovement(mainArray[i]->pos.x, mainArray[i]->pos.y, i);
		}

		for (int j = 0; j < aiSize; j++) {
			if (aiTurn[j]->distance > maxDistance) {
				maxDistance = aiTurn[j]->distance;
				maxIndex = j;
			}
		}

		if (maxDistance == 0) {
			std::cout << "I can't move" << std::endl;
		} else {
			mainArray[aiTurn[maxIndex]->index]->pos.x = aiTurn[maxIndex]->pos.x;
			mainArray[aiTurn[maxIndex]->index]->pos.y = aiTurn[maxIndex]->pos.y;
			mainArray[aiTurn[maxIndex]->index]->shape.setPosition(mainArray[aiTurn[maxIndex]->index]->pos.x, mainArray[aiTurn[maxIndex]->index]->pos.y);

			std::swap(isWhite, isBlack);
		}

		for (int i = 0; i < aiSize; i++) {
			aiTurn[i] = 0;
		}
	}
}
