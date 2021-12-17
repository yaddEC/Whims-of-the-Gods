</br>

## Presentation

**Whim Of The Gods** is a tower defense game made in C++ and by using Raylib.</br> 
This is our very first project in C++ so the objective was to get used to C++ architechture and features.

</br>

### **GamePlay**

The gameplay is very simple, it's a classic tower defense. </br>
In **Whim Of The Gods** the player must protect the castle from the enemies by placing turrets along the path. Every turret costs money and you only start with 100$ but don't worry killing enemies and destroying objects will reward you with some money. The money will allow you to buy new turrets, upgade the ones you already have. You can't move or trade turrets once they are placed you hqve the option to sell them at half of their original price. </br>
There are **3 types of enemies**. The first ones are **warriors** (medium speed, medium damage), the second ones are **berserkers** (low speed, high damage) and the last are **healers** (high speed, low damage and obviously heal). Make the best strategie and defeat as many enemy waves as possible!

</br>


## Project Structure

``` sh
.
├── assets
│   ├── 1_plan.png
│   ├── 2_plan.png
│   ├── 3_plan.png
│   ├── 4_plan.png
│   ├── 5_plan.png
│   ├── buttonSound.wav
│   ├── creditsTheme.mp3
│   ├── gameOverTheme.mp3
│   ├── hit01.wav
│   ├── hit02.wav
│   ├── hit03.wav
│   ├── jackhammer.png
│   ├── Kaboom.mp3
│   ├── mainTheme.mp3
│   ├── Metal Hit.mp3
│   ├── secondTheme.mp3
│   ├── sellSound.ogg
│   ├── title.png
│   ├── towerDefense_tilesheet_aide.png
│   └── towerDefense_tilesheet.png
├── Makefile
├── README.md
├── src
│   ├── entities
│   │   ├── enemy.cpp
│   │   ├── enemy.hpp
│   │   ├── entity.cpp
│   │   ├── entity.hpp
│   │   ├── tile.cpp
│   │   ├── tile.hpp
│   │   ├── turret.cpp
│   │   └── turret.hpp
│   ├── game.cpp
│   ├── game.hpp
│   ├── main.cpp
│   ├── sounds.cpp
│   └── sounds.hpp
└── third_party
    ├── include
    │   ├── mathematics.hpp
    │   └── raylib.h
    ├── libs-wasm32-unknown-emscripten
    │   └── libraylib.a
    ├── libs-x86_64-linux-gnu
    │   └── libraylib.a
    └── libs-x86_64-pc-cygwin
        └── libraylib.a
```
</br>

## Commands

Compile :
``` sh
$make 
```
Execute :
``` sh
$./tower
```
Delete .d and .o files:
``` sh
$make clean
```

</br>

## More Informations

- Last version: **v1.0**
- Last Update date: **12/17/2021**
- Authors: **DECHAUX Yann** & **HENO Matias**