#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Player.hpp"

using namespace sf;

void update()
{
    
}

int main()
{
    
    VideoMode vm(600,800);
    RenderWindow window(vm,"Game Boilerplate");
    window.setFramerateLimit(60);
    //instantiate textures
    Texture textureBackground;
    textureBackground.loadFromFile("assets/purple.png");
    textureBackground.setRepeated(true);

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(IntRect(0, 0, 600,800));
    
    Texture textureShip;
    textureShip.loadFromFile("assets/player.png");

    Player player(textureShip);
    player.sprite.setPosition(600 / 2.0f , 700);
    

    float playerSpeed = 5;
    bool leftArrowPressed = false, rightArrowPressed = false, upArrowPressed = false, downArrowPressed = false;

    while (window.isOpen())
    {
        /* USER INPUT */
        Event event;

        while(window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case Keyboard::Escape:
                    window.close();
                    break;

                    case Keyboard::Left:
                    leftArrowPressed = true;
                    break;

                    case Keyboard::Right:
                    rightArrowPressed = true;
                    break;

                    case Keyboard::Up:
                    upArrowPressed = true;
                    break;

                    case Keyboard::Down:
                    downArrowPressed = true;
                    break;

                }
            }
            
            if(event.type == Event::KeyReleased)
            {
                switch(event.key.code)
                {
                    case Keyboard::Left:
                    leftArrowPressed = false;
                    break;

                    case Keyboard::Right:
                    rightArrowPressed = false;
                    break;

                    case Keyboard::Up:
                    upArrowPressed = false;
                    break;                    

                    case Keyboard::Down:
                    downArrowPressed = false;
                    break;
                }
            }
        }

        if(leftArrowPressed)
        {
            player.sprite.move(Vector2f(-playerSpeed, 0));
        }
        if(rightArrowPressed)
        {
            player.sprite.move(Vector2f(playerSpeed, 0));
        }
        if(upArrowPressed)
        {
            player.sprite.move(Vector2f(0, -playerSpeed));
        }
        if(downArrowPressed)
        {
            player.sprite.move(Vector2f(0, playerSpeed));
        }

        player.handleSprite();

        window.clear();

        //rendering
        window.draw(spriteBackground);
        window.draw(player.sprite);

        window.display();
    }
    return 0;
}