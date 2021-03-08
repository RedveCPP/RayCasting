#include <SFML/Graphics.hpp>
#include "Classes/Player.hpp"
#include "Classes/Wall.hpp"
#include <vector>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "sfml");
	sf::Event mainEvent;
	std::vector<Wall> wallArray;
	wallArray.resize(4 + howManyWalls);
	generateWalls(wallArray);
	bool drawWalls=true;
	Player user(Vector3(400, 300));
	while (window.isOpen()) {
		window.clear();
		while (window.pollEvent(mainEvent)) {
			if (mainEvent.type == mainEvent.Closed) {
				window.close();
			}

			if (mainEvent.key.code == sf::Keyboard::W) {
				user.Move(Vector3(0, -user.playerSpeed));
			}

			if (mainEvent.key.code == sf::Keyboard::S) {
				user.Move(Vector3(0, user.playerSpeed));
			}

			if (mainEvent.key.code == sf::Keyboard::A) {
				user.Move(Vector3(-user.playerSpeed, 0));
			}

			if (mainEvent.key.code == sf::Keyboard::D) {
				user.Move(Vector3(user.playerSpeed, 0));
			}
			
			if (mainEvent.key.code == sf::Keyboard::Q) {
				drawWalls = true;
				if (mainEvent.type == mainEvent.KeyReleased)
				{
					drawWalls = false;
				}
			}
			if (mainEvent.type == mainEvent.KeyPressed)
			{
				if (mainEvent.key.code == sf::Keyboard::E)
				{
					generateWalls(wallArray);
				}
			}
		}
		if (drawWalls)
		{
			for (auto& wall : wallArray)
			{
				wall.draw(window);
			}
		}
		user.CastWalls(wallArray);
		user.Draw(window);
		window.display();
	}
	return 0;
}