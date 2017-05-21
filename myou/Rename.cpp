#include "Rename.h"

void Rename(char *oldname, char *newname)
{
	if (0 == rename(oldname, newname))
	{
		std::cout << "rename successful" << std::endl;
	}
	else
	{
		std::cout << "Rename" << std::endl;
	}
}


void GetUnzipFolderPath(char *path)
{
	char tmp[_TMP_LENGTH] = "\0";
	for (int i = 0; i < strlen(path); ++i)
	{
		if (path[i] != '.')
		{
			tmp[i] = path[i];
		}
		else
		{
			break;
		}
	}
	strcpy(path, tmp);
	path[strlen(tmp)] = '\0';
}

void GetZipFolderPath(char *path, const char *changefoldername)//D://zipfile/sym      symbols
{
	char tmp[_TMP_LENGTH] = { 0 };
	int i;
	for (i = strlen(path) - 1; i >= 0; --i)
	{
		if (path[i] == '/')
		{
			break;
		}
	}
	strncpy(tmp, path, i + 1);
	strcat(tmp, changefoldername);
	tmp[strlen(tmp)] = '\0';
	strcpy(path, tmp);
	path[strlen(tmp)] = '\0';
}

void GetZipPath(char *path)
{
	strcat(path, SUFFIX_RENAME);
	path[strlen(path)] = '\0';
}