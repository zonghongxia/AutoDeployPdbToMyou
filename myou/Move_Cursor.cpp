#include "Move_Cursor.h"


void gotoxy(int x, int y)//将光标设置到屏幕上的某个位置
{
	COORD coord = { x,y };//一个点，用来表示光标在屏幕中的位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//设置光标位置
}

COORD getxy()//获取当前光标的位置
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;//用于存储将要获得的环境句柄信息
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//保存标准输出环境句柄
	GetConsoleScreenBufferInfo(hOut, &SBInfo);//获得环境句柄，里面包含了当前光标的位置信息
	COORD PrePo;//COORD是一个坐标类，里面是横坐标和纵坐标
	PrePo.X = SBInfo.dwCursorPosition.X;//从中取出光标的位置
	PrePo.Y = SBInfo.dwCursorPosition.Y;
	return PrePo;
}