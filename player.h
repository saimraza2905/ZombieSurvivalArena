#pragma once
#include <SFML/Graphics.hpp>
// extern so arena.cpp can use these same variables
extern float px, py;
extern float bx[50], by[50];
extern bool bon[50];

void startplayer();
void moveplayer(sf::RenderWindow &window, float dt);
void movebullets(float dt);
void drawplayer(sf::RenderWindow &window);
void drawbullets(sf::RenderWindow &window);
