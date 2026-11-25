#pragma once
#include<SFML/Graphics.hpp>

bool loadfont();
void writetext(sf::RenderWindow &window,std::string words,int size,float x,float y,sf::Color color);
void centertext(sf::RenderWindow &window,std::string words,int size,float x,float y, sf::Color color);
bool overbutton(int x,int y,int mx,int my);
void drawmenu(sf::RenderWindow &window);
void drawgameover(sf::RenderWindow &window,int score);
