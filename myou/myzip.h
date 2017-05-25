#ifndef _MYZIP_H
#define _MYZIP_H

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "List_Filepath.h"
#include "../myou/zip.h"
#include "Move_Cursor.h"

class ZIP
{
public:
	ZIP(const std::string &ppath, std::string &pzipfilename=std::string());//输入一个路径和需要压缩的文件的路径
	void CreateMyZip();

	~ZIP();

private:
	static void ChangeSuffix(std::string &path, const std::string &suffix);

	void GetSubStr(const std::string &path, std::string &subtmp);

	void GetZipNameFromPath(const std::vector<std::string> &ve, const std::string path, std::vector<std::string> &zipvector);

	bool IsFolder();
	void ZipFolder();
	void ZipFile();

private:
	static const int GLOBAL_LENSZIP;
	static const int GLOBAL_TMP_LENGTH;

private:
	std::string m_path;
	std::string m_zipfilename;
};

#endif
