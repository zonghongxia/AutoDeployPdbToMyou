#include "Move_Cursor.h"


void gotoxy(int x, int y)//��������õ���Ļ�ϵ�ĳ��λ��
{
	COORD coord = { x,y };//һ���㣬������ʾ�������Ļ�е�λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//���ù��λ��
}

COORD getxy()//��ȡ��ǰ����λ��
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;//���ڴ洢��Ҫ��õĻ��������Ϣ
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//�����׼����������
	GetConsoleScreenBufferInfo(hOut, &SBInfo);//��û����������������˵�ǰ����λ����Ϣ
	COORD PrePo;//COORD��һ�������࣬�����Ǻ������������
	PrePo.X = SBInfo.dwCursorPosition.X;//����ȡ������λ��
	PrePo.Y = SBInfo.dwCursorPosition.Y;
	return PrePo;
}