#include <SFML/Graphics.hpp>
#include "map.h"
#include "GameEngine.h"

using namespace sf;

int main() {
	RenderWindow window(VideoMode(560, 560), "Game");

	Image map_image;
	map_image.loadFromFile("C:/C++/sfml/src/Images/cells.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	GameEngine eng(window);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		for (int i=0;i<HEIGHT_MAP;i++)
		for (int j=0;j<WIDTH_MAP;j++)
		{
			if (TileMap[i][j] == 'B') s_map.setTextureRect(IntRect(0, 57, 0, 0));
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(0, 0, 56, 56));
			if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect(56, 0, 56, 56));

			s_map.setPosition(j*56, i*56);
			window.draw(s_map);
		}

		eng.draw(window);
		eng.step(window);

		window.display();
	}

	return 0;
}