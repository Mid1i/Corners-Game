#ifndef GameEngine_H
#define GameEngine_H

#include <SFML/Graphics.hpp>
#include <windows.h>

class GameEngine {
	private:

		sf::CircleShape White_Circle_1;

		typedef struct
		{
			bool color;
			sf::CircleShape shape;
			sf::Vector2i pos;
		} table_checkers_t;

		table_checkers_t** mainArray;

		int arraySize;
		int eCounter;

		int x_pos;
		int y_pos;

		void insert(sf::Vector2i desktop);			//(х, у)
		void resize(int size);
	public:

		GameEngine(sf::RenderWindow &window);
		void step(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
};

#endif