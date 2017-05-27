#include "myunzip.h"

UNZIP::UNZIP(const std::string  &ppath, const std::string  &pzippath)
{
	m_path = ppath;
	if (!pzippath.empty())
	{
		m_zippath = pzippath;
	}
	else
	{
		int i;
		for (i = m_path.size() - 1; i >= 0; --i)
		{
			if (m_path[i] == '\\')
			{
				break;
			}
		}
		std::string tp = m_path;
		m_zippath = tp.assign(tp, 0, i);
	}
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
		std::cout << input<<"  ";
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