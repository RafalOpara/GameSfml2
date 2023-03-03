#include "Game.h"
//private funcktions

void Game::initializeVariables()
{
    this->window = nullptr;

    //game logic

    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimes = this->enemySpawnTimerMax;
    this->maxEnemies = 3;
    this->mouseHeld = false;
    this->startTime = clock();
    this->temp = 50;
    this->gameTime = 0;


    this->help = 0;
    this->greenBox=0;
    this->redBox=0;
    this->greenBoxLeft = maxEnemies;
}

void Game::initWindow()
{

    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
    if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout << "error error error error F O N T S " << std::endl;
    }

}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
}

Game::Game()
{
    this->initializeVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//accessors
const bool Game::running() const
{

    return this->window->isOpen();
}
const bool Game::getEndGame() const
{
    return this->endGame;
}

void Game::spawnEnemy()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        (rand()% static_cast<int>(this->window->getSize().y-this->enemy.getSize().y))
    );


    //randomize enemy type

    int type = rand() % 2;
    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(75.f, 75.f));
        this->enemy.setFillColor(sf::Color::Green);
        
        
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Red);
        this->greenBoxLeft -=1;
        
        break;
    }

  

    //add object to container enemies

    this->enemies.push_back(this->enemy);
}

void Game::poolEvents()
{
    //event polling

    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }


    }

}



void Game::uptadeMousePositions()
{
    //return void uptade the mouse positions: relative to window (vector2i)

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::uptadeTime()
{
    this->stopTime = clock();
    this->gameTime = ((double)(this->stopTime - this->startTime)) / CLOCKS_PER_SEC;
    std::cout << gameTime;
}

void Game::uptadeText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << std::endl;
    ss << "Health: " << this->health << std::endl;
    ss << "Time: " << this->gameTime << std::endl;

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    //updating time for enemey 
  

    //MUSIMY ZNALEZC SPOSOB ABY PRZESTAWALO SPAWNIC AZ ZABIJEMY WSZYSTKIE ZIELONE
    
  
    bool spawnDone = false;
    if (this->help== maxEnemies)
    {
        spawnDone = true;
        
          if (this->greenBoxLeft == 0)
            {
              this->help = 0;
              this->maxEnemies +=1;
              this->enemies.clear();
              this->enemies.shrink_to_fit();
              this->greenBoxLeft = this->maxEnemies;
            }
        
    }
    


    if (spawnDone == false)
    {
        if (this->enemies.size() < this->maxEnemies)
        {
            if (this->enemySpawnTimes >= this->enemySpawnTimerMax)
            {

                //spawn enemy and reset
                this->spawnEnemy();
                this->help++;
                this->enemySpawnTimes = 0.f;
            }
            else
                this->enemySpawnTimes += 1.f;
        }
    }
      
       


    // move the enemies and uptading  TUUUUUTAJ ZMIANA RUSZANIA SIE KUURWA

  /*  for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 3.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "health: " << this->health << std::endl;
        }

    }
    */
    //do something if click

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {

                    //gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Red)
                    {
                        this->points -= 1;
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                    {
                        this->points += 1;
                        this->greenBoxLeft--;
                    }


                    std::cout << "point: " << this->points << std::endl;

                    //delete enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    
                 
                }
            }
            if (!deleted)
            {
                this->health--;
            }
           
           
        }



    }
    else
    {
        this->mouseHeld = false;
    }

   
}
//uptade and render


void Game::uptade()
{
    this->poolEvents();

    if (!this->endGame)
    {

        this->uptadeMousePositions();
        this->uptadeTime();
        this->uptadeText();
        this->updateEnemies();

    }

    if (this->health <= 0)
        this->endGame = true;

}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //rendering all the enemies
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    this->window->clear();

    // draw 
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
