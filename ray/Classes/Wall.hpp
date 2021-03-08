#pragma once
#include "Vector3.hpp"
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Ray;
class Player;
class Wall {
private:
	Vector3 _firstCorner;
	Vector3 _secondCorner;
public:
	Wall() = default;
	Wall(Vector3 startingPoint, Vector3 endingPoint);
	void draw(sf::RenderWindow& window);
	friend class Ray;
};

Wall::Wall(Vector3 startingPoint, Vector3 endingPoint):
	_firstCorner{startingPoint},_secondCorner{endingPoint}
{
}

void Wall::draw(sf::RenderWindow& window) {
	sf::Color wallColor{ sf::Color{255,0,0,255} };
	sf::Vertex Line[]{
		sf::Vertex(sf::Vector2f(_firstCorner.x,_firstCorner.y),wallColor),
		sf::Vertex(sf::Vector2f(_secondCorner.x,_secondCorner.y),wallColor)
	};
	window.draw(Line, 3, sf::Lines);
}

#include <random>
#include <vector>
void generateWalls(std::vector<Wall> &wallArray) {
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distributionX(6, 794); // od x w³¹cznie do y w³¹cznie
	std::uniform_int_distribution<int> distributionY(6, 694); // od x w³¹cznie do y w³¹cznie
	for (auto& wall : wallArray) {
		double x1 = distributionX(generator);
		double x2 = distributionX(generator);
		double y1 = distributionY(generator);
		double y2 = distributionY(generator);
		wall = Wall(Vector3(x1,y1), Vector3(x2,y2));
	}
	// window borders
	wallArray[0]=(Wall(Vector3(5, 5), Vector3(795, 5)));
	wallArray[1]=(Wall(Vector3(5, 5), Vector3(5, 595)));
	wallArray[2]=(Wall(Vector3(5, 595), Vector3(795, 595)));
	wallArray[3]=(Wall(Vector3(795, 5), Vector3(795, 595)));
	
	// box walls, just for testing 
	//wallArray[4] = Wall(Vector3(350, 250), Vector3(450, 250));
	//wallArray[5] = Wall(Vector3(350, 250), Vector3(350, 350));
	//wallArray[6] = Wall(Vector3(350, 350), Vector3(450, 350));
	//wallArray[7] = Wall(Vector3(450, 250), Vector3(450, 350));
}