#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 800), "RPG Game", sf::Style::Default, settings);
	window.setFramerateLimit(360);
	sf::CircleShape shape(50.f,10);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(20, 20);

	//-------------------------------- INITIALIZE --------------------------------

	//-------------------------------- INITIALIZE --------------------------------

	//-------------------------------- LOAD --------------------------------

	//-------------------------------- LOAD --------------------------------

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time deltaTimeTimer = clock.restart();
		double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

		//-------------------------------- UPDATE --------------------------------
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		//-------------------------------- UPDATE --------------------------------

		//-------------------------------- DRAW --------------------------------
		window.clear(sf::Color::Black);
		window.draw(shape);
		window.display();
		//-------------------------------- DRAW --------------------------------
	}

	return 0;
}