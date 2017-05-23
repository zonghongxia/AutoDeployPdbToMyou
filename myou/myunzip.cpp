#include "myunzip.h"

UNZIP::UNZIP(const std::string  &ppath, const std::string  &pzippath=std::string())
{
	m_path = ppath;
	if (!pzippath.empty())
	{
		m_zippath = pzippath;
	}
	else
	{
		m_zippath[0] = '\0';
	}
	/*m_path = new char[strlen(ppath) + 1];
	strcpy(m_path, ppath);
	m_path[strlen(m_path)] = '\0';
	if (*pzippath != NULL)
	{
		m_zippath = new char[strlen(pzippath) + 1];
		strcpy(m_zippath, pzippath);
		m_zippath[strlen(m_zippath)] = '\0';
	}
	else
	{
		m_zippath = new char[1];
		m_zippath[0] = '\0';
	}*/
}

UNZIP::~UNZIP()  {}

void UNZIP::CreateZip()
{
	HZIP hz;
	ZIPENTRY ze;

	std::cout << "��ѹ��ʼ" << std::endl;
	hz = OpenZip(m_path.c_str(), 0);//��һ����ѹ�ļ�
	GetZipItem(hz, -1, &ze);
	if (m_zippath[0] != '\0')
	{
		SetUnzipBaseDir(hz, m_zippath.c_str());//���ý�ѹĿ¼
	}
	int numitems = ze.index;
	for (int zi = 0; zi<numitems; zi++)
	{
		ZIPENTRY ze;
		GetZipItem(hz, zi, &ze); 
		UnzipItem(hz, zi, ze.name); 

		if (zi == numitems - 1)
		{
			zi += 1;
		}
		MoveCursor movecursor;
		COORD coord = movecursor.getxy();
		double tmpnum = (static_cast<double>(zi) / (static_cast<double>(numitems))) * 100;
		char input[10] = { 0 };
		sprintf(input, "%0.1f", tmpnum);
		strcat(input, "%");
		std::cout << input;
		if (zi == numitems - 1)
		{
			continue;
		}
		else
		{
			movecursor.gotoxy(coord.X, coord.Y);//�̶�����ȡ�Ĺ���λ��
		}
	}
	std::cout << std::endl;
	std::cout << "��ѹ���" << std::endl;
	CloseZip(hz);
}