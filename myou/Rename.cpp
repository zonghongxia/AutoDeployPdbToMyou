#include "Rename.h"

ChangePath::ChangePath() {}
ChangePath::~ChangePath()   {}

const int ChangePath::GLOBAL_RENAME_TMP_LENGTH = 128;

void ChangePath::GetUnzipFolderPath(std::string &path)
{
	//std::string tmp("\0");
	int i;
	for (i = path.size() - 1; i >= 0; --i)
	{
		if (path[i] == '.')
		{
			break;
		}
	}
	path = path.assign(path,0,i);
}

void ChangePath::GetZipFolderPath(std::string &path, const std::string &changefoldername)
{
		std::string tmp;
		int i;
		for (i = path.size() - 1; i >= 0; --i)
		{
			if (path[i] == '\\')
			{
				break;
			}
		}
		tmp = path.assign(path,0,i+1);
		tmp += changefoldername;
		path = tmp;
}

void ChangePath::CopyPath(std::string &despath, const std::string &strpath)
{
	despath = strpath;

}


void Rename::RenameFolder()
{
	if (0 == rename(m_oldname.c_str(), m_newname.c_str()))
	{
		std::cout << "rename successful" << std::endl;
	}
	else
	{
		std::cout << "Rename" << std::endl;
	}
}

