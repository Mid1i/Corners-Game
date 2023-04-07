#include "./Includes/Map.h"

//Конструктор класса с картой
Map::Map() {
	map.loadFromFile("C:\\Programming\\C++\\sfml\\src\\Textures\\cells.png");
	s_map.setTexture(map);

	rect_left.setSize(sf::Vector2f(448, 4));			//левая граница карты
	rect_left.setFillColor(sf::Color::Black);

	rect_right.setSize(sf::Vector2f(452, 4));			//правая граница карты
	rect_right.setFillColor(sf::Color::Black);

	rect_up.setSize(sf::Vector2f(448, 4));				//верхняя граница карты
	rect_up.setFillColor(sf::Color::Black);

	rect_down.setSize(sf::Vector2f(448, 4));			//нижняя граница карты
	rect_down.setFillColor(sf::Color::Black);

	rect_up.rotate(90);
	rect_down.rotate(90);
}

/*
	Функция отрисовки карты. Из массива берем данные для отрисовки карты.
	Если значение В, то рисуем границу, если 1, то рисуем черную клетку,
	иначе рисуем белую клетку.
*/
void Map::draw(sf::RenderWindow &window) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (TileMap[i][j] == 'B') {
				s_map.setTextureRect(sf::IntRect(0, 57, 0, 0));
			}

			if (TileMap[i][j] == '0') {
				s_map.setTextureRect(sf::IntRect(0, 0, 56, 56));
			}

			if (TileMap[i][j] == '1') {
				s_map.setTextureRect(sf::IntRect(56, 0, 56, 56));
			}

			s_map.setPosition(j*56, i*56);
			window.draw(s_map);
		}
	}
}

//Функция для отрисовки границ карты
void Map::drawLines(sf::RenderWindow &window) {
	x_pos = 56;
	y_pos = 56;

	rect_left.setPosition(x_pos, y_pos);
	rect_up.setPosition(x_pos, y_pos);

	window.draw(rect_left);
	window.draw(rect_up);

	x_pos = 504;
	y_pos = 56;

	rect_down.setPosition(x_pos, y_pos);
	window.draw(rect_down);

	x_pos = 52;
	y_pos = 504;

	rect_right.setPosition(x_pos, y_pos);
	window.draw(rect_right);
}