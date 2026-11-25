#pragma once 
#include <SFML/Graphics.hpp>

extern int score;
bool inarena(float x, float y, float r);
void startarena();
void movezombies(float dt);
void drawarena(sf::RenderWindow &window);
void drawzombies(sf::RenderWindow &window);