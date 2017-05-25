#ifndef _GETSATISFYDIFFHOUR_H
#define _GETSATISFYDIFFHOUR_H

#include <iostream>
#include <vector>
#include "list_satifydiffhour_file.h"

class GetSatisfyDiffHour
{
public:
	GetSatisfyDiffHour(const std::string & path, const double &hour);
	~GetSatisfyDiffHour();
	void GetHourList(std::vector<std::string> &file_vec);
	void show(std::vector<std::string> &file_vec);
private:
	std::string m_path;
	double m_hour;
};

#endif
