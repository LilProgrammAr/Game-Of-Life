#include "Field.h"
#include <SFML/Graphics.hpp>

int main(int argc, const char** argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Game of Life");
	sf::Event event;
	sf::Clock clock;

	window.setFramerateLimit(60);

	Field field({100, 100}, 4);
	field.init();
	field.setPosition(0, 0);

	sf::Font terminal;
	terminal.loadFromFile("Resources/terminal.ttf");
	sf::Text fpsText;
	fpsText.setFont(terminal);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setOutlineColor(sf::Color::Black);
	fpsText.setPosition(0, 0);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(
					0.f,
					0.f,
					static_cast<float>(event.size.width),
					static_cast<float>(event.size.height)
				);
				window.setView(sf::View(visibleArea));
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				sf::View view = window.getView();
				view.zoom(event.mouseWheelScroll.delta >  0 ? (0.9f) : (1.1f));
				window.setView(view);
			}
			default:
				break;
			}
		}

		field.step();

		fpsText.setString("FPS: " + std::to_string(sf::seconds(1.f).asMilliseconds() / clock.getElapsedTime().asMilliseconds()));

		window.clear();
		window.draw(field);
		{
			sf::View view = window.getView();
			window.setView(window.getDefaultView());
			window.draw(fpsText);
			window.setView(view);
		}
		window.display();
		clock.restart();
	}
}