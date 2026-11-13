#pragma once
#include <SFML/Graphics.hpp>
bool inarena(float x, float y, float r);   // true if a circle is inside the walls
void clearzombies();
bool movezombies(float dt);                // true if a zombie touches the player
void drawarena(sf::RenderWindow &window);
void drawzombies(sf::RenderWindow &window);
