#pragma once
#include "Bullets.h"
class Charater
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	float attackcd;
	float attackcdMax;
	float hp;
	float hpMax;

	void initTexture();
	void initSprite();
	void initVar();
public:

	//acccessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;
	const float& getHp() const;
	const float& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void sethealth(const float hp);
	void l0seHp(const float Damage);
	//functions 

	bool canAttack();
	void update();
	void updatecd();
	void render(sf::RenderTarget& target);
	void move(const float dirX, const float dirY);
	Charater();
	~Charater();


};

