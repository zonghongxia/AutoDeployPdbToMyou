#include "myunzip.h"

_UNZIP::_UNZIP(char *_path, char *_zippath=NULL)
{
	path = new char[strlen(_path) + 1];
	strcpy(path, _path);
	path[strlen(path)] = '\0';
	if (*_zippath != NULL)
	{
		zippath = new char[strlen(_zippath) + 1];
		strcpy(zippath, _zippath);
		zippath[strlen(zippath)] = '\0';
	}
	else
	{
		zippath = new char[1];
		zippath[0] = '\0';
	}
}

void _UNZIP::Create_Zip()
{
	HZIP hz;
	ZIPENTRY ze;

	cout << "解压开始" << endl;
	hz = OpenZip(path, 0);//打开一个解压文件
	GetZipItem(hz, -1, &ze);
	if (*zippath != '\0')
	{
		SetUnzipBaseDir(hz, zippath);//设置解压目录
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
		COORD coord = getxy();//获取当前光标所在的位置
		double tmpnum = (static_cast<double>(zi) / (static_cast<double>(numitems))) * 100;
		char input[10] = { 0 };
		sprintf(input, "%0.1f", tmpnum);
		strcat(input, "%");
		cout << input;
		if (zi == numitems - 1)
		{
			continue;
		}
		else
		{
			gotoxy(coord.X, coord.Y);//固定到获取的光标的位置
		}

	}
	cout << endl;
	cout << "解压完成" << endl;
	CloseZip(hz);
}