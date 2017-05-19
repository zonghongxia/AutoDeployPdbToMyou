#ifndef _MYUNZIP_H
#define _MYUNZIP_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "List_Filepath.h"
#include "../myou/unzip.h"

class _UNZIP
{
public:
	_UNZIP(char *_path, char *_zippath);
	~_UNZIP()
	{
		delete path;
		delete zippath;

	}
	void Create_Zip();
private:
	char *path;
	char *zippath;
};


#endif
