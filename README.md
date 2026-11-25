# Zombie Survival Arena

A 2D zombie shooting game made in C++ with SFML.
This is our Programming Fundamentals semester project (Group 14).

Members: Saim Raza, Wassay Raza, Muhammad Ibrahim

## About the game

You are stuck inside an arena and zombies keep coming at you from the sides.
Shoot them before they touch you. If your health reaches 0, the game is over.
Kill as many as you can to get a high score.

## Features

- Main menu and game over screen
- Normal zombies (3 hits to kill)
- Tank zombies (bigger and red, 6 hits to kill, they come after 8 kills)
- Zombies get faster as you kill more
- Health, ammo and reload
- Sounds and menu music
- Top 3 high scores saved in a file (highscores.txt)

## Controls

- W A S D to move
- Mouse to aim
- Left click to shoot
- R to reload
- Esc to go back to the menu

## How to compile

Open a terminal in the project folder and type this (SFML is installed in C:/SFML):

```
g++ main.cpp menu.cpp player.cpp arena.cpp sound.cpp highscore.cpp -o ZombieArena.exe -I C:/SFML/include -L C:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

## How to run

Double click ZombieArena.exe.
The DLL files, the assets folder and highscores.txt must be in the same folder as the exe.

## Files

- main.cpp: window and game loop
- menu.cpp / menu.h: menu and game over screen
- player.cpp / player.h: player, bullets and HUD
- arena.cpp / arena.h: arena and zombies
- sound.cpp / sound.h: sounds and music
- highscore.cpp / highscore.h: saving the top 3 scores in a file

## Credits

- SFML library (sfml-dev.org)
- Font: DejaVu Sans
- The zombie picture was made with an AI tool
- Sound files were also generated with AI