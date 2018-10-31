#pragma once
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

class Node
{
public:
	Node(sf::Vector2f location, sf::Vector2f size, int gridCount);
	Node();
	~Node();
	void setOpen();
	void showNode(sf::RenderWindow &window);
	void showText(sf::RenderWindow &window);
	void setStart();
	void setEnd();
	void setBlock();
	void status(int i);
	void setGHF(sf::Vector2f &start, sf::Vector2f &end, std::vector<Node*> &nodeSize);
	void setLocation(sf::Vector2f locaton) { this->location = location; };
	void setColor();
	void setTest() { node.setFillColor(sf::Color::Blue); };

	bool getOpen() { return isOpen; };
	bool getEnd() { return isEnd; };
	sf::RectangleShape getNode() { return node; };
	sf::FloatRect getBounds() { return node.getGlobalBounds(); };
	float getLocationX() { return location.x; };
	float getLocationY() { return location.y; };
	sf::Vector2f getPosition() { return location; };
	int getF() { return F; };

	void show() {
		std::cout << location.x << " " << location.y << std::endl;
	}

private:
	int G, H, F;
	sf::Text GText, HText, FText;
	sf::Font font;

protected:
	sf::RectangleShape node;
	sf::Vector2f location;
	sf::Vector2f size;
	int gridCount;
	bool isOpen = true;
	bool isBlock = false;
	bool isStart = false;
	bool isEnd = false;
};

