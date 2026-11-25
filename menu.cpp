//main menu + gameover screen
#include<cmath>
#include<iostream>
#include "menu.h"
#include "highscore.h"
using namespace sf;
using namespace std;

Font gamefont;
Texture zombietex;
Sprite zombiepic;
Clock menutime;
bool picloaded=false;

bool loadfont(){
    picloaded=zombietex.loadFromFile("assets/images/zombie.png");
    if(picloaded==true)
    zombiepic.setTexture(zombietex);
    else
    cout<<"zombie.png missing,menu will have no picture"<<endl;

    if(gamefont.loadFromFile("assets/fonts/font.ttf"))
        return true;
    if(gamefont.loadFromFile("C:/Windows/Fonts/arial.ttf"))
       return true;
    return false;
}

void writetext(RenderWindow &window,string words,int size,float x,float y,Color color){
    Text t(words,gamefont,size);
    t.setFillColor(color);
    t.setPosition(x,y);
    window.draw(t);
}

void centertext(RenderWindow &window, string words,int size,float x,float y,Color color){
    Text t(words,gamefont,size);
    t.setFillColor(color);
    float w= t.getLocalBounds().width;
    t.setPosition(x-w/2, y);
    window.draw(t);
}

bool overbutton(int x,int y,int mx,int my){
    if(mx>x && mx<x+300 && my>y-30 && my<y+30)
    return true;
return false;    
}

void drawbutton(RenderWindow &window,string words,int x,int y){
    Vector2i mouse=Mouse::getPosition(window);
    bool hover=overbutton(x,y,mouse.x,mouse.y);

    RectangleShape bar(Vector2f(300,60));
    bar.setPosition(x,y-30);
    if(hover==true)
      bar.setFillColor(Color(90,20,25));
    else
      bar.setFillColor(Color(35,12,15));
    window.draw(bar);
    
    RectangleShape stripe(Vector2f(10,60));
    stripe.setPosition(x,y-30);
    stripe.setFillColor(Color(200,30,30));
    if(hover==true)
        stripe.setSize(Vector2f(22,60));
    window.draw(stripe);

    if(hover==true)
        writetext(window,words,28,x+40,y-21,Color::White);
    else
        writetext(window,words,28,x+40,y-21,Color(210,70,70)); 
}

void drawdrips(RenderWindow &window){
    float len[22] = {45, 100, 28, 82, 96, 38, 66, 24, 95, 52, 110, 33, 74, 112, 42, 88, 30, 105, 58, 36, 92, 70};

    RectangleShape drip;
    drip.setFillColor(Color(150, 15, 15));
    CircleShape drop(10);  
    drop.setFillColor(Color(150, 15, 15));

    for(int i=0;i<22;i++){
        float x=15+i*60;
        drip.setSize(Vector2f(20,len[i]));
        drip.setPosition(x,0);
        drop.setPosition(x,len[i]-6);
        window.draw(drip);
        window.draw(drop);
    }
}

void drawmenu(RenderWindow &window){
    window.clear(Color(25,6,9));
    drawdrips(window);

    if(picloaded==true){
        float t=menutime.getElapsedTime().asSeconds();
        float movex=sin(t*1.3)*20;
        float movey=sin(t*1.7)*13;
        zombiepic.setPosition(650+movex,140+movey);
        window.draw(zombiepic);
    }
    writetext(window,"ZOMBIE",80,90,110,Color(210,35,35));
    writetext(window,"SURVIVAL",80,90,200,Color(235,235,235));
    writetext(window,"ARENA",80,90,290,Color(210,35,35));

    drawbutton(window,"PLAY GAME",90,470);
    drawbutton(window,"EXIT",90,560);
}

void drawgameover(RenderWindow &window,int score){
    window.clear(Color(25,6,9));
    drawdrips(window);
    centertext(window,"GAME OVER",80,640,120,Color(210,35,35));

    RectangleShape box(Vector2f(400,170));
    box.setPosition(440,250);
    box.setFillColor(Color(35,12,15));
    box.setOutlineThickness(3);
    box.setOutlineColor(Color(150,30,30));
    window.draw(box);
    
    if(newhighscore == true)
       centertext(window, "NEW HIGH SCORE!", 26, 640,265,Color(255, 200, 0));
    else
       centertext(window, "YOUR SCORE", 26, 640,265,Color(200, 150, 150));
    centertext(window,to_string(score),80,640,305,Color::White);
    drawbutton(window,"PLAY AGAIN",490,490);
    drawbutton(window,"MAIN MENU",490,570);
}