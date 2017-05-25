#include "GetSatisfyDiffHour.h"

GetSatisfyDiffHour::GetSatisfyDiffHour(const std::string & path, const double &hour)
{
	m_path = path;
	m_hour = hour;
}

GetSatisfyDiffHour::~GetSatisfyDiffHour() {}

void GetSatisfyDiffHour::GetHourList(std::vector<std::string> &file_vec)
{
	CBrowseDirDiffHour statdir(m_path);
	if (!statdir.SetInitDir(m_path))
	{
		puts("目录不存在。");
		return;
	}

	statdir.BeginBrowseFilenames("*.*", file_vec, m_hour);
}

void GetSatisfyDiffHour::show(std::vector<std::string> &file_vec)
{
	for (std::vector<std::string>::iterator it = file_vec.begin(); it < file_vec.end(); ++it)//遍历文件夹中的文件
	{
		std::cout << *it << std::endl;
	}
}