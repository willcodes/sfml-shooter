#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Player.hpp"

using namespace sf;

struct Bullet {
    int x, y, dx;
};

struct Asteroid {
    int x,y,dx;
};

int main() {

    int gWindow_w = 1440; int gWindow_h = 900;
    VideoMode vm(gWindow_w, gWindow_h);
    RenderWindow window(vm,"Space Shooter");
    window.setFramerateLimit(60);

    Texture t2, t3, t4, bg1, bg2, bg3;
    t2.loadFromFile("assets/bullet.png");
    t3.loadFromFile("assets/player.png");
    t4.loadFromFile("assets/asteroid_1.png");
    bg1.loadFromFile("assets/starlayer1.png");
    bg2.loadFromFile("assets/starlayer2.png");
    bg3.loadFromFile("assets/starlayer3.png");

    bg1.setRepeated(true);
    bg2.setRepeated(true);
    bg3.setRepeated(true);
    
    Sprite sBullet(t2), sAsteroid(t4), sBg1(bg1), sBg1_copy(bg1), sBg2(bg2), sBg2_copy(bg2), sBg3(bg3);
    Player player(t3, 0, gWindow_h / 2, 5);
    FloatRect sBulletBounds = sBullet.getLocalBounds();
    FloatRect sAsteroidBounds = sAsteroid.getLocalBounds();

    int player_bullet_speed = 10;
    float player_bullet_timer = 0.0f, delay = 0.2f, time = 0.0f, asteroid_timer = 0.0f, asteroid_delay = 1.0f;
    int sBg1_x = 0, sBg2_x = 0, sBg3_x = 0;
    float sBg1_dx = 0.85f, sBg2_dx = 0.99f, sBg3_dx = 1.6f;
    Clock clock;
    std::srand ((unsigned)std::time(NULL));
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

    while (window.isOpen()) {
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        player_bullet_timer += time;
        asteroid_timer += time;

        Event event;
        while(window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if(Keyboard::isKeyPressed(Keyboard::Right)) player.x += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Left))  player.x -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Up))    player.y -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Down))  player.y += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        player.handleSprite();

        if(Keyboard::isKeyPressed(Keyboard::Space) && delay < player_bullet_timer) {
            int x = player.x + player.w / 2, y = (player.y + (player.h / 2)) + sBulletBounds.height / 2.0;
            Bullet bullet;
            bullet.x = x; bullet.y = y, bullet.dx = player_bullet_speed;
            std::cout << "PLAYER Y: " << player.y << "\t" << "BULLET Y: " << bullet.y << std::endl;
            bullets.push_back(bullet);
            player_bullet_timer = 0;
            std::cout << "BULLET CREATED Y POSITION: " << bullets[bullets.size() - 1].y << "\tBULLETS SIZE: " << bullets.size() << std::endl;
        }
        if(std::rand() % 10 + 1 > 3 && asteroid_delay < asteroid_timer) {
            // std::srand((int)std::time(0) * gWindow_w);
            int x = std::rand() % gWindow_w, y = 0;
            Asteroid asteroid;
            asteroid.x = x; asteroid.y = y; asteroid.dx = 1;
            asteroids.push_back(asteroid);
            asteroid_timer = 0;
        }
        
        window.clear();

        sBg1_x -= sBg1_dx * 2.5;
        sBg2_x -= sBg2_dx * 2.6;
        
        if(sBg1_x < -sBg1.getLocalBounds().width) sBg1_x = 0;
        if(sBg2_x < -sBg2.getLocalBounds().width) sBg2_x = 0;

        sBg1.setPosition(sBg1_x, 0);
        sBg1_copy.setPosition(sBg1_x + sBg1.getLocalBounds().width, 0);
        sBg2_copy.setPosition(sBg2_x + sBg2.getLocalBounds().width, 0);
        sBg2.setPosition(sBg2_x, 0);

        window.draw(sBg1);
        window.draw(sBg1_copy);
        window.draw(sBg2);
        window.draw(sBg2_copy);
        window.draw(sBg3);

        player.sprite.setPosition(player.x, player.y);
        window.draw(player.sprite);

        for(unsigned i = 0;  i < bullets.size(); i++) {
            for(unsigned j = 0; j < asteroids.size(); j++ ) {
                if(bullets[i].x > asteroids[j].x && bullets[i].x < asteroids[j].x + sAsteroidBounds.width 
                    && bullets[i].y > asteroids[j].y && bullets[i].y < asteroids[j].y + sAsteroidBounds.height) {
                    std::cout << "HIT!" << " ASTEROIDS: "<< asteroids.size() << std::endl;
                    asteroids.erase(asteroids.begin() + j);
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
            
        for(unsigned i = 0;  i < bullets.size(); i++) {
            sBullet.setPosition(bullets[i].x, bullets[i].y - bullets[i].dx);
            // std::cout << "BULLET POS Y: " << bullets[i].y << std::endl;
            if(bullets[i].x > gWindow_w) {
                bullets.erase(bullets.begin()+i);
                break;
            } 
            else { 
                bullets[i].x += bullets[i].dx; 
            }
            window.draw(sBullet);
        }

        for(unsigned i = 0;  i < asteroids.size(); i++) {
            sAsteroid.setPosition(asteroids[i].x, asteroids[i].y);
            // std::cout << "BULLET POS Y: " << asteroids[i].y << std::endl;
            if(asteroids[i].y > 800) {
                asteroids.erase(asteroids.begin()+i);
                break;
            } 
            else { 
                asteroids[i].y += asteroids[i].dx; 
            }
                if(asteroids[i].x > player.x && asteroids[i].x < player.x + player.w
                    && asteroids[i].y > player.y && asteroids[i].y < player.y + player.h) {
                    std::cout << "PLAYER HIT!" << std::endl;
                }
            window.draw(sAsteroid);
        }

        window.display();
    }
    return 0;
}
