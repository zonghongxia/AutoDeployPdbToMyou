#ifndef _LIST_FILEPATH_H
#define _LIST_FILEPATH_H

#include <stdlib.h>  
#include <direct.h>
#include <string.h>  
#include <string>  
#include <io.h>
#include <stdio.h>   
#include <vector>  
#include <iostream>  


class CBrowseDir
{
protected:
	char m_szInitDir[_MAX_PATH];
public:
	CBrowseDir();

	bool SetInitDir(const char *dir);
	bool BeginBrowse(const char *filespec);
	std::vector<std::string> BeginBrowseFilenames(const char *filespec);
protected:
	bool BrowseDir(const char *dir, const char *filespec);
	std::vector<std::string> GetDirFilenames(const char *dir, const char *filespec);

	virtual bool AddFileCount(const char *filename);//处理文件的个数的接口
	virtual void AddDirCount(const char *currentdir, const char *parentdir);//处理目录个数的接口
};

class CStatDir :public CBrowseDir
{
protected:
	int m_nFileCount;   //保存文件个数  
	int m_nSubdirCount; //保存子目录个数  

public:
	CStatDir();
	int GetFileCount();
	int GetSubdirCount();//返回子目录个数 

protected:
	virtual bool AddFileCount(const char *filename);
	virtual void AddDirCount(const char *currentdir, const char *parentdir);
};

#endif