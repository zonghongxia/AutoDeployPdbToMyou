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

	virtual bool AddFileCount(const char *filename);//�����ļ��ĸ����Ľӿ�
	virtual void AddDirCount(const char *currentdir, const char *parentdir);//����Ŀ¼�����Ľӿ�
};

class CStatDir :public CBrowseDir
{
protected:
	int m_nFileCount;   //�����ļ�����  
	int m_nSubdirCount; //������Ŀ¼����  

public:
	CStatDir();
	int GetFileCount();
	int GetSubdirCount();//������Ŀ¼���� 

protected:
	virtual bool AddFileCount(const char *filename);
	virtual void AddDirCount(const char *currentdir, const char *parentdir);
};

#endif

//class g_CBrowseDir
//{
//protected:
//	//��ų�ʼĿ¼�ľ���·������'\'��β  
//	char m_szInitDir[_MAX_PATH];
//
//public:
//	//ȱʡ������  
//	g_CBrowseDir();
//
//	//���ó�ʼĿ¼Ϊdir���������false����ʾĿ¼������  
//	bool SetInitDir(const char *dir);
//
//	//��ʼ������ʼĿ¼������Ŀ¼����filespecָ�����͵��ļ�  
//	//filespec����ʹ��ͨ��� * ?�����ܰ���·����  
//	//�������false����ʾ�������̱��û���ֹ  
//	bool BeginBrowse(const char *filespec);
//	std::vector<std::string> BeginBrowseFilenames(const char *filespec);
//
//protected:
//	//����Ŀ¼dir����filespecָ�����ļ�  
//	//������Ŀ¼,���õ����ķ���  
//	//�������false,��ʾ��ֹ�����ļ�  
//	bool BrowseDir(const char *dir, const char *filespec);
//	std::vector<std::string> GetDirFilenames(const char *dir, const char *filespec);
//	//����BrowseDirÿ�ҵ�һ���ļ�,�͵���ProcessFile  
//	//�����ļ�����Ϊ�������ݹ�ȥ  
//	//�������false,��ʾ��ֹ�����ļ�  
//	//�û����Ը�д�ú���,�����Լ��Ĵ������  
//	virtual bool ProcessFile(const char *filename);
//
//	//����BrowseDirÿ����һ��Ŀ¼,�͵���ProcessDir  
//	//�������ڴ����Ŀ¼������һ��Ŀ¼����Ϊ�������ݹ�ȥ  
//	//������ڴ�����ǳ�ʼĿ¼,��parentdir=NULL  
//	//�û����Ը�д�ú���,�����Լ��Ĵ������  
//	//�����û�����������ͳ����Ŀ¼�ĸ���  
//	virtual void ProcessDir(const char *currentdir, const char *parentdir);
//};
//
//class CStatDir :public g_CBrowseDir
//{
//protected:
//	int m_nFileCount;   //�����ļ�����  
//	int m_nSubdirCount; //������Ŀ¼����  
//
//public:
//	//ȱʡ������  
//	CStatDir()
//	{
//		//��ʼ�����ݳ�Աm_nFileCount��m_nSubdirCount  
//		m_nFileCount = m_nSubdirCount = 0;
//	}
//
//	//�����ļ�����  
//	int GetFileCount()
//	{
//		return m_nFileCount;
//	}
//
//	//������Ŀ¼����  
//	int GetSubdirCount()
//	{
//		//��Ϊ�����ʼĿ¼ʱ��Ҳ����ú���ProcessDir��  
//		//���Լ�1�������������Ŀ¼������  
//		return m_nSubdirCount - 1;
//	}
//
//protected:
//	//��д�麯��ProcessFile��ÿ����һ�Σ��ļ�������1  
//	virtual bool ProcessFile(const char *filename)
//	{
//		m_nFileCount++;
//		return g_CBrowseDir::ProcessFile(filename);
//	}
//
//	//��д�麯��ProcessDir��ÿ����һ�Σ���Ŀ¼������1  
//	virtual void ProcessDir(const char *currentdir, const char *parentdir)
//	{
//		m_nSubdirCount++;
//		g_CBrowseDir::ProcessDir(currentdir, parentdir);
//	}
//};
