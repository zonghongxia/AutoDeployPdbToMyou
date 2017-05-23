#ifndef _RENAME_H
#define _RENAME_H

#include <stdio.h>
#include <iostream>

class ChangePath
{
public:
	ChangePath();
	~ChangePath();
public:
	void GetUnzipFolderPath(std::string &path);
	void GetZipFolderPath(std::string &path, const std::string &changefoldername);
	void CopyPath(std::string &despath, const std::string &strpath);
private:
	static const int GLOBAL_RENAME_TMP_LENGTH;
};

class Rename
{
public:
	Rename(const std::string &oldname,const std::string &newname):m_oldname(oldname),m_newname(newname){}
	~Rename() {}

	void RenameFolder();

private:
	std::string m_oldname;
	std::string m_newname;
};

//class g_ChangePath
//{
//public:
//	g_ChangePath();
//	~g_ChangePath();
//public:
//	void GetUnzipFolderPath(char *path);
//	void GetZipFolderPath(char *path, const char *changefoldername);
//	void CopyPath(char *despath,char *strpath);
//private:
//	static const int GLOBAL_RENAME_TMP_LENGTH;
//};
//
//
//class gRename
//{
//public:
//	gRename(const std::string &oldname,const std::string &newname):m_oldname(oldname),m_newname(newname){}
//	~gRename() {}
//
//	void RenameFolder();
//
//private:
//	std::string m_oldname;
//	std::string m_newname;
//};

#endif
