#include "Move_Cursor.h"

MoveCursor::MoveCursor():m_x(0),m_y(0)  {}

MoveCursor::~MoveCursor()  {}

void MoveCursor::gotoxy(int x, int y)//���ù���λ��
{
	COORD l_coord = { x,y };//һ���㣬������ʾ�������Ļ�е�λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), l_coord);
}

COORD MoveCursor::getxy()
{
	CONSOLE_SCREEN_BUFFER_INFO l_SBInfo;//���ڴ洢��Ҫ��õĻ��������Ϣ
	HANDLE l_hOut = GetStdHandle(STD_OUTPUT_HANDLE);//�����׼����������
	GetConsoleScreenBufferInfo(l_hOut, &l_SBInfo);//��û����������������˵�ǰ����λ����Ϣ
	COORD l_PrePo;//COORD��һ�������࣬�����Ǻ������������
	l_PrePo.X = l_SBInfo.dwCursorPosition.X;//����ȡ������λ��
	l_PrePo.Y = l_SBInfo.dwCursorPosition.Y;
	return l_PrePo;
}

