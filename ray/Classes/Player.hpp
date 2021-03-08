#pragma once
#include "Vector3.hpp"
#include "Ray.hpp"
#include <array>
#include <vector>
double ToRadians(double angle) {
	return angle * M_PI / 180;
}

class Wall;
class Player {
private:
	std::array<Ray, howManyRays> _rayArray;
	Vector3 _playerPos;
	sf::CircleShape playerCircle;
public:
	Player(Vector3 position);
	void Move(const Vector3& vector);
	void Draw(sf::RenderWindow& window);
	void CastWalls(std::vector<Wall> walls);
	const int playerSpeed{5 };
};

void Player::CastWalls(std::vector<Wall> walls) {
	for (auto& ray : _rayArray) {
		ray.WallIntersection(walls);
	}
}
#include <iostream>
Player::Player(Vector3 position):
	_playerPos{ position } {
	for (int i = 0; i < howManyRays;++i) {
		_rayArray[i] = Ray(_playerPos, ToRadians(i*0.1));
	}
	playerCircle.setFillColor(sf::Color::Blue);
	playerCircle.setRadius(10);
	playerCircle.setPosition(_playerPos.x-playerCircle.getRadius(), _playerPos.y - playerCircle.getRadius());
}

void Player::Move(const Vector3 &vector) {
	_playerPos += vector;
	for (auto& ray : _rayArray) {
		ray.SetStart(_playerPos);
	}
	
	playerCircle.setPosition(playerCircle.getPosition().x + vector.x, playerCircle.getPosition().y + vector.y);
}


void Player::Draw(sf::RenderWindow& window) {
	for (auto& ray : _rayArray) {
		ray.Draw(window);
	}
	window.draw(playerCircle);
}