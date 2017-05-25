#ifndef _MYUNZIP_H
#define _MYUNZIP_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include "List_Filepath.h"
#include "../myou/unzip.h"
#include "Move_Cursor.h"

class UNZIP
{
public:
	UNZIP(const std::string  &ppath, const std::string  &pzippath = std::string());
	~UNZIP();
	void CreateZip();
private:
	std::string m_path;//ѹ���ļ�����Ŀ¼
	std::string m_zippath;//��Ҫ��������·��
};


#endif
