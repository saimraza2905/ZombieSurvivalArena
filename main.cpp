#include <iostream>
#include <cstdlib>
#include <ctime>
#include "menu.h"
#include "player.h"
#include "arena.h"
#include "sound.h"
#include "highscore.h"
using namespace sf;
using namespace std;

int main (){
    srand(time(NULL));
    RenderWindow window(VideoMode(1280, 720), "Zombie Survival Arena", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    if(!loadfont()){
        cout << "Font not found! Put a font at assets/fonts/font.ttf" << endl;
        return 1;
    }
    if(!loadsounds())
       cout << "Sound files not found, the game will be silent." << endl;
    
    loadscores();
    int state = 0; //0= main menu, 1 = playing, 2 =game over  
    Clock gameclock;
    
    while(window.isOpen()){
        float dt = gameclock.restart().asSeconds();

        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
               window.close();
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape && state == 1)
               state = 0;
            if(e.type == Event::MouseButtonPressed){
                int mx = e.mouseButton.x;
                int my = e.mouseButton.y;

                if(state == 0){
                    if(overbutton(90, 470, mx, my)){
                        startplayer();
                        startarena();
                        state = 1;
                    }
                    if(overbutton(90, 560, mx, my))
                       window.close();
                }
                if(state == 2){
                    if(overbutton(490, 490, mx, my)){
                       startplayer();
                       startarena();
                       state = 1;
                    }
                    if(overbutton(490, 570, mx, my))
                       state = 0;
                }
            }
        }
        if(state == 1){
            updateplayer(window, dt);
            movebullets(dt);
            movezombies(dt);
            if(health <= 0){
                playsound(4);
                savescore(score);
                state = 2;
            }
        }
        updatemusic(state);

        window.setMouseCursorVisible(state != 1);
        if(state == 0){
            drawmenu(window);
        }
        else if(state == 1){
            drawarena(window);
            drawzombies(window);
            drawbullets(window);
            drawplayer(window);
            drawhud(window, score);
        }
        else{
            drawgameover(window, score);
        }
        window.display();
    }
    return 0;
}