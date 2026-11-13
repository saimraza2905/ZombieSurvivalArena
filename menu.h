#pragma once
#include <SFML/Graphics.hpp>
bool loadfont();
void drawmenu(sf::RenderWindow &window);
int menuclick(int mx, int my);   // 0 = nothing, 1 = play, 2 = exit
