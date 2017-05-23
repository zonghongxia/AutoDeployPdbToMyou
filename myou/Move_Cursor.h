#ifndef _MOVE_CURSOR_H
#define _MOVE_CURSOR_H
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include <iomanip>

class MoveCursor
{
public:
	MoveCursor();
	~MoveCursor();

	void gotoxy(int x, int y);//将光标跳到x,y的位置

	COORD getxy();//获取当前光标所在位置
private:
	int m_x;//横坐标
	int m_y;//纵坐标
};

#endif