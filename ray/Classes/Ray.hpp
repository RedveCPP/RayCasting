#pragma once
#include "Vector3.hpp"
#include "Wall.hpp"
#include <SFML/Graphics.hpp>
//#include <vector>
class Ray {
private:
	Vector3 _startingPos;
	Vector3 _endingPos;
	Vector3 _corePos;
	double _angle{};
	int _multiplier{ 360 };
public:
	Ray() = default;
	Ray(Vector3 startingPos, double angle);
	void Draw(sf::RenderWindow& window);
	void WallIntersection(std::vector<Wall> wallArray);
	void SetStart(const Vector3 point);
};
#include <iostream>
void Ray::SetStart(const Vector3 point) {
	_startingPos = point;
}

#include <cmath>
Ray::Ray(Vector3 startingPos, double angle) :
	_startingPos{ startingPos }, _angle{ angle }, _multiplier{ 360 } {
	int multiplier{ 360 };
	double x = sin(angle) * 360 * multiplier;
	double y = cos(angle) * 360 * multiplier;
	_endingPos = Vector3(x, y);
	_corePos = _endingPos;
}

void Ray::Draw(sf::RenderWindow& window) {
	sf::Color color(184, 0, 0);
	color = sf::Color::White;
	color.a = 50;

	sf::Vertex Line[]{
			sf::Vertex(sf::Vector2f(_startingPos.x,_startingPos.y),color),
			sf::Vertex(sf::Vector2f(_endingPos.x,_endingPos.y),color)
	};
	window.draw(Line, 3, sf::Lines);
}

void Ray::WallIntersection(std::vector<Wall> wallArray) {
	_endingPos = _corePos;
	Vector3 recordPoint = INFINITY;
	double rayLimit = 50;
	for (auto& wall : wallArray) {
		// formula parts
		double x1{ _startingPos.x };
		double x2{ _endingPos.x };
		double x3{ wall._firstCorner.x };
		double x4{ wall._secondCorner.x };
		double y1{ _startingPos.y };
		double y2{ _endingPos.y };
		double y3{ wall._firstCorner.y };
		double y4{ wall._secondCorner.y };
		double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

		if (den == 0) {
			return;
		}

		double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		// if interact with wall, calculate where
		if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) {
			double x = (x3 + u * (x4 - x3));
			double y = (y1 + t * (y2 - y1));
			double recordPointDistance = GetDistance(_startingPos, recordPoint);
			double newPointDistance = GetDistance(_startingPos, Vector3(x, y));
			if (newPointDistance < recordPointDistance) {
				recordPoint = Vector3(x, y);
			}

		}

	}
	_endingPos = recordPoint;
}