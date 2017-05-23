#ifndef _MYUNZIP_H
#define _MYUNZIP_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include "List_Filepath.h"
#include "../myou/unzip.h"
#include "Move_Cursor.h"

class UNZIP
{
public:
	UNZIP(const std::string  &ppath, const std::string  &pzippath);
	~UNZIP();
	void CreateZip();
private:
	std::string m_path;
	std::string m_zippath;
};


#endif
