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
	Node neighbourNode[8];
	bool set = true;
	bool initial = true;
	bool init = true;
	baseNode = start;

	//while (!found) {
	while (!found) {
		findNeighbours(neighbourNode);
	}
}

void Grid::findNeighbours(Node neighbourNode[]) {
	bool set = true;
	int j = 0;
	for (int i = 0; i < 8; i++) {
		neighbourNode[i] = baseNode;
		sf::Vector2f tempLocation(neighbourNode[i].getLocationX() + posX[i], neighbourNode[i].getLocationY() + posY[i]);
		neighbourNode[i].setLocation(tempLocation);
		float tempPosX = tempLocation.x;
		float tempPosY = tempLocation.y;
		for (int k = 0; k < node.size(); k++) {
			if (node[k]->getBounds().contains(tempPosX, tempPosY)) {
				if (node[k]->getBounds().contains(end.getLocationX(), end.getLocationY())) {
					std::cout << "Found End!" << std::endl;
					found = true;
					return;
				}
				if (node[k]->getOpen() && !node[k]->getEnd()) {
					node[k]->setColor();
					node[k]->setGHF(*&start.getPosition(), *&end.getPosition(), node);
					if (set) {
						min = node[k]->getF();
						set = false;
					}
					if (min >= node[k]->getF()) {
						min = node[k]->getF();
						j = k;
						break;
					}
					break;
				}
				break;
			}
		}
	}
	node[j]->setPath();
	baseNode = *node[j];
}