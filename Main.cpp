#include <iostream>

#include "Node.h"
#include "Grid.h"

int main() {
	unsigned int d = 0;
	bool loop = true;
	bool start = true;
	bool end = true;
	std::cout << "Enter window size: ";
	std::cin >> d;

	sf::RenderWindow window(sf::VideoMode(d, d), "Pathfinding");
	//std::vector<sf::RectangleShape*> grid;
	sf::Vector2f position(0.0f, 0.0f);
	sf::Vector2f dimensions((float)d, (float)d);

	//std::string color;
	std::vector<unsigned int> color(4);

	Grid grid(dimensions);
	grid.setGrid();
	Node node();


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::S:
					if (start) {
						start = false;
						loop = true;
						std::cout << "Click to add Start point" << std::endl;
						while (loop) {
							if (sf::Event::MouseButtonPressed) {
								if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
									sf::Vector2i mousePos = sf::Mouse::getPosition(window);
									auto translatedPos = window.mapPixelToCoords(mousePos);
									for (int i = 0; i < grid.getOpenNode(); i++) {
										if (grid.getNodeBounds(i).contains(translatedPos)) {
											if (grid.getNode(i)->getOpen() && !grid.getNode(i)->getEnd()) {
												grid.getNode(i)->setStart();
												grid.setStart(i);
												break;
											}
											else {
												std::cout << "Can't place point here" << std::endl;
												start = true;
												break;
											}
										}
									}
									loop = false;
									break;
								}
							}
						}
						break;
					}
					else {
						std::cout << "Start point already exists!" << std::endl;
						break;
					}

				case sf::Keyboard::E:
					if (end) {
						end = false;
						loop = true;
						std::cout << "Click to add End Point" << std::endl;
						while (loop) {
							if (sf::Event::MouseButtonPressed) {
								if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
									sf::Vector2i mousePos = sf::Mouse::getPosition(window);
									auto translatedPos = window.mapPixelToCoords(mousePos);
									for (int i = 0; i < grid.getOpenNode(); i++) {
										if (grid.getNodeBounds(i).contains(translatedPos)) {
											if (grid.getNode(i)->getOpen()) {
												grid.getNode(i)->setEnd();
												grid.setEnd(i);
												break;
											}
											else {
												std::cout << "Can't place point here" << std::endl;
												end = true;
												break;
											}
										}
									}
									loop = false;
									break;
								}
							}
						}
						break;
					}
					else {
						std::cout << "End point already exists!" << std::endl;
						break;
					}

				case sf::Keyboard::B:
					loop = true;
					std::cout << "Click to add Blocks" << std::endl;
					while (loop) {
						if (sf::Event::MouseButtonPressed) {
							while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								sf::Vector2i mousePos = sf::Mouse::getPosition(window);
								auto translatedPos = window.mapPixelToCoords(mousePos);
								for (int i = 0; i < grid.getOpenNode(); i++) {
									if (grid.getNodeBounds(i).contains(translatedPos)) {
										grid.getNode(i)->setBlock();
									}
								}
								loop = false;
							}
						}
					}
					break;

				case sf::Keyboard::X:
					for (int i = 0; i < grid.getGrid(); i++) {
						grid.getNodeStatus(i);
					}
					break;

				case sf::Keyboard::Enter:
					grid.run(window);
					break;
				}
			}
		}
		window.clear();
		grid.showGrid(window);
		//node.showGrid(window);
		window.display();
	}
}