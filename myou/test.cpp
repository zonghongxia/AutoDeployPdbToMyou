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
	//获取cookie
	string getcookieurl = "https://myou.cvte.com/api/in/auth/login";
	string user_password("{\"loginName\":\"iip.fwq\", \"password\":\"11111111\"}");//设置用户名和密码
	string content_type("Content-Type:application/json;charset=UTF-8");//设置头部信息的Content_Type字段
	string cookie = GetCookies(getcookieurl, user_password, content_type);

	char path[TMP_LENGTH] = { 0 };//保存压缩文件的绝对路径
	char absolutepath[TMP_LENGTH] = { 0 };//保存压缩解压时的目录
	char unzippathbuf[TMP_LENGTH] = { 0 };
	char UnZipbuf[TMP_LENGTH] = { 0 };
	strcpy(unzippathbuf, "D://zipfile/sym.zip");
	strcpy(UnZipbuf, "D://zipfile");
	strcpy(path, unzippathbuf);
	path[strlen(path) - 1] = '\0';

	//解压
	_UNZIP _unzip(unzippathbuf, UnZipbuf);//（压缩文件所在路径，自定义解压到什么路径否则压缩到当前项目所在目录下）
	_unzip.Create_Zip();

	////修改文件夹名字
	GetUnzipFolderPath(path);//获取解压以后的文件夹所在的绝对路径
	strcpy(absolutepath, path);
	absolutepath[strlen(absolutepath) - 1] = '\0';
	GetZipFolderPath(absolutepath, _CHANGE_FOLDER_NAME);
	Rename(path, absolutepath);

	//压缩
	_ZIP _zip(absolutepath);//(需要解压的路径，解压到的路径)
	_zip.Create_Zip();
	

	//上传文件到web
	GetZipPath(absolutepath);
	string post_file_path = absolutepath;
	string post_file_name("symbol_file");
	string app_version_name("app_version");
	string app_version("200.4.220.55");
	string url = "http://myou.cvte.com/api/in/applications/cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b/crashdumps/upload_symbols";

	PostHttp(url, cookie, post_file_name, post_file_path, app_version_name, app_version);
	return 0;
}
