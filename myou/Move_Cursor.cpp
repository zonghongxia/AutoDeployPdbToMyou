#include "Move_Cursor.h"

MoveCursor::MoveCursor():m_x(0),m_y(0)  {}

MoveCursor::~MoveCursor()  {}

void MoveCursor::gotoxy(int x, int y)//设置光标的位置
{
	COORD l_coord = { x,y };//一个点，用来表示光标在屏幕中的位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), l_coord);
}

COORD MoveCursor::getxy()
{
	CONSOLE_SCREEN_BUFFER_INFO l_SBInfo;//用于存储将要获得的环境句柄信息
	HANDLE l_hOut = GetStdHandle(STD_OUTPUT_HANDLE);//保存标准输出环境句柄
	GetConsoleScreenBufferInfo(l_hOut, &l_SBInfo);//获得环境句柄，里面包含了当前光标的位置信息
	COORD l_PrePo;//COORD是一个坐标类，里面是横坐标和纵坐标
	l_PrePo.X = l_SBInfo.dwCursorPosition.X;//从中取出光标的位置
	l_PrePo.Y = l_SBInfo.dwCursorPosition.Y;
	return l_PrePo;
}

