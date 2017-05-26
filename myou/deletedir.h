#ifndef _DELETEDIR_H_
#define _DELETEDIR_H_

#include <Windows.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <string>
#include <iostream>

class DeleteFolderorFile
{
public:
	DeleteFolderorFile(std::string &path);
	bool DeleteDir();
	bool DeleteFolder(const std::string &lpPath);
private:
	//bool DeleteFolder(const std::string &lpPath);
	std::string m_pDir;
};

#endif