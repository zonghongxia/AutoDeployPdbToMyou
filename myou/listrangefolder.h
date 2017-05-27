#ifndef _LIST_FILEPATH_H
#define _LIST_FILEPATH_H

#include <stdlib.h>  
#include <direct.h>
#include <string.h>  
#include <string>  
#include <io.h>
#include <stdio.h>   
#include <vector>  
#include <iostream>
#include "GetDiffHour.h"

class CRangeDir
{
private:
	std::string m_szInitDir;
public:
	CRangeDir(const std::string &initdir);
	bool SetInitDir(const  std::string &dir);
	void BeginBrowseFilenames(const std::string &filespec, std::vector<std::string> &file_vector, std::string &cmpfolder, const std::string &cmpfolder2);
private:
	void GetDirFilenames(const std::string &dir, const std::string &filespec, std::vector<std::string> &file_vector, const std::string &cmpfolder, const std::string &cmpfolder2);
};

#endif


