#include "Field.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <future>
#include <ctime>

std::uint8_t Field::getCellNeighboorsCount(size_t i, size_t j) const
{
	std::uint8_t count = 0;
	count += cells[(i == 0) ? (cells.size() - 1) : (i - 1)][(j == 0) ? (cells[i].size() - 1) : (j - 1)];
	count += cells[(i == 0) ? (cells.size() - 1) : (i - 1)][j];
	count += cells[(i == 0) ? (cells.size() - 1) : (i - 1)][(j == cells[i].size() - 1) ? (0) : (j + 1)];
	count += cells[i][(j == 0) ? (cells[i].size() - 1) : (j - 1)];
	count += cells[i][(j == cells[i].size() - 1) ? (0) : (j + 1)];
	count += cells[(i == cells.size() - 1) ? (0) : (i + 1)][(j == 0) ? (cells[i].size() - 1) : (j - 1)];
	count += cells[(i == cells.size() - 1) ? (0) : (i + 1)][j];
	count += cells[(i == cells.size() - 1) ? (0) : (i + 1)][(j == cells[i].size() - 1) ? (0) : (j + 1)];
	return count;
}

Field::Field(sf::Vector2i size, std::uint16_t cellSize)
	: size(size)
	, cellSize(cellSize)
	, cells(size.y, std::vector<bool>(size.x, false))
{
	cellTemplate.setSize(
		sf::Vector2f(
			static_cast<float>(cellSize),
			static_cast<float>(cellSize)
		)
	);

	cellTemplate.setFillColor(sf::Color::Green);
}

void Field::init()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	for (auto& row : cells)
	{
		for (size_t i = 0; i < row.size(); ++i)
		{
			row[i] = rand() % 2 == 0;
		}
	}
}

void Field::step()
{
	auto temp = cells;
	std::vector<std::future<void>> futures;
	futures.reserve(cells.size());
	for (size_t i = 0; i < cells.size(); ++i)
	{
		futures.emplace_back(
			std::async(
				std::launch::async,
				[this, &temp, i]() {
					for (size_t j = 0; j < cells[i].size(); ++j)
					{
						std::uint8_t count = getCellNeighboorsCount(i, j);

						if (count < 2 || count > 3)
						{
							temp[i][j] = 0;
						}
						else if (count == 3)
						{
							temp[i][j] = true;
						}
					}
				}
			)
		);
	}
	for (auto& fut : futures)
	{
		fut.wait();
	}
	cells = std::move(temp);
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform fieldTransform = getTransform();
	for (size_t i = 0; i < cells.size(); ++i)
	{
		for (size_t j = 0; j < cells[i].size(); ++j)
		{
			if (cells[i][j])
			{
				cellTemplate.setPosition(
					static_cast<float>(cellSize * j),
					static_cast<float>(cellSize * i)
				);
				target.draw(cellTemplate, fieldTransform);
			}
		}
	}
}
