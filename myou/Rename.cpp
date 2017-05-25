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
	/*for (int i = 0; i < path.size(); ++i)
	{
		if (path[i] != '.')
		{
			tmp += path[i];
		}
		else
		{
			break;
		}
	}
	path = tmp;*/
}

void ChangePath::GetZipFolderPath(std::string &path, const std::string &changefoldername)
{
		//char tmp[GLOBAL_RENAME_TMP_LENGTH] = { 0 };
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
		/*strncpy(tmp, path.c_str(), i + 1);
		strcat(tmp, changefoldername.c_str());*/
		//tmp[strlen(tmp)] = '\0';
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


//g_ChangePath::g_ChangePath()  {}
//g_ChangePath::~g_ChangePath()   {}
//
//const int g_ChangePath::GLOBAL_RENAME_TMP_LENGTH = 128;
//
//void g_ChangePath::GetUnzipFolderPath(char *path)
//{
//	char tmp[GLOBAL_RENAME_TMP_LENGTH] = "\0";
//	for (int i = 0; i < strlen(path); ++i)
//	{
//		if (path[i] != '.')
//		{
//			tmp[i] = path[i];
//		}
//		else
//		{
//			break;
//		}
//	}
//	strcpy(path, tmp);
//	path[strlen(tmp)] = '\0';
//}
//
//void g_ChangePath::GetZipFolderPath(char *path, const char *changefoldername)
//{
//		char tmp[GLOBAL_RENAME_TMP_LENGTH] = { 0 };
//		int i;
//		for (i = strlen(path) - 1; i >= 0; --i)
//		{
//			if (path[i] == '/')
//			{
//				break;
//			}
//		}
//		strncpy(tmp, path, i + 1);
//		strcat(tmp, changefoldername);
//		tmp[strlen(tmp)] = '\0';
//		strcpy(path, tmp);
//		path[strlen(tmp)] = '\0';
//}
//
//void g_ChangePath::CopyPath(char *despath, char *strpath)
//{
//	strcpy(despath, strpath);
//	despath[strlen(despath) - 1] = '\0';
//}
//
//
//void gRename::RenameFolder()
//{
//	if (0 == rename(m_oldname.c_str(), m_newname.c_str()))
//	{
//		std::cout << "rename successful" << std::endl;
//	}
//	else
//	{
//		std::cout << "Rename" << std::endl;
//	}
//}

