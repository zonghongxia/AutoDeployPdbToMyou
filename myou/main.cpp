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
	//获取cookie
	std::string getcookieurl = "https://myou.cvte.com/api/in/auth/login";
	std::string userpassword("{\"loginName\":\"iip.fwq\", \"password\":\"11111111\"}");//设置用户名和密码
	std::string contenttype("Content-Type:application/json;charset=UTF-8");//设置头部信息的Content_Type字段
	GetCookie  gcookie(getcookieurl,userpassword,contenttype);
	std::string cookie = gcookie.GetCookies();
	//std::cout << "cookie =  " << cookie << std::endl;

	std::string path;//保存压缩文件的绝对路径
	std::string absolutepath;//保存压缩解压时的目录
	std::string unzippathbuf;
	std::string unzipbuf;
	unzippathbuf = "D://zipfile/sym.zip";//压缩文件所在的绝对路径
	unzipbuf = "D://zipfile";//所要解析到的目录
	path = unzippathbuf;

	//解压
	UNZIP unzip(unzippathbuf, unzipbuf);//（压缩文件所在路径，自定义解压到什么路径否则压缩到当前项目所在目录下）
	unzip.CreateZip();

	//修改文件夹名字
	ChangePath lpath;
	lpath.GetUnzipFolderPath(path);//获取解压以后的文件夹所在的绝对路径
	lpath.CopyPath(absolutepath, path);
	lpath.GetZipFolderPath(absolutepath, G_GLOBAL_CHANGE_FOLDER_NAME);
	Rename rename(path, absolutepath);
	rename.RenameFolder();

	//压缩
	ZIP zip(absolutepath.c_str());//(需要解压的路径，解压到的路径)
	zip.CreateMyZip();

	////上传文件到web
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
