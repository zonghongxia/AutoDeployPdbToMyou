#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <curl/curl.h>
#include "List_Filepath.h"
#include "../myou/zip.h"
#include "../myou/unzip.h"
#include "myzip.h"
#include "myunzip.h"

const int TMP_LENGTH = 128;

const char * CHANGE_FOLDER_NAME = "symbols";

const char *SUFFIX_NAME = ".zip";


void Rename(char *oldname, char *newname)
{
	if (rename(oldname, newname) == 0)
	{
		cout << "rename successful" << endl;
	}
	else
	{
		cout << "Rename" << endl;
	}
}

void PostHttp(char *path)
{
	CURL *curl;
	CURLcode res;
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;

	curl_global_init(CURL_GLOBAL_ALL);

	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "app_version",
		CURLFORM_COPYCONTENTS, "1.1.111.2",
		CURLFORM_END);

	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "symbol_file",
		CURLFORM_FILE, path,
		CURLFORM_END);//symbols


	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "Submit",
		CURLFORM_END);

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://myou.cvte.com/api/in/applications/cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b/crashdumps/upload_symbols");


		curl_easy_setopt(curl, CURLOPT_COOKIE, "x-auth-token=eyJ0cHkiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJleHAiOjE0OTU3NzU2OTMsImlkIjoiNTkwZDNjMjI1YjY2NjQxYzQ5YmQxODMxIn0.tv91XtEBP36wHTHWRzBFtQ4QdcJiyO_aD_IZkJKj-x4; Expires=Fri, 26-May-2017 05:14:53 GMT; Path=/");
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		curl_formfree(formpost);
	}
}

void GetUnzipFolderPath(char *path)
{
	char tmp[TMP_LENGTH] = {0};
	for (int i = 0; i < strlen(path); ++i)
	{
		if (path[i] != '.')
		{
			tmp[i] = path[i];
		}
		else
		{
			break;
		}
	}
	strcpy(path,tmp);
	path[strlen(tmp)] = '\0';
}

void GetZipFolderPath(char *path,const char *changefoldername)//D://zipfile/sym      symbols
{
	char tmp[TMP_LENGTH] = { 0 };
	int i;
	for (i=strlen(path)-1; i >= 0; --i)
	{
		if (path[i] == '/')
		{
			break;
		}
	}
	strncpy(tmp,path,i+1);
	strcat(tmp,changefoldername);
	tmp[strlen(tmp)] = '\0';
	strcpy(path,tmp);
	path[strlen(tmp)] = '\0';
}

void GetZipPath(char *path)
{
	strcat(path, SUFFIX_NAME);
	path[strlen(path)] = '\0';
}

int main(int argc, char *argv[])
{
	char path[TMP_LENGTH] = {0};//保存压缩文件的绝对路径
	char absolutepath[TMP_LENGTH] = {0};//保存压缩解压时的目录

	//输入路径
	char unzippathbuf[TMP_LENGTH] = { 0 };
	fgets(unzippathbuf, TMP_LENGTH, stdin);//输入压缩文件所在目录
	unzippathbuf[strlen(unzippathbuf) - 1] = '\0';
	strcpy(path,unzippathbuf);
	path[strlen(path) - 1] = '\0';
	char UnZipbuf[TMP_LENGTH] = { 0 };
	fgets(UnZipbuf, TMP_LENGTH, stdin);//输入解压到的路径
	UnZipbuf[strlen(UnZipbuf) - 1] = '\0';

	//解压
	_UNZIP _unzip(unzippathbuf, UnZipbuf);//（压缩文件所在路径，自定义解压到什么路径否则压缩到当前项目所在目录下）
	_unzip.Create_Zip();

	////修改文件夹名字
	GetUnzipFolderPath(path);//获取解压以后的文件夹所在的绝对路径
	strcpy(absolutepath,path);
	absolutepath[strlen(absolutepath) - 1] = '\0';
	GetZipFolderPath(absolutepath, CHANGE_FOLDER_NAME);
	Rename(path, absolutepath);

	cout << path << endl;
	cout << absolutepath << endl;

	//压缩
	_ZIP _zip(absolutepath);//(需要解压的路径，解压到的路径)
	_zip.Create_Zip();

	GetZipPath(absolutepath);

	cout << absolutepath << endl;

	//上传到WEB
	PostHttp(absolutepath);



	//http://myou.cvte.com/#/login

	return 0;
}




//int main()
//{
////压缩
//	/*char Folderpathbuf[256] = {0};
//	fgets(Folderpathbuf, 256, stdin);
//	Folderpathbuf[strlen(Folderpathbuf) - 1] = '\0';
//	char Zipbuf[256] = {0};
//	fgets(Zipbuf, 256, stdin);
//	Zipbuf[strlen(Zipbuf) - 1] = '\0';
//	_ZIP _zip(Folderpathbuf,Zipbuf);//(需要解压的路径，解压到的路径)
//	_zip.Create_Zip();*/
//
////解压
//	char unzippathbuf[256] = {0};
//	fgets(unzippathbuf, 256, stdin);
//	unzippathbuf[strlen(unzippathbuf) - 1] = '\0';
//	char UnZipbuf[256] = {0};
//	fgets(UnZipbuf, 256, stdin);
//	UnZipbuf[strlen(UnZipbuf) - 1] = '\0';
//	_UNZIP _unzip(unzippathbuf, UnZipbuf);//（压缩文件所在路径，自定义解压到什么路径否则压缩到当前项目所在目录下）
//	_unzip.Create_Zip();
//
//	return 0;
//}