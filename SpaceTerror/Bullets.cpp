#include "Bullets.h"

Bullets::Bullets(sf::Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float movement_Speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_X,pos_Y);
	this->shape.setScale(0.05f, 0.05f);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->movementSpeed = movement_Speed;

}

const sf::FloatRect Bullets::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullets::update()
{
	this->shape.move(this->movementSpeed * this->direction);

}

void Bullets::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}






Bullets::Bullets()
{
}

Bullets::~Bullets()
{
	
}
