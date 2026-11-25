#include <SFML/Audio.hpp>
#include "sound.h"
using namespace sf;
using namespace std;

string soundfiles[5] = {"assets/sounds/shoot.wav", "assets/sounds/reload.wav", "assets/sounds/zombie.wav","assets/sounds/hurt.wav", "assets/sounds/gameover.wav"};
SoundBuffer soundbuffer[5];
Sound sound[5];
Music menumusic;
bool soundok = false;

bool loadsounds(){
    for(int i = 0; i < 5; i++){
        if(!soundbuffer[i].loadFromFile(soundfiles[i]))
            return false;
        sound[i].setBuffer(soundbuffer[i]);
    }
    sound[0].setVolume(70);
    if(!menumusic.openFromFile("assets/sounds/menu.wav"))
       return false;
    menumusic.setLoop(true);
    menumusic.setVolume(65);
    soundok = true;
    return true;
}
void playsound(int number){
    if(soundok == true)
       sound[number].play();
}

void updatemusic(int state){
    if(soundok == false)
       return;
    if(state == 0 && menumusic.getStatus() != Music::Playing)
       menumusic.play();
    if(state != 0 && menumusic.getStatus() == Music::Playing)
       menumusic.stop();
}