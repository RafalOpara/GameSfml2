#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include<sstream>
#include <time.h>
#include <math.h>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Game
{
private:
    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // mouse positions

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    //text
    sf::Text uiText;

    //game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimes;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    int startTime;
    int stopTime;
    int gameTime;
    int temp;
  
   
    int help;
    int greenBox;
    int redBox;
    int greenBoxLeft;

    //game objects

    std::vector<sf::ConvexShape> enemies;
    sf::ConvexShape enemy;

    //private funckions

    void initializeVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();
    void initTime();

public:
    //constructor destructor
    Game();
    virtual ~Game();

    //accessors
    const bool running() const;
    const bool getEndGame() const;


    //funcktons
    void spawnEnemy();


    void poolEvents();
    void uptadeMousePositions();
    void uptadeText();
    void uptadeTime();
    void updateEnemies();
    void uptade();


    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();
};