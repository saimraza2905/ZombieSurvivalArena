# Zombie Survival Arena

This is our Programming Fundamentals project. It is a small 2D zombie shooting game made in C++ with SFML. This is the mid evaluation version.

## Group members

- Saim Raza: arena and zombies (arena.h, arena.cpp), main.cpp and this readme
- Wassay Raza: player, aiming and bullets (player.h, player.cpp)
- Muhammad Ibrahim: main menu (menu.h, menu.cpp)

## What works right now

- Main menu with PLAY and EXIT buttons
- Move the blue player with W A S D
- The gun points where the mouse is
- Left click to shoot
- Walls around the arena, the player and bullets can't go through them
- Green zombies come from the edges and run after the player
- One bullet kills one zombie
- If a zombie touches you, the game goes back to the menu

## What we want to add later

Health, ammo, waves, score, different zombie types, and a game over screen.

## How to run it

You need SFML 2.6.1 installed in C:\SFML. Open the folder in a terminal and type:

g++ main.cpp menu.cpp player.cpp arena.cpp -o game.exe -I C:/SFML/include -L C:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

Then copy the 3 dll files from C:\SFML\bin into the same folder as game.exe and run game.exe.

## Controls

W A S D to move, mouse to aim, left click to shoot, ESC to go back to the menu.
