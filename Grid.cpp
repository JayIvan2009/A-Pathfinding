#include "Grid.h"



Grid::Grid(sf::Vector2f &dimensions)
	: dimensions(dimensions)
{
	double i = 0.005 * (this->dimensions.x / (this->dimensions.x * (this->dimensions.x / 1000)));
	gridCount = pow((this->dimensions.x * this->dimensions.y) /
				(this->dimensions.x * (this->dimensions.x * i) + this->dimensions.y * (this->dimensions.y * i)) * .1, 2);
	grid = std::vector<sf::RectangleShape>(gridCount);

	size.x = pow(this->dimensions.x * i * 2, 2);
	size.y = pow(this->dimensions.x * i * 2, 2);
	std::cout << i << std::endl;
	std::cout << gridCount << std::endl;
	std::cout << grid.size() << std::endl;
	std::cout << size.x << std::endl;
	std::cout << size.y << std::endl;
}

Grid::Grid() {
}

Grid::~Grid()
{
	while (!location.empty()) {
		delete location.back();
		location.pop_back();
	}
	while (!node.empty()) {
		delete node.back();
		node.pop_back();
	}
}

void Grid::setGrid() {
	double j = 0.005 * (this->dimensions.x / (this->dimensions.x * (this->dimensions.x / 1000)));
	for (int i = 0; i < gridCount; i++) {
		sf::Vector2f *pos = new sf::Vector2f();
		grid[i].setSize(size);
		size = grid[i].getSize();
		if (position.x == dimensions.x) {
			position.x = 0.0f;
			position.y += size.y;
		}
		grid[i].setPosition(position.x, position.y);
		*pos = grid[i].getPosition();
		location.push_back(pos);
		//std::cout << pos->x << pos->y << std::endl;

		grid[i].setOutlineThickness(-(dimensions.x * j));
		grid[i].setOutlineColor(sf::Color::Color(235, 235, 235));

		Node *temp = new Node(*pos, size, gridCount);
		node.push_back(temp);
		position.x += size.x;

	}
}

void Grid::showGrid(sf::RenderWindow &window) {
	for (int i = 0; i < gridCount; i++) {
		window.draw(grid[i]);
		window.draw(node[i]->getNode());
		node[i]->showText(window);
	}
	/* for (int i = 0; i < gridCount; i++) {
		std::cout << location[i]->x << location[i]->y << std::endl;
	} */
}

void Grid::run(sf::RenderWindow &window) {
	Node firstNode[8], nextNode;
	float posX[8] = { 0.0, 100.0, 0.0, -100.0, -100.0, 100.0, 100.0, -100.0 };
	float posY[8] = { -100.0, 0.0, 100.0, 0.0, -100.0, -100.0, 100.0, 100.0};
	float min = 0.0;
	bool found = false;
	nextNode = start;
	//std::unordered_map<Node, sf::Vector2f> { {firstNode[0], position[0]}};

	//while (!found) {
		/*if (firstNode.getBounds() == end.getBounds()) {
			found = true;
			//break;
		}*/
		//else {
	for (int l = 0; l < 30; l++) {
		for (int i = 0; i < 8; i++) {
			firstNode[i] = nextNode;
			sf::Vector2f tempLocation(firstNode[i].getLocationX() + posX[i], firstNode[i].getLocationY() + posY[i]);
			firstNode[i].setLocation(tempLocation);
			float tempPosX = tempLocation.x;
			float tempPosY = tempLocation.y;
			std::cout << tempPosX << " " << tempPosY << std::endl;
			for (int k = 0; k < node.size(); k++) {
				if (node[k]->getBounds().contains(tempPosX, tempPosY)) {
					//	if (node[i]->getOpen()) {
					node[k]->setColor();
					node[k]->setGHF(*&start.getPosition(), *&end.getPosition(), node);
					if (!found) {
						min = node[k]->getF();
						found = true;
					}
					if (min > node[k]->getF()) {
						min = node[k]->getF();
						nextNode = *node[k];
					}
					//break;
				}
			}
		}
	}
}

void Grid::calcG() {
	
}

void Grid::calcH() {

}

void Grid::calcF() {

}