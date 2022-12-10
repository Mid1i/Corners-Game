#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window)
{
	x_pos = 67;
	y_pos = 67;

	White_Circle_1.setRadius(15);
	White_Circle_1.setFillColor(sf::Color::White);
	White_Circle_1.setPosition(x_pos, y_pos);
	
}

void GameEngine::draw(sf::RenderWindow &window)
{
	window.draw(White_Circle_1);
}

void GameEngine::step(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		x_pos -= 56;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		y_pos -= 56;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		x_pos += 56;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		y_pos += 56;
	}

	White_Circle_1.setPosition(x_pos, y_pos);
	window.draw(White_Circle_1);
	Sleep(65);
}