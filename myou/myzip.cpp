#include "myzip.h"


using namespace std;

void GetSubStr(string path, string &subtmp)
{
	if (path.empty())
	{
		return;
	}
	int i = path.size() - 1;
	bool tag = true;
	while (path[i] != '/')
	{
		tag = false;
		--i;
	}
	if (!tag)
	{
		subtmp.insert(0, path, i + 1, path.size() - i);
	}
}

vector<string> GetZipNameFromPath(vector<string> ve, string path)//从文件夹所在路径ve中把需要压缩的文件的信息提取出来
{
	vector<string> l_zipvector;
	if (ve.empty() || path.empty())
	{
		return l_zipvector;
	}

	string subtmp;
	GetSubStr(path, subtmp);//获取需要压缩的文件夹

	for (vector<string>::iterator it = ve.begin(); it != ve.end(); ++it)
	{
		size_t rt = (*it).find(subtmp);
		string tmp;
		tmp = (*it).substr(rt, (*it).size() - rt);
		l_zipvector.push_back(tmp);
	}
	return l_zipvector;
}



_ZIP::_ZIP(const char *_path, char *_zipfilename)//输入一个路径和需要压缩的文件的路径
{
	path = new char[strlen(_path) + 1];
	strcpy(path, _path);
	path[strlen(path)] = '\0';
	if (_zipfilename == NULL || *_zipfilename == NULL)
	{
		zipfilename = new char[strlen(_path) + 1 + LENSZIP];
		strcpy(zipfilename, path);
		if (Is_Folder())//判断是否为文件夹
		{
			strcat(zipfilename, ".zip");
		}
		else
		{
			ChangeSuffix(zipfilename, ".zip");
		}
		zipfilename[strlen(zipfilename)] = '\0';
	}
	else
	{
		zipfilename = new char[strlen(_zipfilename) + 1];
		strcpy(zipfilename, _zipfilename);
		zipfilename[strlen(zipfilename)] = '\0';
	}
}

void _ZIP::ChangeSuffix(char *&path, char *suffix)
{
	char tmp[TMP_LENGTH] = { 0 };
	int j = 0;
	for (int i = 0; i < strlen(path); ++i)
	{
		if (path[i] != '.')
		{
			tmp[j] = path[i];
			j++;
		}
		else
		{
			break;
		}
	}
	strcat(tmp, ".zip");
	strcpy(path, tmp);
}

bool _ZIP::Is_Folder()
{
	_chdir(path);
	long hFile;
	_finddata_t fileinfo;
	if ((hFile = _findfirst("*.*", &fileinfo)) != -1)
	{
		do
		{
			//检查是不是目录，如果是返回真，如果是文件返回假
			if ((fileinfo.attrib & _A_SUBDIR) && (strcmp(fileinfo.name, ".") != 0) && (strcmp(fileinfo.name, "..") != 0)
	                                                   		   && (strcmp(fileinfo.name, "Debug")))
			{
				return true;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return false;
}

void _ZIP::Zip_Folder()
{
	CStatDir statdir;
	if (!statdir.SetInitDir(path))
	{
		puts("目录不存在。");
		return;
	}

	HZIP hz;
	hz = CreateZip(zipfilename, (char *)0);

	vector<string>file_vec = statdir.BeginBrowseFilenames("*.*");
	vector<string> zipnamevector = GetZipNameFromPath(file_vec, path);
	vector<string>::iterator zt = zipnamevector.begin();
	int zi = 0;
	double numitems = file_vec.size()+1;
	std::cout<<"压缩开始" << std::endl;
	for (vector<string>::iterator it = file_vec.begin(); it < file_vec.end() && zt != zipnamevector.end(); ++it, ++zt)//遍历文件夹中的文件
	{
		
		char *path = const_cast<char *>((*it).c_str());
		char *zippath = const_cast<char *>((*zt).c_str());
		ZipAdd(hz, zippath, path);

		zi++;
		if (zi == numitems - 1)
		{
			zi += 1;
		}
		COORD coord = getxy();//获取当前光标所在的位置
		double tmpnum = (static_cast<double>(zi) / (static_cast<double>(numitems))) * 100;
		char input[10] = { 0 };
		sprintf(input, "%0.1f", tmpnum);
		strcat(input,"%");
		std::cout << input;
		if (zi == numitems - 1)
		{
			continue;
		}
		else
		{
			gotoxy(coord.X, coord.Y);//固定到获取的光标的位置
		}
	}
	std::cout << std::endl;
	std::cout << "压缩完毕" << std::endl;
	CloseZip(hz);
}

void _ZIP::Zip_File()
{
	HZIP hz;
	hz = CreateZip(zipfilename, (char *)0);

	string subtmp;
	GetSubStr(path, subtmp);//获取需要压缩的文件夹
	char *tmp = const_cast<char *>(subtmp.c_str());
	ZipAdd(hz, tmp, path);
	CloseZip(hz);
}


