#include <cmath>
#include <cstdlib>
#include "arena.h"
#include "player.h"
using namespace sf;
float zx[30], zy[30];
bool zon[30];
float spawntimer = 1;

float dist(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// walls are 40 px thick in a 1280 x 720 window, so inside is 40 to 1240 and 40 to 680
bool inarena(float x, float y, float r) {
    return x - r > 40 && x + r < 1240 && y - r > 40 && y + r < 680;
}

void clearzombies() {
    for (int i = 0; i < 30; i++)
        zon[i] = false;
}

// pick a random spot on an edge, try again if it is too close to the player
void addzombie() {
    for (int i = 0; i < 30; i++) {
        if (zon[i] == false) {
            float x, y;
            do {
                if (rand() % 2 == 0) {
                    x = 60 + rand() % 1160;
                    if (rand() % 2 == 0) y = 60; else y = 660;
                } else {
                    y = 60 + rand() % 600;
                    if (rand() % 2 == 0) x = 60; else x = 1220;
                }
            } while (dist(x, y, px, py) < 300);
            zx[i] = x;
            zy[i] = y;
            zon[i] = true;
            return;
        }
    }
}

bool movezombies(float dt) {
    bool touched = false;
    spawntimer = spawntimer - dt;
    if (spawntimer <= 0) {
        addzombie();
        spawntimer = 1.5;
    }
    for (int i = 0; i < 30; i++) {
        if (zon[i] == false) continue;

        // dividing by length keeps the zombie speed the same in every direction
        float dx = px - zx[i], dy = py - zy[i];
        float length = sqrt(dx * dx + dy * dy) + 0.001;
        zx[i] = zx[i] + dx / length * 90 * dt;
        zy[i] = zy[i] + dy / length * 90 * dt;

        for (int j = 0; j < 50; j++) {
            if (bon[j] && dist(bx[j], by[j], zx[i], zy[i]) < 20) {
                bon[j] = false;
                zon[i] = false;
            }
        }
        if (zon[i] && length < 32) touched = true;
    }
    return touched;
}

void drawarena(RenderWindow &window) {
    window.clear(Color(70, 70, 75));
    RectangleShape floor(Vector2f(1200, 640));
    floor.setPosition(40, 40);
    floor.setFillColor(Color(35, 35, 39));
    window.draw(floor);
}

void drawzombies(RenderWindow &window) {
    CircleShape zombie(16);
    zombie.setFillColor(Color(110, 140, 70));
    for (int i = 0; i < 30; i++) {
        if (zon[i]) {
            zombie.setPosition(zx[i] - 16, zy[i] - 16);
            window.draw(zombie);
        }
    }
}
