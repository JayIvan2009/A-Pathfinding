#pragma once
#include <iostream>
#include <vld.h>
#include <cmath>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "Node.h"

class Grid
{
public:
	Grid(sf::Vector2f &dimensions);
	Grid();
	~Grid();

	void setGrid();
	void showGrid(sf::RenderWindow &window);
	void getNodeStatus(int i) { node[i]->status(i); };
	int getGrid() { return gridCount; };

	void setStart(int i) { start = *node[i]; };
	void setEnd(int i) { end = *node[i]; };
	Node getStart() { return start; };
	Node getEnd() { return end; };

	sf::FloatRect getNodeBounds(int i) { return node[i]->getBounds(); };
	Node* getNode(int i) { return node[i]; };
	size_t getOpenNode() { return node.size(); };

	void run(sf::RenderWindow &window);
	void findNeighbours(Node neighbourNode[]);

private:
	sf::RenderWindow window;
	sf::Vector2f position = sf::Vector2f(0.0f, 0.0f);
	std::vector<Node*> tempNode;

protected:
	sf::Vector2f dimensions;
	std::vector<Node*> node;
	std::vector<Node*> openNode;
	std::vector<Node*> closedNode;
	Node start;
	Node end;
	Node baseNode;
	std::vector<sf::RectangleShape> grid;
	std::vector<sf::Vector2f*> location;
	sf::Vector2f size;
	int gridCount;
	bool found = false;
	float min = 0.0;

	const float posX[8] = { 0.0, 100.0, 0.0, -100.0, -100.0, 100.0, 100.0, -100.0 };
	const float posY[8] = { -100.0, 0.0, 100.0, 0.0, -100.0, -100.0, 100.0, 100.0 };
};

