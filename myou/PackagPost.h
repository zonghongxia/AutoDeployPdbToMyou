#ifndef _PACKAGPOST_H
#define _PACKAGPOST_H
#include <string>
#include <iostream>
#include <map>
#include "myzip.h"
#include "myunzip.h"
#include "Rename.h"
#include "Get_Cookie.h"
#include "PostFiletoWeb.h"
#include "Constant.h"

class PackagPost
{
public:
	bool IsPostFiletoWeb();

	void PostToWeb(const std::vector<std::string> &file_vec);
private:

	void ExtractPathandAppversion(std::map<std::string, std::string> &apmap, const std::vector<std::string> &file_vec);
};


#endif
