#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <fstream>  
#include <sstream>
#include <curl/curl.h>
#include "List_Filepath.h"
#include "../myou/zip.h"
#include "../myou/unzip.h"
#include "myzip.h"
#include "myunzip.h"
#include "Rename.h"
#include "Get_Cookie.h"
#include "PostFiletoWeb.h"

const char * _CHANGE_FOLDER_NAME = "symbols";

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	//��ȡcookie
	string getcookieurl = "https://myou.cvte.com/api/in/auth/login";
	string user_password("{\"loginName\":\"iip.fwq\", \"password\":\"11111111\"}");//�����û���������
	string content_type("Content-Type:application/json;charset=UTF-8");//����ͷ����Ϣ��Content_Type�ֶ�
	string cookie = GetCookies(getcookieurl, user_password, content_type);

	char path[TMP_LENGTH] = { 0 };//����ѹ���ļ��ľ���·��
	char absolutepath[TMP_LENGTH] = { 0 };//����ѹ����ѹʱ��Ŀ¼
	char unzippathbuf[TMP_LENGTH] = { 0 };
	char UnZipbuf[TMP_LENGTH] = { 0 };
	strcpy(unzippathbuf, "D://zipfile/sym.zip");
	strcpy(UnZipbuf, "D://zipfile");
	strcpy(path, unzippathbuf);
	path[strlen(path) - 1] = '\0';

	//��ѹ
	_UNZIP _unzip(unzippathbuf, UnZipbuf);//��ѹ���ļ�����·�����Զ����ѹ��ʲô·������ѹ������ǰ��Ŀ����Ŀ¼�£�
	_unzip.Create_Zip();

	////�޸��ļ�������
	GetUnzipFolderPath(path);//��ȡ��ѹ�Ժ���ļ������ڵľ���·��
	strcpy(absolutepath, path);
	absolutepath[strlen(absolutepath) - 1] = '\0';
	GetZipFolderPath(absolutepath, _CHANGE_FOLDER_NAME);
	Rename(path, absolutepath);

	//ѹ��
	_ZIP _zip(absolutepath);//(��Ҫ��ѹ��·������ѹ����·��)
	_zip.Create_Zip();
	

	//�ϴ��ļ���web
	GetZipPath(absolutepath);
	string post_file_path = absolutepath;
	string post_file_name("symbol_file");
	string app_version_name("app_version");
	string app_version("200.4.220.55");
	string url = "http://myou.cvte.com/api/in/applications/cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b/crashdumps/upload_symbols";

	PostHttp(url, cookie, post_file_name, post_file_path, app_version_name, app_version);
	return 0;
}
