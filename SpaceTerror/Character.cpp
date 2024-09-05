
#include "Character.h"



void Charater::initTexture()
{
	if (!this->texture.loadFromFile("Texture/Spaceship-PNG-File.png"))
	{
		std::cout << "fuck youself";
	}
}

void Charater::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.05f, 0.05f);
	this->sprite.setPosition(200.f, 420.f);
}
const sf::Vector2f& Charater::getPosition() const
{


	return this->sprite.getPosition();
}

const sf::FloatRect Charater::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const float& Charater::getHp() const
{
	return this->hp;
}
const float& Charater::getHpMax() const
{
	return this->hpMax;
}
//THESE 2 ARE JUST THE SAME BUT WITH DIFFERENT WAYS OF IMPLEMENTATION
void Charater::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);

}

void Charater::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Charater::sethealth(const float hp)
{
	this->hp = hp;
}

void Charater::l0seHp(const float Damage)
{
	this->hp -= Damage;
}




void Charater::initVar()
{
	this->movementSpeed = 5.f;
	this->attackcdMax = 30.f;
	this->attackcd = this->attackcdMax;
	this->hpMax = 10.f;
	this->hp = this->hpMax;

}


bool Charater::canAttack()
{
	if (this->attackcd >= this->attackcdMax)
	{
		this->attackcd = 0.f;
		return true;
	}
	return false;
}

void Charater::update()
{
	this->updatecd();
}

void Charater::updatecd()
{
	if (this->attackcd < this->attackcdMax)
	{
		this->attackcd += 1.f;
	}

	
}

void Charater::render(sf::RenderTarget& target)
{
	target.draw(sprite);
	
}

void Charater::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

Charater::Charater()
{
	this->initVar();
	this->initTexture();
	this->initSprite();
}

Charater::~Charater()
{
}
