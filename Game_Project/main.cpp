//Robert Parry - Pong - 26/11/22-//22
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "ResourcePath.hpp"

//TODO: ball, comBat, boundaries, frame limit


int width = 1000, height = 1000;//Window width and height;
int score = 0;
int maxY = height - 10;
int minY = (height - height) + 10;

class Racket {
public:
    Racket(double x, double y);
    
    void up();
    void down();
    void update();
    
    sf::RectangleShape getRacketObject();
    sf::FloatRect getRacketFloatRect();
    sf::Vector2f getRacketPosition();
    
private:
    double speed = 1;
    
    sf::Vector2f racketPosition;
    sf::RectangleShape racketObject;
    
};

class comRacket {
public:
    comRacket(double x, double y);
    void comUp();
    void comDown();
private:
    sf::Vector2f comRacketPos;
    double speed = 1;
};

class Ball
{
private:
    sf::Vector2f position;
 
    // A RectangleShape object called ref
    sf::RectangleShape ballShape;
 
    float xVelocity = .2f;
    float yVelocity = .2f;
    float velocityMod = .1f;
 
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
 
};

int main(int, char const**)
{
    Racket racket(width-20, height/2);
    Ball ball(width/2, height/2+50);
    comRacket ComRacket(height/2, 10);
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Game Window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "gameFont.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Pong", font, 50);
    text.setFillColor(sf::Color::White);

    //Main window/////////////////////////////////////////////////////////////////////////
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        //UserInput
        if(((event.type == event.KeyPressed) && event.key.code == sf::Keyboard::Up)) {
            std::cout << "Up Key Pressed" << std::endl;
            racket.up();
        }
        
        if(((event.type == event.KeyPressed) && event.key.code == sf::Keyboard::Down)) {
            std::cout << "Down Key Pressed" << std::endl;
            racket.down();
        }
        
        //Boundaries
        if(racket.getRacketPosition().y == (height - 150))
        {
            std::cout << "Boundary top";
        }
        else if(racket.getRacketPosition().y == ((height - height) + 150))
        {
            std::cout << "Boundary bottom";
        }

        // Handle ball hitting the bottom or top
        if (ball.getPosition().top > width || ball.getPosition().top < 0)
        {
            ball.reboundSides();
        }
         
        // Handle ball left side
        if (ball.getPosition().left < 0)
        {
            //ball.hitLeft();
            ball.reboundBat();
        }
         
        // Reset ball after hitting right side
        if ( ball.getPosition().left > width)
        {
            ball.hitRight();
        }
         
        
        
        // bat reflect
        if (ball.getPosition().intersects(racket.getRacketFloatRect()))
        {
            ball.reboundBat();
        }

        
        
        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
        
        racket.update();
        ball.update();
        
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(racket.getRacketObject());
        window.draw(ball.getShape());
       
    }
    return EXIT_SUCCESS;
}


//Functionality/////////////////////////////////////////////////////

//Racket//////////////////////////////////

Racket::Racket(double x, double y){
       racketPosition.x = x;
       racketPosition.y = y;
       racketObject.setSize(sf::Vector2f(10, 150));
       racketObject.setPosition(racketPosition);
};

sf::Vector2f Racket::getRacketPosition() {
    return racketPosition;
}

sf::RectangleShape Racket::getRacketObject() {
    return racketObject;
}

sf::FloatRect Racket::getRacketFloatRect() {
    return racketObject.getGlobalBounds();
}

void Racket::down(){
    racketPosition.y += speed;
};

void Racket::up(){
    racketPosition.y -= speed;
};

void Racket::update(){
    racketObject.setPosition(racketPosition);
}

//ComRacket///////////////////////////////

comRacket::comRacket(double x, double y){
    
};

void comRacket::comUp(){
    
};

void comRacket::comDown(){
    
};

//Ball////////////////////////////////////

Ball::Ball(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
 
    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setPosition(position);
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
 
void Ball::reboundSides()
{
    yVelocity = -yVelocity;
}
 
void Ball::reboundBat()
{
    position.x -= (xVelocity * 30);
    xVelocity = -xVelocity;
    
    if (xVelocity > 0){
        xVelocity = xVelocity + velocityMod;
        yVelocity = yVelocity + velocityMod;
    }else{
        xVelocity = xVelocity + -velocityMod;
        yVelocity = yVelocity + -velocityMod;
    }
}

void Ball::hitRight()
{
    position.x = width/2;
    position.y = std::rand() % height + 1;
    xVelocity = 0.2f;
    yVelocity = 0.2f;
}

void Ball::hitLeft()
{
    position.x = width/2;
    position.y = height/2;
    xVelocity = 0.2f;
    yVelocity = 0.2f;
}
 
void Ball::update()
{
    // Update the ball position variables
    position.y += yVelocity;
    position.x += xVelocity;
 
    // Move the ball and the bat
    ballShape.setPosition(position);
}
