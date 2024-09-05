#include "Enemy.h"

void Enemy::initshape()
{
	int randR = rand() % 255 + 1;
	int randG = rand() % 255 + 1;
	int randB = rand() % 255 + 1; 
	this->shape.setRadius(this->pointCount + 30);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(randR, randG , randG));

}

void Enemy::initVar()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0.0;
	this->hp = this->hpMax ;
	this->speed = static_cast<float>(this->pointCount) - 2.f;
	this->hpMax = static_cast<int>(this->pointCount);
	this->score = this->pointCount;
	this->damage = this->pointCount * 0.1f;

}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->score;
}

const float& Enemy::getDamage() const
{
	return this->damage;
}




Enemy::Enemy(int pos_x , int pos_y)
{
	
	this->initVar();
	this->initshape();

	this->shape.setPosition(pos_x, pos_y);

}

Enemy::~Enemy()
{
}
