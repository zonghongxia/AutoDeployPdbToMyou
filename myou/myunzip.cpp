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

	hz = OpenZip(path, 0);//(正确)
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
	}
	CloseZip(hz);
}