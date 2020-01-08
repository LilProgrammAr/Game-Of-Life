#include <Field.h>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Game of Life");
	sf::Event event;
	sf::Clock clock;

	window.setFramerateLimit(30);

	Field field({ 50, 50 }, 8);
	field.init();
	field.setPosition(0, 0);

	sf::Font terminal;
	terminal.loadFromFile("Resources/terminal.ttf");
	sf::Text fpsText;
	fpsText.setFont(terminal);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setOutlineColor(sf::Color::Black);
	fpsText.setOutlineThickness(2);
	fpsText.setPosition(0, 0);

	bool mousePressed = false;

	float cameraScale = 1.f;

	sf::View ui = window.getView();

	while (window.isOpen())
	{
		sf::View gameView = window.getView();
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
				gameView = sf::View(visibleArea);
				ui = sf::View(visibleArea);
				window.setView(gameView);
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				float scale = event.mouseWheelScroll.delta > 0 ? (0.9f) : (1.1f);
				gameView.zoom(scale);
				cameraScale *= scale;
				window.setView(gameView);
				break;
			}
			case sf::Event::MouseButtonPressed:
				mousePressed = true;
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;
			case sf::Event::MouseMoved:
			{
				static sf::Vector2f lastMousePos;
				float x = event.mouseMove.x;
				float y = event.mouseMove.y;
				if (mousePressed)
				{
					gameView.move((lastMousePos.x - x) * cameraScale,(lastMousePos.y - y) * cameraScale);
					window.setView(gameView);
				}
				lastMousePos.x = x;
				lastMousePos.y = y;
				break;
			}
			default:
				break;
			}
		}

		field.step();

		fpsText.setString("FPS: " + std::to_string(1.f / clock.getElapsedTime().asSeconds()));

		window.clear();
		window.draw(field);
		{
			sf::View view = window.getView();
			window.setView(ui);
			window.draw(fpsText);
			window.setView(view);
		}
		clock.restart();
		window.display();
	}
}