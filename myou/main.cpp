#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <fstream>  
#include <sstream>
#include "myzip.h"
#include "myunzip.h"
#include "Rename.h"
#include "Get_Cookie.h"
#include "PostFiletoWeb.h"

const std::string G_GLOBAL_CHANGE_FOLDER_NAME = "symbols";

int main()
{
	//��ȡcookie
	std::string getcookieurl = "https://myou.cvte.com/api/in/auth/login";
	std::string userpassword("{\"loginName\":\"iip.fwq\", \"password\":\"11111111\"}");//�����û���������
	std::string contenttype("Content-Type:application/json;charset=UTF-8");//����ͷ����Ϣ��Content_Type�ֶ�
	GetCookie  gcookie(getcookieurl,userpassword,contenttype);
	std::string cookie = gcookie.GetCookies();
	//std::cout << "cookie =  " << cookie << std::endl;

	std::string path;//����ѹ���ļ��ľ���·��
	std::string absolutepath;//����ѹ����ѹʱ��Ŀ¼
	std::string unzippathbuf;
	std::string unzipbuf;
	unzippathbuf = "D://zipfile/sym.zip";//ѹ���ļ����ڵľ���·��
	unzipbuf = "D://zipfile";//��Ҫ��������Ŀ¼
	path = unzippathbuf;

	//��ѹ
	UNZIP unzip(unzippathbuf, unzipbuf);//��ѹ���ļ�����·�����Զ����ѹ��ʲô·������ѹ������ǰ��Ŀ����Ŀ¼�£�
	unzip.CreateZip();

	//�޸��ļ�������
	ChangePath lpath;
	lpath.GetUnzipFolderPath(path);//��ȡ��ѹ�Ժ���ļ������ڵľ���·��
	lpath.CopyPath(absolutepath, path);
	lpath.GetZipFolderPath(absolutepath, G_GLOBAL_CHANGE_FOLDER_NAME);
	Rename rename(path, absolutepath);
	rename.RenameFolder();

	//ѹ��
	ZIP zip(absolutepath.c_str());//(��Ҫ��ѹ��·������ѹ����·��)
	zip.CreateMyZip();

	////�ϴ��ļ���web
	PostFiletoWeb::GetZipPath(absolutepath);
	std::string postfilepath = absolutepath;
	std::string postfilename("symbol_file");
	std::string appversionname("app_version");
	std::string appversion("520.11.31.4");
	std::string url = "http://myou.cvte.com/api/in/applications/cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b/crashdumps/upload_symbols";

	PostNode postnode = {url,cookie, postfilename, postfilepath, appversionname, appversion };
	PostFiletoWeb posthttp(&postnode);
	posthttp.PostHttp();
	return 0;
}
