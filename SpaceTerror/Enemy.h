#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
class Enemy
{
private:

	sf::CircleShape shape;

	float type;
	float hp;
	float hpMax;
	unsigned pointCount;
	float speed;
	int score;
	float damage;
	void initshape();
	void initVar();

public:
	void update();
	void render(sf::RenderTarget& target);
	//accessors
	const sf::FloatRect getBounds() const;

	const int& getPoints() const;
	const float& getDamage() const;
	Enemy(int pos_x, int pos_y);
	~Enemy();



};

