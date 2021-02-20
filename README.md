# Redino

Redino (working title) is a puzzle game aimed to have a small scope, but easy to expand on.
Everything is WIP as of now.

## Installation

In order to compile, you need to have the SDL2 librabry installed on your system.
On debian based distros, run
```
sudo apt get update && sudo apt -y install libsdl2-dev
```
then, clone the repo, and run make:
```
git clone git@github.com:agiraudet/redino.git
cd redino
make
```

## Usage

You can play all the availables levels one after the other by just running
```
./redino
```

Or you can play only one level of your choice by typing:
```
./redino levels/[your_level]
```

## Controls

- WASD  -> *move the character around*
- Q	    -> *quit*
- E		  -> *interract with things when near*
- SPACE -> *lay an egg*
- R		  -> *hatch the last egg layed*
- Z		  -> *reload the current level*

## Level Building

No fancy level editor is implemented right now, but the game loads levels based on simple text files, so its quite easy to build your owns. I recommand looking at some exemple to understand how things work.
(Their is almost no checking as if a level file is valid or not right now, so dont get surprised if you get a segfault each time something is wrong in a level file).
If the first character of a line is '#', the line is ignored (used for commenting).
The files first need a map composed of 'w' for the walls and '.' for the floor.
It should be completly closed.

Each object you want to add to your level must be describde by one line, starting by an 'O'.
Each setting must be in the correct order, and separeted by spaces and/or tabulations.
The settings are (in order):
- ID *'O' for an object, 'P' for the player, 'H' for a hint that will be displayed in game, 'T' for the level's title. ('H' and 'T' are not displayed in game right now).*
- TYPE *must be one off the currently implemented objects : lever, door, portal, spike, check.
- X *the x postion of the object on the grid*
- Y *the Y postion of the object on the grid*
- COLOR *must be one of the currently implemented color : red, green, blue, white, black, none.*
- STATUS *either 0 or 1, depending of if the object is already activated at the start off the level*
- GROUP *all objects in the same group will be activated by the sensors in the same group. 0 means no group.*
- MODE *determine the actions of the object, see below for more details*
- LOGIC *set which logic gate is use by the object when checking the state of all it's parents sensors to determine its activation. Must one off : OR, AND, XOR, XNOR, NOR, NAND*

The line describing the player should use the followings settings:
- ID *'P' for player*
- TYPE *well, player.*
- X *same as objects*
- Y *same as objects*
- COLOR *same as objects*
- MAXEGG *the maximum allowed number of egg layed at once in the level*

About the MODE setting:
It should be an integer between 0 and 15. the 4 least significant bits are used to determine the following options (from most significant to least) :
- SENSOR *A sensor will dictate the state of the non-sensors objects of his group*
- ACT *determine if the player can interract with the object using E*
- COLL *determine if the game check the object for collision. The object can still be transparent, but this in for exemple need for portal, who change the color off the player on contact.*
- UPDATE *called each frame, for exemple usefull for changing sprites off an object*

To see how each objects use thoses option, looks at the files in srcs/obj/.


## Contribute

Please send bug and remarks to agiraude@student.42.fr.
I would also be very happy to see the levels you created !
