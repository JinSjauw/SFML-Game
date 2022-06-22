#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow* window;
	
	//View 
	sf::View view;
	
	//Background
	//sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	std::vector<sf::Sprite> backgrounds;

	//Player 
	Player* player;
	sf::Vector2f playerPosition;
	Vector2D movementDirection;


	//Private Functions
	void initWindow();
	void initView(float x, float y, float width, float height);
	void initPlayer();

	void UpdateView();
	void DisplayBackground();

public:
	Game();
	virtual ~Game();

	//Public Functions
	void Running();

	void UpdatePollEvents();
	void Update();
	void Render();
};

