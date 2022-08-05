#ifndef MAIN
#define MAIN

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include<fstream>
#include<sstream>
#include<iostream>

#define WINDOW_WIDTH 1500.0f
#define WINDOW_HEIGHT 1000.0f

#define PLANE 0
#define ENEMYBIRD 1
#define ENEMYBOMBER 2
#define ENEMYFIGHTER 3
#define METEOR 4
#define MISSILE 5
#define ENEMYMISSILE 6

#endif