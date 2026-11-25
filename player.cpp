#include <cmath>
#include "player.h"
#include "arena.h"
#include "menu.h"
#include "sound.h"
using namespace sf;
using namespace std;

float px,py;  //player position
float angle=0; //direction of gun
int health=100;
int ammo=30;
int reserve=90;
bool reloading=false;
float reloadtime=0;
float shoottime=0;
float hurttime=0;

float bx[50],by[50],bdx[50],bdy[50];
bool bon[50];

//new game start
void startplayer(){
    px=640;
    py=360;
    health=100;
    ammo=30;
    reserve=90;
    reloading=false;
    shoottime=0;
    hurttime=0;
    for(int i=0;i<50;i++)
      bon[i]=false;
}
 
void hurtplayer(int damage){
    if(hurttime<=0){
        health=health-damage;
        hurttime=0.7;
        playsound(3);
    }
}

void moveplayer(float dt){
    float newx=px;
    float newy=py;
    if(Keyboard::isKeyPressed(Keyboard::W))
    newy=newy-220*dt;
    if(Keyboard::isKeyPressed(Keyboard::S))
    newy=newy+220*dt;
    if(Keyboard::isKeyPressed(Keyboard::A))
    newx=newx-220*dt;
    if(Keyboard::isKeyPressed(Keyboard::D))
    newx=newx+220*dt;

    if(inarena(newx,py,16))
    px=newx;
    if(inarena(px,newy,16))
    py=newy;
}

void startreload(){
    if(reloading==false && ammo<30 && reserve>0){
        reloading=true;
        reloadtime=1.3;
        playsound(1);
    }
}

void reloadgun(float dt){
    if(Keyboard::isKeyPressed(Keyboard::R))
    startreload();

    if(reloading){
        reloadtime=reloadtime-dt;
        if(reloadtime<=0){
            int needed=30-ammo;
            if(needed>reserve)
            needed=reserve;
            ammo=ammo+needed;
            reserve=reserve-needed;
            reloading=false;
        }
    }
}

void shoot(){
    if(Mouse::isButtonPressed(Mouse::Left)==false || shoottime>0 || reloading)
    return;

    if(ammo==0){
        startreload();
        return;
    }

    for(int i=0;i<50;i++){
        if(bon[i]==false){
            bon[i]=true;
            bdx[i]=cos(angle);
            bdy[i]=sin(angle);
            bx[i]=px+bdx[i]*28;
            by[i]=py+bdy[i]*28;
            ammo=ammo-1;
            shoottime=0.2;
            playsound(0);
            return;
        }
    }
}

void updateplayer(RenderWindow &window,float dt){
    moveplayer(dt);
    Vector2i mouse=Mouse::getPosition(window);
    angle=atan2(mouse.y-py,mouse.x-px);
    if(shoottime>0)
    shoottime=shoottime-dt;
    if(hurttime>0)
    hurttime=hurttime-dt;
    reloadgun(dt);
    shoot();
}

void movebullets(float dt){
    for(int i=0;i<50;i++){
        if(bon[i]){
            bx[i]=bx[i]+bdx[i]*700*dt;
            by[i]=by[i]+bdy[i]*700*dt;
            if(!inarena(bx[i],by[i],0))
            bon[i]=false;
        }
    }
}

void drawplayer(RenderWindow &window){
    RectangleShape gun(Vector2f(34,8));
    gun.setOrigin(0,4);
    gun.setPosition(px,py);
    gun.setRotation(angle*180/3.14159);
    gun.setFillColor(Color(220,220,220));
    gun.setOutlineThickness(1);
    gun.setOutlineColor(Color::Black);
    window.draw(gun);

    CircleShape body(16);
    body.setPosition(px-16,py-16);
    body.setFillColor(Color(60,140,255));
    body.setOutlineThickness(3);
    body.setOutlineColor(Color::White);
    window.draw(body);

    CircleShape helmet(7);
    helmet.setPosition(px-7, py-7);
    helmet.setFillColor(Color(190, 225, 255));
    window.draw(helmet);

    Vector2i mouse=Mouse::getPosition(window);
    RectangleShape lineh(Vector2f(20,2));
    RectangleShape linev(Vector2f(2,20));
    lineh.setPosition(mouse.x-10,mouse.y-1);
    linev.setPosition(mouse.x-1,mouse.y-10);
    window.draw(lineh);
    window.draw(linev);
}

void drawbullets(RenderWindow &window){
    CircleShape bullet(4);
    bullet.setFillColor(Color(255,230,100));
    for(int i=0;i<50;i++){
        if(bon[i]){
            bullet.setPosition(bx[i]-4,by[i]-4);
            window.draw(bullet);
        }
    }
}

void drawhud(RenderWindow &window,int score){
    RectangleShape box(Vector2f(290,75));
    box.setFillColor(Color(0,0,0,160));
    box.setOutlineThickness(2);
    box.setOutlineColor(Color(150,40,40));

    box.setPosition(40,40);
    window.draw(box);
    writetext(window,"HEALTH",18,55,46,Color::White);
    RectangleShape healthback(Vector2f(250,22));
    healthback.setPosition(55,76);
    healthback.setFillColor(Color(80,0,0));
    window.draw(healthback);
    RectangleShape healthbar(Vector2f(health*2.5,22));
    healthbar.setPosition(55,76);
    if(health<=30)
    healthbar.setFillColor(Color(230,60,30));
    else
    healthbar.setFillColor(Color(0,200,0));
    window.draw(healthbar);
    writetext(window, to_string(health) + " / 100",16,65,78,Color::White);

    box.setPosition(950,40);
    box.setSize(Vector2f(290,60));
    window.draw(box);
    writetext(window,"SCORE: " + to_string(score),30,970,50,Color::White);

    box.setPosition(950,580);
    box.setSize(Vector2f(290,100));
    window.draw(box);
    writetext(window,"AMMO " + to_string(ammo) + " / 30",24,965,586,Color::White);
    RectangleShape icon(Vector2f(5,16));
    for(int i=0;i<30;i++){
        icon.setPosition(965+i*8,624);
        if(i<ammo)
        icon.setFillColor(Color(255,220,80));
        else
        icon.setFillColor(Color(70,60,60));
        window.draw(icon);
    }
    writetext(window,"RESERVE: "+ to_string(reserve),20,965,648,Color(220,200,80));

    if(reloading)
    centertext(window,"RELOADING...",28,640,610,Color(255,170,0));
    else if(ammo==0 && reserve==0)
    centertext(window,"NO AMMO",28,640,610,Color(255,60,60));

    if(hurttime>0.4){
        RectangleShape flash(Vector2f(1280,720));
        flash.setFillColor(Color(255,0,0,70));
        window.draw(flash);
    }
}