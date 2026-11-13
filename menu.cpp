#include "menu.h"
using namespace sf;
using namespace std;
Font font;
string names[2] = {"PLAY", "EXIT"};
int buttony[2] = {340, 440};

bool loadfont() {
    return font.loadFromFile("assets/fonts/font.ttf") || font.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

void drawmenu(RenderWindow &window) {
    window.clear(Color(18, 18, 22));
    Text title("ZOMBIE SURVIVAL ARENA", font, 60);
    title.setPosition(640 - title.getLocalBounds().width / 2, 140);
    window.draw(title);
    for (int i = 0; i < 2; i++) {
        RectangleShape box(Vector2f(280, 60));
        box.setPosition(500, buttony[i] - 30);
        box.setFillColor(Color(170, 30, 30));
        window.draw(box);
        Text label(names[i], font, 28);
        label.setPosition(640 - label.getLocalBounds().width / 2, buttony[i] - 20);
        window.draw(label);
    }
}

// a click counts if the mouse is inside the button rectangle
int menuclick(int mx, int my) {
    for (int i = 0; i < 2; i++) {
        if (mx > 500 && mx < 780 && my > buttony[i] - 30 && my < buttony[i] + 30)
            return i + 1;
    }
    return 0;
}
