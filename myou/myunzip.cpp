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

	cout << "��ѹ��ʼ" << endl;
	hz = OpenZip(path, 0);//��һ����ѹ�ļ�
	GetZipItem(hz, -1, &ze);
	if (*zippath != '\0')
	{
		SetUnzipBaseDir(hz, zippath);//���ý�ѹĿ¼
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
		COORD coord = getxy();//��ȡ��ǰ������ڵ�λ��
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
			gotoxy(coord.X, coord.Y);//�̶�����ȡ�Ĺ���λ��
		}

	}
	cout << endl;
	cout << "��ѹ���" << endl;
	CloseZip(hz);
}