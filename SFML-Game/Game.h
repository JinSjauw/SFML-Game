#pragma once
#include "Player.h"
#include "Enemy.h"
#include <sstream>

class Game
{
private:
	sf::RenderWindow* window;
	
	//View 
	sf::View view;
	
	//Background
	sf::Texture backgroundTexture;
	std::vector<sf::Sprite> backgrounds;

	//Fonts
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text scoreText;

	//Game Logic
	bool gameEnd = false;
	bool gameWin = false;
	int score = 100;

	//Player 
	Player* player;
	sf::Vector2f playerPosition;
	Vector2D movementDirection;

	//Enemies
	std::vector<Enemy*> enemyList;
	int enemyMaxAmount = 0;
	int enemyAmount = 0;
	float spawnTimer;
	float spawnTimerMax;

	//Private Functions

	//Initializing functions
	void initWindow();
	void initView(float x, float y, float width, float height);
	void initText();
	void initPlayer();
	void initEnemies();

	void UpdateView();
	void DisplayBackground();
	
	//Spawn Enemies 
	void UpdateEnemies();

	//Win
	void Win();

public:
	Game();
	virtual ~Game();

	//Public Functions
	void Running();
	
	void UpdateText();
	void UpdatePollEvents();
	void Update();

	void RenderText();
	void Render();
};

