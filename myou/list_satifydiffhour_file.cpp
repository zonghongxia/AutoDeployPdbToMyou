#include "list_satifydiffhour_file.h"

CBrowseDirDiffHour::CBrowseDirDiffHour(const std::string &initdir)
{
	m_szInitDir = initdir;
	int len = m_szInitDir.size();
	if (m_szInitDir[len - 1] != '/')
	{
		m_szInitDir += "/";
	}
}

bool CBrowseDirDiffHour::SetInitDir(const  std::string &dir)
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

void CBrowseDirDiffHour::BeginBrowseFilenames(const std::string &filespec, std::vector<std::string> &file_vector, double const &hour)
{
	return GetDirFilenames(m_szInitDir, filespec, file_vector, hour);
}

void CBrowseDirDiffHour::GetDirFilenames(const std::string &dir, const std::string &filespec, std::vector<std::string> &file_vector, double const &hour)
{
	_chdir(dir.c_str());
	file_vector.clear();

	long l_hFile;
	_finddata_t l_fileinfo;
	if ((l_hFile = _findfirst(filespec.c_str(), &l_fileinfo)) != -1)
	{
		do
		{
			if (!(l_fileinfo.attrib & _A_SUBDIR))
			{
				char l_filename[_MAX_PATH];
				strcpy(l_filename, dir.c_str());
				strcat(l_filename, l_fileinfo.name);
				GetDiffHour pathdiff(l_filename);
				double p = pathdiff.GetPathDiffHour();
				if (p <= hour)
				{
					file_vector.push_back(l_filename);
				}
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);
		_findclose(l_hFile);
	}

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
					double p = pathdiff.GetPathDiffHour();
					if (p <= hour)
					{
						file_vector.push_back(l_subdir);
					}
				}
			}
		} while (_findnext(l_hFile, &l_fileinfo) == 0);

		_findclose(l_hFile);
	}
}