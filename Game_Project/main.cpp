//Robert Parry - Pong - 26/11/22
//Prototype working - 23/12/22
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "ResourcePath.hpp"

//TODO: frame limit, points system, scalability, change ball direction


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

class ComRacket {
public:
    ComRacket(double x, double y);
    
    void comUp();
    void comDown();
    void comUpdate();
    
    sf::RectangleShape getComRacketObject();
    sf::FloatRect getComRacketFloatRect();
    sf::Vector2f getComRacketPosition();
    
private:
    sf::Vector2f comRacketPosition;
    sf::RectangleShape comRacketObject;
    double speed = 1;
};

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
 
    float xVelocity = .2f;
    float yVelocity = .2f;
    float velocityMod = .1f;
};

int main(int, char const**)
{
    Racket racket(width-20, height/2);
    ComRacket comRacket((width - width)+20, height/2);//Maybe just use 20 for x
    Ball ball(width/2, height/2+50);
    
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
            ball.hitLeft();
            //ball.reboundBat();
        }
         
        // Reset ball after hitting right side
        if ( ball.getPosition().left > width)
        {
            ball.hitRight();
        }
        
        // Racket reflect
        if (ball.getPosition().intersects(racket.getRacketFloatRect()))
        {
            ball.reboundBat();
        }

        
        
        //Com checks
        
        //Move to intercept ball
        if (ball.getPosition().left < 400){
            if(ball.getPosition().top < comRacket.getComRacketPosition().y){
                comRacket.comUp();
            }else if((ball.getPosition().top > comRacket.getComRacketPosition().y)){
                comRacket.comDown();
            }
        }
        
        // comRacket reflect
        if (ball.getPosition().intersects(comRacket.getComRacketFloatRect()))
        {
            ball.reboundBat();
        }
        
        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
        
        racket.update();
        comRacket.comUpdate();
        ball.update();
        
        window.clear(sf::Color(0, 0, 0, 255));
        
        window.draw(racket.getRacketObject());
        window.draw(comRacket.getComRacketObject());
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

ComRacket::ComRacket(double x, double y){
       comRacketPosition.x = x;
       comRacketPosition.y = y;
       comRacketObject.setSize(sf::Vector2f(10, 150));
       comRacketObject.setPosition(comRacketPosition);
};

sf::Vector2f ComRacket::getComRacketPosition() {
    return comRacketPosition;
}

sf::RectangleShape ComRacket::getComRacketObject() {
    return comRacketObject;
}

sf::FloatRect ComRacket::getComRacketFloatRect() {
    return comRacketObject.getGlobalBounds();
}

void ComRacket::comDown(){
    comRacketPosition.y += speed;
};

void ComRacket::comUp(){
    comRacketPosition.y -= speed;
};

void ComRacket::comUpdate(){
    comRacketObject.setPosition(comRacketPosition);
}

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
    position.y = std::rand() % height + 1;
    xVelocity = -0.2f;
    yVelocity = -0.2f;
}
 
void Ball::update()
{
    // Update the ball position variables
    position.y += yVelocity;
    position.x += xVelocity;
 
    // Move the ball and the bat
    ballShape.setPosition(position);
}
