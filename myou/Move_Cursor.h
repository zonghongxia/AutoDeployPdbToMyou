#ifndef _MOVE_CURSOR_H
#define _MOVE_CURSOR_H
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include <iomanip>
using namespace std;

void gotoxy(int x, int y);//将光标设置到屏幕上的某个位置

COORD getxy();//获取当前光标的位置

#endif