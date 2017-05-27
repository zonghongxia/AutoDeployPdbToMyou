#include "GetRangeFolder.h"

GetRangeFolder::GetRangeFolder(const std::string &path, const std::string &cmp1, const std::string &cmp2)
{
	m_path = path;
	if (!cmp1.empty())
	{
		m_firstcmpfloder = cmp1;
	}
	if (!cmp2.empty())
	{
		m_lastcmpfloder = cmp2;
	}
	if (cmp1.empty() && cmp2.empty())
	{
		m_firstcmpfloder = m_lastcmpfloder = std::string();
	}
}

void GetRangeFolder::GetPathtoVec(std::vector<std::string> &file_vec)
{
	CRangeDir statdir(m_path);
	if (!statdir.SetInitDir(m_path))
	{
		puts("目录不存在。");
		return;
	}

	statdir.BeginBrowseFilenames("*.*", file_vec, m_firstcmpfloder, m_lastcmpfloder);
}

void GetRangeFolder::show(const std::vector<std::string> &file_vec)
{
	for (std::vector<std::string>::const_iterator it = file_vec.begin(); it < file_vec.end(); ++it)//遍历文件夹中的文件
	{
		std::cout << *it << std::endl;
	}
}