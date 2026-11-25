#include <cmath>
#include <cstdlib>
#include "arena.h"
#include "player.h"
#include "sound.h"
using namespace sf;

int score = 0;
//max 15 zombies at a time
float zombiex[15], zombiey[15];
int zombiehp[15], zombiemax[15];
bool zombiealive[15], zombietank[15];
float spawntime = 2;
float tanktime = 6;
int killed = 0;

// 3 crates
float crateleft[3] = {250, 900, 300};
float cratetop[3] = {160, 470, 480};
float cratewidth[3] = {140, 140, 60};
float crateheight[3] = {60, 60, 140};

float dist(float x1, float y1, float x2, float y2){
    float a = x2 - x1;
    float b = y2 - y1;
    return sqrt(a * a + b * b);
}

bool incrate(float x, float y){
    for(int i = 0; i < 3; i++){
        if(x > crateleft[i] && x < crateleft[i] + cratewidth[i]){
            if(y > cratetop[i] && y < cratetop[i] + crateheight[i])
               return true;
        }
    }
    return false;
}

bool inarena(float x, float y, float r){
    if(x - r < 20 || x + r > 1260 || y - r < 20 || y + r > 700)
       return false;
    if(incrate(x - r, y - r) || incrate(x + r, y - r))
       return false;
    if(incrate(x - r, y + r) || incrate(x + r, y + r))
       return false;
    return true;
}

//new game start
void startarena(){
    score = 0;
    killed = 0;
    spawntime = 2;
    tanktime = 6;
    for(int i = 0; i < 15; i++)
        zombiealive[i] = false;
}

void addzombie(bool tank){
    for(int i = 0; i < 15; i++){
        if(zombiealive[i] == false){
            float x, y;
            do{
                if(rand() % 2 == 0){
                    x = 60 + rand() % 1160;
                    if(rand() % 2 == 0)
                       y = 60;
                    else
                       y = 660;
                } else{
                    y = 60 + rand() % 600;
                    if(rand() % 2 == 0)
                       x = 60;
                    else
                       x = 1220;
                }
            } while(dist(x, y, px, py) < 300);
            zombiex[i] = x;
            zombiey[i] = y;
            zombietank[i] = tank;
            if(tank == true)
               zombiehp[i] = 6;
            else
               zombiehp[i] = 3;
            zombiemax[i] = zombiehp[i];
            zombiealive[i] = true;
            return;
        }
    }
}

void movezombies(float dt){
    int kills = killed;
    float speed = 80 + kills * 2;
    if(speed > 150)
       speed = 150;
    float gap = 2 - kills * 0.04;  //time between 2 zombies
    if(gap < 0.8)
       gap = 0.8;

    spawntime = spawntime - dt;
    if(spawntime <= 0){
        addzombie(false);
        spawntime = gap;
    }
    if(killed >= 8){
        tanktime = tanktime - dt;
        if(tanktime <= 0){
            addzombie(true);
            tanktime = 6;
        }
    }

    for(int i = 0; i < 15; i++){
        if(zombiealive[i] == false)
           continue;
        float r = 16;
        float s = speed;
        if(zombietank[i] == true){
            r = 24;
            s = speed * 0.7;
        }
        float dx = px - zombiex[i];
        float dy = py - zombiey[i];
        float length = sqrt(dx * dx + dy * dy) + 0.001;
        float newx = zombiex[i] + dx / length * speed * dt;
        float newy = zombiey[i] + dy / length * speed * dt;

        if(inarena(newx, zombiey[i], r))
           zombiex[i] = newx;
        if(inarena(zombiex[i], newy, r))
           zombiey[i] = newy;

        for(int j = 0; j < 50; j++){
            if(bon[j] && dist(bx[j], by[j], zombiex[i], zombiey[i]) < r + 4){
                bon[j] = false;
                zombiehp[i] = zombiehp[i] - 1;
                if(zombiehp[i] <= 0){
                    zombiealive[i] = false;
                    killed = killed + 1;
                    if(zombietank[i] == true){
                        score = score + 300;
                        reserve = reserve + 12;
                    }
                    else{
                        score = score + 100;
                        reserve = reserve + 8;
                    }
                    playsound(2);
                    break;
                }
            }
        }
        if(zombiealive[i] && length < r + 16)
           hurtplayer(10);       
    }
}

void drawarena(RenderWindow &window){
    window.clear(Color(60, 55, 58));  //grey wall

    RectangleShape floor(Vector2f(1240, 680));
    floor.setPosition(20,20);
    floor.setFillColor(Color(38, 30, 32));
    window.draw(floor);

    RectangleShape line(Vector2f(2, 680));
    line.setFillColor(Color(52, 42, 44));
    for(int x = 100; x < 1260; x = x + 80){
        line.setPosition(x, 20);
        window.draw(line);
    }
    line.setSize(Vector2f(1240, 2));
    for(int y = 100; y < 700; y = y + 80){
        line.setPosition(20, y);
        window. draw(line);
    }

    RectangleShape crate;
    crate.setFillColor(Color(100, 62, 30));
    crate.setOutlineThickness(-7);
    crate.setOutlineColor(Color(140, 95, 48));
    for(int i = 0; i < 3; i++){
        crate.setSize(Vector2f(cratewidth[i], crateheight[i]));
        crate.setPosition(crateleft[i], cratetop[i]);
        window.draw(crate);
    }
}

void drawzombies(RenderWindow &window){
    CircleShape body(16);
    body.setOutlineThickness(2);
    body.setOutlineColor(Color::Black);

    CircleShape eye(3);

    RectangleShape healthback(Vector2f(32, 5));
    healthback.setFillColor(Color(80, 0, 0));
    RectangleShape healthbar(Vector2f(32, 5));
    healthbar.setFillColor(Color(0, 200, 0));

    for (int i = 0; i < 15; i++) {
        if (zombiealive[i] == false)
            continue;

        float r = 16;
        if(zombietank[i] == true){
            r = 24;
            body.setFillColor(Color(190, 35, 35));
            eye.setFillColor(Color(255, 220, 0));
        } 
        else{
            body.setFillColor(Color(110, 140, 70));
            eye.setFillColor(Color(255, 40, 40));
        }
        body.setRadius(r);
        body.setPosition(zombiex[i] - r, zombiey[i] - r);
        window.draw(body);
        float dx = px - zombiex[i];
        float dy = py - zombiey[i];
        float length = sqrt(dx * dx + dy * dy) + 0.001;
        float eyex = zombiex[i] + dx / length * (r * 0.55);
        float eyey = zombiey[i] + dy / length * (r * 0.55);
        eye.setPosition(eyex - r / 2 - 3, eyey - 3);
        window.draw(eye);
        eye.setPosition(eyex + r / 2 - 3, eyey - 3);
        window.draw(eye);   
        
        //zombie health bar
        healthback.setSize(Vector2f(r * 2, 5));
        healthback.setPosition(zombiex[i] - r, zombiey[i] - r -12);
        healthbar.setPosition(zombiex[i] - r, zombiey[i] - r - 12);
        healthbar.setSize(Vector2f(r * 2 * zombiehp[i] / zombiemax[i], 5));
        window.draw(healthback);
        window.draw(healthbar);
    }
}