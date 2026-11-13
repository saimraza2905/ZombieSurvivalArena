#include <iostream>
#include <cstdlib>
#include <ctime>
#include "menu.h"
#include "player.h"
#include "arena.h"
using namespace sf;
int main() {
    srand(time(NULL));
    RenderWindow window(VideoMode(1280, 720), "Zombie Survival Arena");
    window.setFramerateLimit(60);
    if (!loadfont()) {
        std::cout << "Font not found! Put a font at assets/fonts/font.ttf" << std::endl;
        return 1;
    }
    bool inmenu = true;
    Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        // the loop does 3 things every frame: events, update, draw
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                inmenu = true;
            if (inmenu && event.type == Event::MouseButtonPressed) {
                int choice = menuclick(event.mouseButton.x, event.mouseButton.y);
                if (choice == 1) {
                    startplayer();
                    clearzombies();
                    inmenu = false;
                }
                if (choice == 2)
                    window.close();
            }
        }

        if (inmenu == false) {
            moveplayer(window, dt);
            movebullets(dt);
            if (movezombies(dt))
                inmenu = true;
        }

        if (inmenu) {
            drawmenu(window);
        } else {
            drawarena(window);
            drawzombies(window);
            drawbullets(window);
            drawplayer(window);
        }
        window.display();
    }
    return 0;
}
