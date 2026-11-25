#pragma once
#include<SFML/Graphics.hpp>

extern float px,py;
extern int reserve;
extern int health;
extern float bx[50],by[50];
extern bool bon[50];

void startplayer();
void hurtplayer(int damage);
void updateplayer(sf::RenderWindow &window,float dt);
void movebullets(float dt);
void drawplayer(sf::RenderWindow &window);
void drawbullets(sf::RenderWindow &window);
void drawhud(sf::RenderWindow &window,int score);