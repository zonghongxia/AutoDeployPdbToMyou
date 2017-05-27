#ifndef _GETRANGEFOLDER_H
#define _GETRANGEFOLDER_H

#include <string>
#include <iostream>
#include "listrangefolder.h"

class GetRangeFolder
{
public:
	GetRangeFolder(const std::string &path, const std::string &cmp1, const std::string &cmp2);

	void GetPathtoVec(std::vector<std::string> &file_vec);

	void show(const std::vector<std::string> &file_vec);
private:
	std::string m_path;
	std::string m_firstcmpfloder;
	std::string m_lastcmpfloder;
};

#endif

