#include "listrangefolder.h"

CRangeDir::CRangeDir(const std::string &initdir)
{
	m_szInitDir = initdir;
	int len = m_szInitDir.size();
	if (m_szInitDir[len - 1] != '/')
	{
		m_szInitDir += "/";
	}
}

bool CRangeDir::SetInitDir(const  std::string &dir)
{
	if (_fullpath(const_cast<char *>(m_szInitDir.c_str()), dir.c_str(), _MAX_PATH) == NULL)
	{
		return false;
	}
	if (_chdir(m_szInitDir.c_str()) != 0)
	{
		return false;
	}
	int len = m_szInitDir.size();
	if (m_szInitDir[len - 1] != '\\')
	{
		m_szInitDir += "\\";
	}

	return true;
}

void CRangeDir::BeginBrowseFilenames(const std::string &filespec, std::vector<std::string> &file_vector, std::string &cmpfolder, const std::string &cmpfolder2)
{
	return GetDirFilenames(m_szInitDir, filespec, file_vector, cmpfolder, cmpfolder2);
}

void CRangeDir::GetDirFilenames(const std::string &dir, const std::string &filespec, std::vector<std::string> &file_vector, const std::string &cmpfolder, const std::string &cmpfolder2)
{
	_chdir(dir.c_str());
	file_vector.clear();
	long l_hFile;
	_finddata_t l_fileinfo;

	if (cmpfolder.empty() && cmpfolder2.empty())
	{
		std::string Newpath;
		bool btag = false;
		long min = 0;
		_chdir(dir.c_str());
		if ((l_hFile = _findfirst("*.*", &l_fileinfo)) != -1)
		{
			do
			{
				if ((l_fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(l_fileinfo.name, ".") != 0 && strcmp(l_fileinfo.name, "..") != 0)
					{
						char l_subdir[_MAX_PATH];
						strcpy(l_subdir, dir.c_str());
						strcat(l_subdir, "\\");
						strcat(l_subdir, l_fileinfo.name);
						GetDiffHour pathdiff(l_subdir);
						long p = pathdiff.GetPathDiffHour();
						if (!btag)
						{
							min = p;
							Newpath = l_subdir;
							btag = true;
						}
						else
						{
							if (p <= min)
							{
								min = p;
								Newpath = l_subdir;
							}
						}
					}
				}
			} while (_findnext(l_hFile, &l_fileinfo) == 0);
			file_vector.push_back(Newpath);
			_findclose(l_hFile);
		}
	}
	else if (!cmpfolder.empty() && !cmpfolder2.empty())
	{
		bool btag = false;
		_chdir(dir.c_str());
		if ((l_hFile = _findfirst("*.*", &l_fileinfo)) != -1)
		{
			do
			{
				if ((l_fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(l_fileinfo.name, ".") != 0 && strcmp(l_fileinfo.name, "..") != 0)
					{
						char l_subdir[_MAX_PATH];
						strcpy(l_subdir, dir.c_str());
						strcat(l_subdir, "\\");
						strcat(l_subdir, l_fileinfo.name);

						if (strcmp(cmpfolder.c_str(), l_fileinfo.name) == 0)
						{
							file_vector.push_back(l_subdir);
							btag = true;
						}
						else if (!btag)
						{
							continue;
						}
						else if (strcmp(cmpfolder2.c_str(), l_fileinfo.name) != 0)
						{
							file_vector.push_back(l_subdir);
						}
						else if (strcmp(cmpfolder2.c_str(), l_fileinfo.name) == 0)
						{
							file_vector.push_back(l_subdir);
							break;
						}
					}
				}
			} while (_findnext(l_hFile, &l_fileinfo) == 0);
			_findclose(l_hFile);
		}
	}
	else
	{
		if ((l_hFile = _findfirst("*.*", &l_fileinfo)) != -1)
		{
			do
			{
				if ((l_fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(l_fileinfo.name, ".") != 0 && strcmp(l_fileinfo.name, "..") != 0)
					{
						if (strcmp(cmpfolder.c_str(), l_fileinfo.name) == 0)
						{
							char l_subdir[_MAX_PATH];
							strcpy(l_subdir, dir.c_str());
							strcat(l_subdir, "\\");
							strcat(l_subdir, l_fileinfo.name);
							file_vector.push_back(l_subdir);
							break;
						}
					}
				}
			} while (_findnext(l_hFile, &l_fileinfo) == 0);
			_findclose(l_hFile);
		}
	}
}