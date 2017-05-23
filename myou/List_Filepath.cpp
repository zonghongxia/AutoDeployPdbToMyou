#include "List_Filepath.h"


CBrowseDir::CBrowseDir()
{
	_getcwd(m_szInitDir, _MAX_PATH);

	int len = strlen(m_szInitDir);
	if (m_szInitDir[len - 1] != '\\')
	{
		strcat(m_szInitDir, "\\");
	}
}

bool CBrowseDir::SetInitDir(const char *dir)
{
	if (_fullpath(m_szInitDir, dir, _MAX_PATH) == NULL)
	{
		return false;
	}
	if (_chdir(m_szInitDir) != 0)
	{
		return false;
	}
	int len = strlen(m_szInitDir);
	if (m_szInitDir[len - 1] != '\\')
	{
		strcat(m_szInitDir, "\\");
	}

	return true;
}

std::vector<std::string> CBrowseDir::BeginBrowseFilenames(const char *filespec)
{
	AddDirCount(m_szInitDir, NULL);
	return GetDirFilenames(m_szInitDir, filespec);
}

bool CBrowseDir::BeginBrowse(const char *filespec)
{
	AddDirCount(m_szInitDir, NULL);
	return BrowseDir(m_szInitDir, filespec);
}

bool CBrowseDir::BrowseDir(const char *dir, const char *filespec)
{
	_chdir(dir);

	long l_hFile;
	_finddata_t l_fileinfo;
	if ((l_hFile = _findfirst(filespec, &l_fileinfo)) != -1)
	{
		do
		{
			if (!(l_fileinfo.attrib & _A_SUBDIR))
			{
				char filename[_MAX_PATH];
				strcpy(filename, dir);
				strcat(filename, l_fileinfo.name);
				std::cout << filename << std::endl;
				if (!AddFileCount(filename))
					return false;
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);
		_findclose(l_hFile);
	}  
	_chdir(dir);
	if ((l_hFile = _findfirst("*.*", &l_fileinfo)) != -1)
	{
		do
		{
			if ((l_fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(l_fileinfo.name, ".") != 0  &&  strcmp(l_fileinfo.name, "..") != 0)
				{
					char l_subdir[_MAX_PATH];
					strcpy(l_subdir, dir);
					strcat(l_subdir, l_fileinfo.name);
					strcat(l_subdir, "\\");
					AddDirCount(l_subdir, dir);
					if (!BrowseDir(l_subdir, filespec))
						return false;
				}
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);
		_findclose(l_hFile);
	}
	return true;
}


std::vector<std::string> CBrowseDir::GetDirFilenames(const char *dir, const char *filespec)
{
	_chdir(dir);
	std::vector<std::string> l_filename_vector;
	l_filename_vector.clear();

	long l_hFile;
	_finddata_t l_fileinfo;
	if ((l_hFile = _findfirst(filespec, &l_fileinfo)) != -1)
	{
		do
		{
			if (!(l_fileinfo.attrib & _A_SUBDIR))
			{
				char l_filename[_MAX_PATH];
				strcpy(l_filename, dir);
				strcat(l_filename, l_fileinfo.name);
				l_filename_vector.push_back(l_filename);
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);
		_findclose(l_hFile);
	}

	_chdir(dir);
	if ((l_hFile = _findfirst("*.*", &l_fileinfo)) != -1)
	{
		do
		{
			if ((l_fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(l_fileinfo.name, ".") != 0  &&  strcmp(l_fileinfo.name, "..") != 0)
				{
					char l_subdir[_MAX_PATH];
					strcpy(l_subdir, dir);
					strcat(l_subdir, l_fileinfo.name);
					strcat(l_subdir, "\\");
					AddDirCount(l_subdir, dir);
					std::vector<std::string>l_tmp = GetDirFilenames(l_subdir, filespec);
					for (std::vector<std::string>::iterator it = l_tmp.begin(); it<l_tmp.end(); it++)
					{
						l_filename_vector.push_back(*it);
					}
				}
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);

		_findclose(l_hFile);
	}
	return l_filename_vector;
}

bool CBrowseDir::AddFileCount(const char *filename)
{
	return true;
}


void CBrowseDir::AddDirCount(const char*currentdir, const char *parentdir)
{
}

CStatDir::CStatDir()
{
	m_nFileCount = m_nSubdirCount = 0;
}

int CStatDir::GetFileCount()
{
	return m_nFileCount;
}

int CStatDir::GetSubdirCount()
{
	return m_nSubdirCount - 1;
}

bool CStatDir::AddFileCount(const char *filename)
{
	m_nFileCount++;
	return CBrowseDir::AddFileCount(filename);
}

void CStatDir::AddDirCount(const char *currentdir, const char *parentdir)
{
	m_nSubdirCount++;
	CBrowseDir::AddDirCount(currentdir, parentdir);
}


