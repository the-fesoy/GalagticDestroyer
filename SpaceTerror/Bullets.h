#pragma once
#include "Enemy.h"
class Bullets
{ 
private:

	sf::Sprite shape;
	sf::Vector2f direction;
	float movementSpeed;

	


public:
	Bullets(sf::Texture * texture, float pos_X , float pos_Y ,float dir_X ,float dir_Y , float movementSpeed);
	//accessor
    const sf::FloatRect getBounds() const ;

	//functions
	void update();
	void render(sf::RenderTarget * target);

	Bullets();
	~Bullets();
};

