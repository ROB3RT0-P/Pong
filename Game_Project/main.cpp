//Robert Parry - Pong - 26/11/22-//22
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ResourcePath.hpp"

int width = 1000, height = 1000;//Window width and height;
int score = 0;
int maxY = height - 10;
int minY = (height - height) + 10;

class racket {
public:
    racket(double x, double y);
    void up();
    void down();
private:
    sf::Vector2f racketPos;
    double speed = 1;
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

class ball {
public:
    ball(double x, double y);
private:
    sf::Vector2f ballPos;
    double speed = 1;
};

int main(int, char const**)
{
    racket Racket(width-20, height/2);
    ball Ball(width/2, height/2+50);
    comRacket ComRacket(height/2, 10);
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Game Window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "background.jpeg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "gameFont.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Pong", font, 50);
    text.setFillColor(sf::Color::White);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    //music.play();

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
            Racket.up();
        }
        
        if(((event.type == event.KeyPressed) && event.key.code == sf::Keyboard::Down)) {
            std::cout << "Down Key Pressed" << std::endl;
            Racket.down();
        }
        
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    
  
    return EXIT_SUCCESS;
}

racket::racket(double x, double y){
    
};

//Functions for functionality
void racket::down(){
    
};

void racket::up(){
    
};

comRacket::comRacket(double x, double y){
    
};

void comRacket::comUp(){
    
};

void comRacket::comDown(){
    
};

ball::ball(double x, double y){
    
};
