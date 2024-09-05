#include "Character.h"
#include <map>
#include <string>
#include <sstream>
#include "Bullets.h"
#include "Enemy.h"
class Game
{
private:
	sf::RenderWindow * window;
	sf::VideoMode video;
	sf::Event eve;

	std::map<std::string , sf::Texture *> textures;
	std::vector<Bullets*> bullets;
	std::vector<Enemy*> enemies;
	
	Charater* character;
	sf::Texture backgroundTexture;
	sf::Sprite spaceBackground;
	sf::Font font;
	sf::Text PointText;
	sf::Text GameOver;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;


	float spawnTimer;
	float SpawnTM;
	unsigned points;
	int characterHealth;
	int characterHealthMax;



	bool canMove = true;
	void initSystems();
	void initBackground();
	void initGUI();
	void initWindow();
	void initCharacter();
	void initEnemies();
	void initTextures();
public:
	void run();
	void updatePollEvent();
	//collision
	void collision();
	//text stuff
	void updateGUI();
	void renderGUI();
	//world background
	void renderBackground();
	//character and enemies and bullets
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void updateCombate();
	void update();
	void render();
	

	Game();
	~Game();
};
