#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(720, 1200), "Raket Spel", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

	this->backgroundTexture.loadFromFile("Assets/Background2.png");
	this->backgroundTexture.setRepeated(true);
	
	//Filling up the list with 3 copies of the same background sprite
	for (unsigned int i = 0; i < 20; i++) 
	{
		sf::Sprite backgroundSprite;
		backgroundSprite.setTexture(this->backgroundTexture);
		backgroundSprite.setPosition(0, backgroundSprite.getGlobalBounds().height - (i * backgroundSprite.getGlobalBounds().height));
		this->backgrounds.push_back(backgroundSprite);
		
	}
}

void Game::initView(float x, float y, float width, float height)
{
	this->view.setCenter(x, y);
	this->view.setSize(width, height);
	this->window->setView(this->view);
	//std::cout << "View position " << this->view.getCenter().x << " : " << this->view.getCenter().y << std::endl;
}

void Game::initPlayer()
{
	initView(
	this->window->getSize().x / 2, this->window->getSize().y / 2,
	this->window->getSize().x, this->window->getSize().y);

	this->player = new Player();
	this->player->setPositicon(this->view.getSize().x / 2, this->view.getSize().y - this->player->getSprite().getGlobalBounds().height - 10.f);
	this->playerPosition = this->player->getSprite().getPosition();
}

void Game::UpdateView()
{
	this->playerPosition = this->player->getSprite().getPosition();

	//If Player passes the 2nd last background the view stops moving.
	if (this->playerPosition.y < this->backgrounds[this->backgrounds.size() - 2].getPosition().y)
		return;

	//If player passes past a certain point the view gets centered on the player
	if (this->playerPosition.y < this->view.getSize().y / 2)
	{
		this->view.setCenter(this->window->getSize().x / 2, playerPosition.y);
	}
	else 
	{
		this->view.setCenter(this->window->getSize().x / 2, this->view.getCenter().y);
	}
}

void Game::DisplayBackground()
{
	for (auto item : backgrounds) 
	{
		this->window->draw(item);
	}
}

void Game::initEnemies()
{
	this->enemyTotalAmount = 20;
	Vector2D position = Vector2D(300.f, 600.f);
	std::cout << "Position: " << position << std::endl;
	this->enemy = new Enemy(position, .2f, .2f);
	
}

void Game::SpawnEnemies()
{

		
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{	
	//Delete pointers
	delete this->player;
	delete this->enemy;
	delete this->window;
}

//Functions
void Game::Running()
{
	while (this->window->isOpen()) 
	{
		this->Update();
		this->Render();
	}
}

void Game::UpdatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::Update()
{
	this->UpdatePollEvents();
	UpdateView();
	this->player->Update(this->window);
	this->window->setView(this->view);
	SpawnEnemies();
}

void Game::Render()
{
	this->window->clear();

	//Drawing
	
	//Drawing background
	DisplayBackground();

	//Drawing Player
	this->player->Render(*this->window);
	//Drawing Enemy
	this->enemy->Render(*this->window);

	//Present
	this->window->display();
}
