#ifndef _LIST_SATIFYDIFFHOUR_H
#define _LIST_SATIFYDIFFHOUR_H

#include <stdlib.h>  
#include <direct.h>
#include <string.h>  
#include <string>  
#include <io.h>
#include <stdio.h>   
#include <vector>  
#include <iostream>
#include "GetDiffHour.h"

class CBrowseDirDiffHour
{
private:
	std::string m_szInitDir;
public:
	CBrowseDirDiffHour(const std::string &initdir);
	bool SetInitDir(const  std::string &dir);
	void BeginBrowseFilenames(const std::string &filespec, std::vector<std::string> &file_vector, double const &hour);
private:
	void GetDirFilenames(const std::string &dir, const std::string &filespec, std::vector<std::string> &file_vector, double const &hour);
};

#endif


