
#include "Game.h"


void Game::initSystems()
{
	this->points = 0;

}

void Game::initBackground()
{
	this->backgroundTexture.loadFromFile("Texture/full-resolution-1280.png");
	this->spaceBackground.setTexture(this->backgroundTexture);
}

void Game::initGUI()
{
	this->font.loadFromFile("Fonts/broderbund-old-bold.ttf");
	this->PointText.setFont(this->font);
	this->PointText.setCharacterSize(20);
	this->PointText.setFillColor(sf::Color::White);


	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(0.f, 30.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	this->GameOver.setFont(this->font);
	this->GameOver.setCharacterSize(100);
	this->GameOver.setFillColor(sf::Color::Red);
	this->GameOver.setString("GAME OVER");
	this->GameOver.setPosition(
		this->window->getSize().x / 2.f - this->GameOver.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->GameOver.getGlobalBounds().height / 2.f);
}

void Game::initWindow()
{
	this->video = sf::VideoMode(600, 600);
	this->window = new sf::RenderWindow(video, "galagtic destroyer", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initCharacter()
{
	this->character = new Charater();
}

void Game::initEnemies()
{
	this->SpawnTM = 100.f;
	this->spawnTimer = SpawnTM;
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Texture/Transparent-Gun-Shooting-Bullet-PNG.png");
	
}

void Game::updateInput()
{
	//movement logic
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->character->move(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->character->move(1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->character->move(0, -1);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->character->move(0, 1);
	}
	//bullets shit
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->character->canAttack())
	{
		this->bullets.push_back(new Bullets(this->textures["BULLET"],
			this->character->getPosition().x,
			this->character->getPosition().y - this->character->getBounds().height/2,
			0.f, -1.f, 5.f));
	}

}

void Game::updatePollEvent()
{

	while (this->window->pollEvent(eve))
	{
		if (eve.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (eve.Event::type == sf::Event::KeyPressed && eve.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
		
	}
}

void Game::collision()
{
	if (this->character->getBounds().left < 0.f)
	{
		this->character->setPosition(0.f , this->character->getPosition().y);
	}
	if (this->character->getBounds().left + this->character->getBounds().width > this->window->getSize().x)
	{
		this->character->setPosition(this->window->getSize().x - this->character->getBounds().width, this->character->getPosition().y);
	}
	if (this->character->getBounds().top < 0.f)
	{
		this->character->setPosition(this->character->getPosition().x, 0.f);

	}
	if (this->character->getBounds().top + this->character->getBounds().height > this->window->getSize().y)
	{
		this->character->setPosition(this->character->getPosition().x, this->window->getSize().y - this->character->getBounds().height);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "score : " << this->points;

	this->PointText.setString(ss.str());


	float hpPercent = static_cast<float>(this->character->getHp()) / this->character->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300 * hpPercent, this->playerHpBar.getSize().y));
}

void Game::renderGUI()
{
	this->window->draw(this->PointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderBackground()
{
	this->window->draw(this->spaceBackground);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvent();
		if (this->character->getHp() > 0)
		{
			this->update();
		}
			this->render();
		
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}

}

void Game::updateEnemies()
{
	this->spawnTimer += 0.8f;
	if (this->spawnTimer >= this->SpawnTM)
	{
		this->enemies.push_back(new Enemy(rand() %this->window->getSize().x - 20, -120));
		this->spawnTimer = 0.f;
	}


	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();
		if (enemy->getBounds().top + enemy->getBounds().height/2 > this->window->getSize().y)
		{
			delete enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		else if (enemy->getBounds().intersects(this->character->getBounds()))
		{

			this->character->l0seHp(this->enemies[counter]->getDamage());
			delete enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			
			--counter;
		}


	
		++counter;
	}
	

}

void Game::updateCombate()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		bool enemy_deleted = false;

		for (size_t j = 0; j < bullets.size() && !enemy_deleted; j++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
				enemy_deleted = true;
			
			}
		}
		
		
		
	}
	
}

void Game::update()
{


	this->updateBullets();
	this->updateEnemies();
	this->updateCombate();
	this->character->update();
	this->updateInput();
	this->collision();
	this->updateGUI();
	
}

void Game::render()
{
	this->window->clear();
	this->renderBackground();
	for (auto* enemy : this->enemies) 
	{
		enemy->render(*this->window);
	}
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	this->character->render(*this->window);

	this->renderGUI();

	if (this->character->getHp() <= 0)
	{
		this->window->draw(this->GameOver);

		
	}

	

	this->window->display();

	
}

Game::Game()
{
	
	this->initWindow();
	this->initSystems();
	this->initBackground();
	this->initTextures();
	this->initCharacter();
	this->initEnemies();
	this->initGUI();
}

Game::~Game()
{
	delete this->window;
	delete this->character;
	for (auto* i : this->enemies)
	{
		delete i;
	}
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	for (auto* i : this->bullets)
	{
		delete i;
	}
}
