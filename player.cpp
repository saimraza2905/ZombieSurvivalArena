#include <cmath>
#include "player.h"
#include "arena.h"
using namespace sf;
float px, py;
float angle = 0;
float shoottimer = 0;
float bx[50], by[50], bdx[50], bdy[50];
bool bon[50];

void startplayer() {
    px = 640;
    py = 360;
    for (int i = 0; i < 50; i++)
        bon[i] = false;
}

void moveplayer(RenderWindow &window, float dt) {
    // new position = old position + speed * dt, so speed is same on every pc
    float newx = px, newy = py;
    if (Keyboard::isKeyPressed(Keyboard::W)) newy = newy - 220 * dt;
    if (Keyboard::isKeyPressed(Keyboard::S)) newy = newy + 220 * dt;
    if (Keyboard::isKeyPressed(Keyboard::A)) newx = newx - 220 * dt;
    if (Keyboard::isKeyPressed(Keyboard::D)) newx = newx + 220 * dt;
    if (inarena(newx, py, 16)) px = newx;
    if (inarena(px, newy, 16)) py = newy;

    Vector2i mouse = Mouse::getPosition(window);
    angle = atan2(mouse.y - py, mouse.x - px);

    // bullets are reused, so we look for one that is not in use
    if (shoottimer > 0) shoottimer = shoottimer - dt;
    if (Mouse::isButtonPressed(Mouse::Left) && shoottimer <= 0) {
        for (int i = 0; i < 50; i++) {
            if (bon[i] == false) {
                bon[i] = true;
                bdx[i] = cos(angle);
                bdy[i] = sin(angle);
                bx[i] = px + bdx[i] * 28;
                by[i] = py + bdy[i] * 28;
                shoottimer = 0.25;
                break;
            }
        }
    }
}

void movebullets(float dt) {
    for (int i = 0; i < 50; i++) {
        if (bon[i]) {
            bx[i] = bx[i] + bdx[i] * 700 * dt;
            by[i] = by[i] + bdy[i] * 700 * dt;
            if (!inarena(bx[i], by[i], 0))
                bon[i] = false;
        }
    }
}

void drawplayer(RenderWindow &window) {
    RectangleShape gun(Vector2f(34, 8));
    gun.setOrigin(0, 4);
    gun.setPosition(px, py);
    gun.setRotation(angle * 180 / 3.14159);
    gun.setFillColor(Color(30, 30, 30));
    window.draw(gun);
    CircleShape body(16);
    body.setPosition(px - 16, py - 16);
    body.setFillColor(Color(60, 140, 255));
    window.draw(body);
}

void drawbullets(RenderWindow &window) {
    CircleShape bullet(4);
    bullet.setFillColor(Color(255, 230, 100));
    for (int i = 0; i < 50; i++) {
        if (bon[i]) {
            bullet.setPosition(bx[i] - 4, by[i] - 4);
            window.draw(bullet);
        }
    }
}
