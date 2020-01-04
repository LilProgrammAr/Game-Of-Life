#include <SFML/Graphics.hpp>

int main(int argc, const char** argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Game of Life");
	sf::Event event;
	sf::Clock clock;


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
			default:
				break;
			}
		}

		window.clear();
		window.display();
	}
}