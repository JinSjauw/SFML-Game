#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(720, 1200), "Raket Spel", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

	this->backgroundTexture.loadFromFile("Assets/Background2.png");
	
	
	//Filling up the list with 3 copies of the same background sprite
	for (unsigned int i = 0; i < 15; i++) 
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
}

void Game::initText()
{
	if (this->font.loadFromFile("Fonts/Pixeboy-z8XGD.ttf")) 
	{
		this->uiText.setFont(this->font);
		this->uiText.setCharacterSize(120);
		this->uiText.setFillColor(sf::Color::White);
		this->uiText.setString("");

		this->scoreText.setFont(this->font);
		this->scoreText.setCharacterSize(40);
		this->scoreText.setFillColor(sf::Color::White);
		this->scoreText.setString("SCORE TEXT : SCORE");
	}
}

void Game::initPlayer()
{
	initView(
	this->window->getSize().x / 2, this->window->getSize().y / 2,
	this->window->getSize().x, this->window->getSize().y);

	this->player = new Player();
	this->player->setPositicon(this->view.getSize().x / 2, this->view.getSize().y - this->player->getSprite().getGlobalBounds().height + 10.f);
	this->playerPosition = this->player->getSprite().getPosition();
}

void Game::initEnemies()
{
	this->enemyMaxAmount = 15;

	Vector2D position = Vector2D(300.f, 600.f);
	this->enemy = new Enemy();
	this->enemy->SetPosition(position.x, position.y);
	this->spawnTimerMax = 35.f;
	this->spawnTimer = this->spawnTimerMax;

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

void Game::UpdateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax && this->enemyAmount < this->enemyMaxAmount)
	{
		Vector2D position = Vector2D(rand() % this->window->getSize().x, this->view.getCenter().y - this->view.getSize().y);
		float randomSize = (rand() % 4 + 1) / 10.f;
		
		//Creating enemy
		Enemy* enemy = new Enemy(position, randomSize, (rand() % 4 + 1) / 10.f);

		//Setting direction for movement
		float randomAngle = (rand() % 1 + 1) / 10.f;
		int randomDirection = rand() % 2;
		Vector2D direction = Vector2D(randomAngle * ((randomDirection < 1) ? -1.f : 1.f), 1.f);
		enemy->SetDirection(direction);

		this->enemyList.push_back(enemy);
		this->enemyAmount++;
		this->spawnTimer = 0.f;
	}

	for (int i = 0; i < this->enemyList.size(); i++) 
	{
		this->enemyList[i]->Update(this->window);
		if (this->enemyList[i]->TestCollision(this->enemyList[i]->getSprite(), this->player->getSprite())) 
		{
			this->enemyList.erase(this->enemyList.begin() + i);
			this->enemyAmount--;
			std::cout << this->enemyList.size() << " Enemy Collision!" << std::endl;
			this->score -= 10;
			if (score <= 0) 
			{
				gameEnd = true;
				gameWin = false;
				this->uiText.setString("YOU DIED");
			}
		}

		//Remove enemies when they pass the bottom screen
		if (this->enemyList[i]->getPosition().y > this->view.getCenter().y + this->view.getSize().y / 2) 
		{
			this->enemyList.erase(this->enemyList.begin() + i);
			this->enemyAmount--;
			std::cout << this->enemyList.size() << " Enemy Deleted!" << std::endl;
		}
	}
}

void Game::Win()
{
	if (player->getSprite().getPosition().y + player->getSprite().getGlobalBounds().height < this->view.getCenter().y - this->view.getSize().y / 2) 
	{
		gameEnd = true;
		gameWin = true;
		this->uiText.setString("YOU WON");
	}
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initEnemies();
	this->initText();
}

Game::~Game()
{	
	//Delete pointers
	for (auto* enemy : enemyList) 
	{
		delete enemy;
	}
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

void Game::UpdateText()
{
	std::stringstream ss;

	ss << "Score: " << this->score;
	this->scoreText.setString(ss.str());
	this->scoreText.setPosition(20.f, this->view.getCenter().y - this->view.getSize().y / 2 );

	this->uiText.setPosition(this->view.getCenter().x - this->uiText.getGlobalBounds().width / 2, this->view.getCenter().y - this->uiText.getGlobalBounds().height / 2);

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

	if (gameEnd)
		return;

	this->UpdateView();
	this->player->Update(this->window);
	this->window->setView(this->view);
	this->UpdateEnemies();
	this->Win();
	this->UpdateText();
	
}

void Game::RenderText()
{
	this->window->draw(this->uiText);
	this->window->draw(this->scoreText);
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
	for (auto *enemy : this->enemyList) 
	{
		enemy->Render(*this->window);
	}

	this->RenderText();

	//Present
	this->window->display();
}
