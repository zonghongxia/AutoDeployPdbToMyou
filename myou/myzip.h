#ifndef _MYZIP_H
#define _MYZIP_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "List_Filepath.h"
#include "../myou/zip.h"
#include "Move_Cursor.h"

const int LENSZIP = 4;

const int TMP_LENGTH = 128;

void GetSubStr(string path, string &subtmp);

vector<string> GetZipNameFromPath(vector<string> ve, string path);//���ļ�������·��ve�а���Ҫѹ�����ļ�����Ϣ��ȡ����

class _ZIP
{
public:
	_ZIP(const char *_path, char *_zipfilename = NULL);//����һ��·������Ҫѹ�����ļ���·��
	inline void Create_Zip()
	{
		if (Is_Folder())
		{
			Zip_Folder();
		}
		else
		{
			Zip_File();
		}
	}

	~_ZIP()
	{
		delete path;
		delete zipfilename;
	}

private:
	static void ChangeSuffix(char *&path, char *suffix);

	bool Is_Folder();
	void Zip_Folder();

	void Zip_File();
	char *path;
	char *zipfilename;
};


#endif
