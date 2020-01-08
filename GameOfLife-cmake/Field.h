#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <vector>

class Field final 
	: public sf::Drawable
	, public sf::Transformable
	, public sf::NonCopyable
{
private:
	mutable sf::RectangleShape cellTemplate;
	std::vector<std::vector<bool>> cells;
	sf::Vector2i size;
	std::uint16_t cellSize;
private:
	std::uint8_t getCellNeighboorsCount(size_t i, size_t j) const;
public:
	Field(sf::Vector2i size, std::uint16_t cellSize);

	void init();

	void step();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

