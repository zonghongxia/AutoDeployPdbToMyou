#ifndef _DELETEDIR_H_
#define _DELETEDIR_H_

#include <Windows.h>
#include <tchar.h>
#include <cstring>
#include <string.h>
#include <wchar.h>
#include <tchar.h>
#include <shellapi.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <string>
#include <iostream>

class DeleteFolderorFile
{
public:
	DeleteFolderorFile(std::string &path);
	bool DeleteDir();
private:
	bool DeleteDirectory(LPCTSTR lpszDir, bool noRecycleBin = true);
	std::string m_pDir;
};

#endif