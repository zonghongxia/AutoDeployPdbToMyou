#ifndef _GETDIFFHOUR_H
#define _GETDIFFHOUR_H

#include <sys/stat.h>
#include <time.h>
#include <iostream>

class GetDiffHour
{
public:
	GetDiffHour(const std::string &path);

	double GetPathDiffHour();

	~GetDiffHour();

private:
	std::string m_path;
};
#endif

