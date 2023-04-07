#ifndef Map_H
#define	Map_H

#include <SFML/Graphics.hpp>

//Класс, отвечающий за создание карты и ее заполнение
class Map
{
	private:

		int height = 10;				//длина карты
		int width = 10;					//ширина карты

		int x_pos;
		int y_pos;

		sf::Texture map;
		sf::Sprite s_map;

		sf::RectangleShape rect_left;
		sf::RectangleShape rect_right;
		sf::RectangleShape rect_up;
		sf::RectangleShape rect_down;

		sf::String TileMap[10] = {
			"BBBBBBBBBB",
			"B01010101B",
			"B10101010B",
			"B01010101B",
			"B10101010B",
			"B01010101B",
			"B10101010B",
			"B01010101B",
			"B10101010B",
			"BBBBBBBBBB",
		};

	public:

		Map();

		void draw(sf::RenderWindow &window);		//отрисовка карты

		void drawLines(sf::RenderWindow &window);	//отрисовка границ карты
};

#endif