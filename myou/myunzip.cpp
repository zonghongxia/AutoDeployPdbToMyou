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

	std::cout << "解压开始" << std::endl;
	hz = OpenZip(m_path.c_str(), 0);//打开一个解压文件
	GetZipItem(hz, -1, &ze);
	if (m_zippath[0] != '\0')
	{
		SetUnzipBaseDir(hz, m_zippath.c_str());//设置解压目录
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
			movecursor.gotoxy(coord.X, coord.Y);//固定到获取的光标的位置
		}
	}
	std::cout << std::endl;
	std::cout << "解压完成" << std::endl;
	CloseZip(hz);
}