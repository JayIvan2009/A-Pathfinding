#include "Node.h"

Node::Node(sf::Vector2f location, sf::Vector2f size, int gridCount)
	: location(location), size(size), gridCount(gridCount)
{
	if (!font.loadFromFile("font.ttf")) {
		std::cout << "Can't find font!" << std::endl;
	}
	node.setPosition(this->location.x, this->location.y);
	node.setSize(this->size);
	node.setFillColor(sf::Color::Color(0, 0, 0, 0));
}

Node::Node() {
}

Node::~Node()
{
}

void Node::setOpen() {

}

void Node::showNode(sf::RenderWindow &window) {
	window.draw(node);
	/* for (int i = 0; i < gridCount; i++) {
		std::cout << location[i]->x << location[i]->y << std::endl;
	} */
}

void Node::showText(sf::RenderWindow &window) {
	window.draw(GText);
	window.draw(HText);
	window.draw(FText);
}


void Node::setStart() {
	node.setFillColor(sf::Color::Color(0, 0, 200, 125));
	isOpen = false;
	isStart = true;
	
}

void Node::setEnd() {
	node.setFillColor(sf::Color::Color(200, 0, 0, 125));
	isEnd = true;
}

void Node::setBlock() {
	node.setFillColor(sf::Color::Color(0, 0, 0, 200));
	isOpen = false;
	isBlock = true;
}

void Node::status(int i) {
	if (isOpen) {
		std::cout << "Node " << i + 1 << " is open" << std::endl;
	}
	else {
		std::cout << "Node " << i + 1 << " is closed" << std::endl;
	}
	if (isStart) {
		std::cout << "Node " << i + 1 << " is the Start point" << std::endl;
	}
	if (isEnd) {
		std::cout << "Node " << i + 1 << " is the End point" << std::endl;
	}
	if (isBlock) {
		std::cout << "Node " << i + 1 << " is a block" << std::endl;
	}
}

void Node::setColor() {
	node.setFillColor(sf::Color::Color(0, 255, 0, 125));
}

void Node::setGHF(sf::Vector2f &start, sf::Vector2f &end, std::vector<Node*> &nodeSize) {
	std::cout << end.y << " " << location.y << " " << end.x << " " << location.x << std::endl;
	std::cout << start.y << " " << location.y << " " << start.x << " " << location.x << std::endl;
	G = sqrt(pow(end.x - location.x, 2) + pow(end.y - location.y, 2));
	H = sqrt(pow(start.x - location.x, 2) + pow(start.y - location.y, 2));
	F = H + G;

	GText.setFont(font);
	GText.setString(std::to_string(G));  
	GText.setPosition(node.getPosition().x + node.getSize().x * .4, node.getPosition().y + node.getSize().x * .15);
	GText.setCharacterSize(20);
	GText.setFillColor(sf::Color::Color(0, 175, 0));

	HText.setFont(font);
	HText.setString(std::to_string(H));
	HText.setPosition(node.getPosition().x + node.getSize().x * .4, node.getPosition().y + node.getSize().x * .35);
	HText.setCharacterSize(20);
	HText.setFillColor(sf::Color::Color(0, 175, 0));

	FText.setFont(font);
	FText.setString(std::to_string(F));
	FText.setPosition(node.getPosition().x + node.getSize().x * .4, node.getPosition().y + node.getSize().x * .55);
	FText.setCharacterSize(20);
	FText.setFillColor(sf::Color::Color(0, 175, 0));
		
	std::cout << "G: " << G << " " << "H: " << H<<  std::endl;
	std::cout << "F: " << F << std::endl;
}