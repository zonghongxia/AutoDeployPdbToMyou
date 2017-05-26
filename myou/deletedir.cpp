#include "deletedir.h"

DeleteFolderorFile::DeleteFolderorFile(std::string &path)
{
	m_pDir = path;
}
bool DeleteFolderorFile::DeleteDir()
{
	if (m_pDir.empty())
	{
		return false;
	}
	//�ж����ļ������ļ���
	struct _stat sfile;
	if (_stat(m_pDir.c_str(), &sfile) == 0)
	{
		if (_S_IFREG&sfile.st_mode)
		{
			if (DeleteFile(m_pDir.c_str()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (_S_IFDIR & sfile.st_mode)
		{

			if (DeleteFolder(m_pDir.c_str()))////////////////////
			{
				return true;
			}
		}
	}
	return true;
}
bool DeleteFolderorFile::DeleteFolder(const std::string &lpPath)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind, lpPath.c_str());
	strcat(szFind, "\\*.*");
	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)//��Ȥ�ķ��� 
	{
		return false;
	}
	while (TRUE) {
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{  //�ж��Ƿ�Ϊ�ļ���        
			if (FindFileData.cFileName[0] != '.')
			{
				strcpy(szFind, lpPath.c_str());
				strcat(szFind, "\\");
				strcat(szFind, FindFileData.cFileName);
				//std::cout << szFind << std::endl;
				if (!DeleteFolder(szFind))
				{
					return false;
				}
			}
		}
		else
		{
			std::string buf;
			buf = lpPath;
			buf += "\\";
			buf += FindFileData.cFileName;
			if (!DeleteFile(buf.c_str()))//Ƕ������ɾ��
			{
				return false;
			}
		}
		if (!FindNextFile(hFind, &FindFileData))
		{
			break;
		}
	}
	FindClose(hFind);
	RemoveDirectory(lpPath.c_str());
	return true;
}