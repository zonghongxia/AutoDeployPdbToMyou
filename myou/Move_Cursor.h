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

	void gotoxy(int x, int y);//���������x,y��λ��

	COORD getxy();//��ȡ��ǰ�������λ��
private:
	int m_x;//������
	int m_y;//������
};

#endif