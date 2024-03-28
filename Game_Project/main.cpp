/*
____/\\\\\\\\\__________/\\\\\\\\\\\__/\\\\\\\\\\\\\___        
 __/\\\///////\\\_______\/////\\\///__\/\\\/////////\\\_       
  _\/\\\_____\/\\\___________\/\\\_____\/\\\_______\/\\\_      
   _\/\\\\\\\\\\\/____________\/\\\_____\/\\\\\\\\\\\\\/__     
    _\/\\\//////\\\____________\/\\\_____\/\\\/////////____    
     _\/\\\____\//\\\___________\/\\\_____\/\\\_____________   
      _\/\\\_____\//\\\___/\\\___\/\\\_____\/\\\_____________  
       _\/\\\______\//\\\_\//\\\\\\\\\______\/\\\_____________ 
        _\///________\///___\/////////_______\///______________           
*/

// Robert Parry - Pong - 26/11/22
// RJP - Prototype working - 23/12/22
// RJP - Optimised, Score, Frame Limit, removed ComRacket - 28/03/24

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

// GLOABAL VARIABLES //////////////////////////////////////////////////////////////////

int width = 1000, height = 1000;
double speed = 1;
const double velocityMod = 0.1;
const int racketHeight = 150;
const int racketWidth = 10;
const int ballSize = 10;
int playerScore = 0;
int comScore = 0;

// RACKET /////////////////////////////////////////////////////////////////////////////

class Racket 
{
public:
    Racket(double x, double y);
    
    void up();
    void down();
    void update();
    
    sf::RectangleShape getRacketObject();
    sf::FloatRect getRacketFloatRect();
    sf::Vector2f getRacketPosition();
    
private:
    sf::Vector2f racketPosition;
    sf::RectangleShape racketObject;
};

Racket::Racket(double x, double y) 
{
    racketPosition.x = x;
    racketPosition.y = y;
    racketObject.setSize(sf::Vector2f(racketWidth, racketHeight));
    racketObject.setPosition(racketPosition);
}

sf::Vector2f Racket::getRacketPosition() 
{
    return racketPosition;
}

sf::RectangleShape Racket::getRacketObject() 
{
    return racketObject;
}

sf::FloatRect Racket::getRacketFloatRect() 
{
    return racketObject.getGlobalBounds();
}

void Racket::up() 
{
    racketPosition.y -= speed;
}

void Racket::down() 
{
    racketPosition.y += speed;
}

void Racket::update() 
{
    racketObject.setPosition(racketPosition);
}

// BALL ///////////////////////////////////////////////////////////////////////////////

class Ball 
{
public:
    Ball(float startX, float startY);
 
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    float getXVelocity();
    void reboundSides();
    void reboundBat();
    void hitLeft();
    void hitRight();
    void update();
    
private:
    sf::Vector2f position;
    sf::RectangleShape ballShape;
    float xVelocity;
    float yVelocity;
};

Ball::Ball(float startX, float startY) 
{
    position.x = startX;
    position.y = startY;
    ballShape.setSize(sf::Vector2f(ballSize, ballSize));
    ballShape.setPosition(position);
    xVelocity = 0.2f;
    yVelocity = 0.2f;
}

sf::FloatRect Ball::getPosition() 
{
    return ballShape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape() 
{
    return ballShape;
}

float Ball::getXVelocity() 
{
    return xVelocity;
}

void Ball::reboundSides() {
    yVelocity = -yVelocity;
}

void Ball::reboundBat() 
{
    position.x -= (xVelocity * 30);
    if (rand() % 2 == 0)
    {
        xVelocity = -xVelocity;
        xVelocity += (xVelocity > 0) ? velocityMod : -velocityMod;
        yVelocity += (yVelocity > 0) ? velocityMod : -velocityMod;
    }
}

void Ball::hitLeft() 
{
    position.x = width/2;
    position.y = std::rand() % height + 1;
    xVelocity = -0.2f;
    yVelocity = -0.2f;
    playerScore++;
}

void Ball::hitRight() 
{
    position.x = width/2;
    position.y = std::rand() % height + 1;
    xVelocity = 0.2f;
    yVelocity = 0.2f;
    comScore++;
}

void Ball::update() 
{
    position.y += yVelocity;
    position.x += xVelocity;
    ballShape.setPosition(position);
}

// MAIN ///////////////////////////////////////////////////////////////////////////////

int main(int, char const**) 
{
    Racket racket(width - 20, height / 2);
    Racket comRacket(20, height / 2);
    Ball ball(width / 2, height / 2 + 50);
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Game Window");
    window.setFramerateLimit(60);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) 
    {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "gameFont.ttf")) 
    {
        return EXIT_FAILURE;
    }
    sf::Text text("Pong", font, 50);
    text.setFillColor(sf::Color::White);

    // Create text objects for displaying scores
    sf::Text playerScoreText;
    sf::Text comScoreText;
    playerScoreText.setFont(font);
    comScoreText.setFont(font);
    playerScoreText.setCharacterSize(30);
    comScoreText.setCharacterSize(30);
    playerScoreText.setFillColor(sf::Color::White);
    comScoreText.setFillColor(sf::Color::White);
    playerScoreText.setPosition(width - 150, 20);
    comScoreText.setPosition(100, 20);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        {
            racket.up();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
        {
            racket.down();
        }

        if (racket.getRacketPosition().y == (height - 150)) 
        {
            std::cout << "Boundary top" << std::endl;
        }
        else if (racket.getRacketPosition().y == 10) 
        {
            std::cout << "Boundary bottom" << std::endl;
        }

        if (ball.getPosition().top > width || ball.getPosition().top < 0) 
        {
            ball.reboundSides();
        }

        if (ball.getPosition().left < 0) 
        {
            ball.hitLeft();
        }

        if (ball.getPosition().left > width) 
        {
            ball.hitRight();
        }

        if (ball.getPosition().intersects(racket.getRacketFloatRect())) 
        {
            ball.reboundBat();
        }

        if (ball.getPosition().left < 400) 
        {
            if (ball.getPosition().top < comRacket.getRacketPosition().y) 
            {
                comRacket.up();
            }
            else if (ball.getPosition().top > comRacket.getRacketPosition().y) 
            {
                comRacket.down();
            }
        }

        if (ball.getPosition().intersects(comRacket.getRacketFloatRect())) 
        {
            ball.reboundBat();
        }



        window.clear(sf::Color::Black);
        window.draw(racket.getRacketObject());
        window.draw(comRacket.getRacketObject());
        window.draw(ball.getShape());
        window.display();

        playerScoreText.setString("Player: " + std::to_string(playerScore));
        comScoreText.setString("Computer: " + std::to_string(comScore));

        racket.update();
        comRacket.update();
        ball.update();
    }

    return EXIT_SUCCESS;
}