#ifndef _POSTFILETOWEB_H
#define _POSTFILETOWEB_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include "Move_Cursor.h"

typedef struct PostNode
{
	const std::string m_cvteurl;
	const std::string m_cookie;
	const std:: string m_postfilename;
	const std::string m_postfilepath;
	const std::string m_appversionname;
	const std::string m_appversion;
}PostNode;

struct myprogress//进度条
{
	double lastruntime;
	CURL *curl;
};

class PostFiletoWeb
{
public:
	PostFiletoWeb(PostNode * const node);
	~PostFiletoWeb();

	void PostHttp();

	static void GetZipPath( std::string &path);
private:
	static const std::string S_SUFFIX_RENAME;
	static int older_progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow);//回调函数
	static size_t CallBackWrite(const char *data, size_t size, int nmember, std::string  * strData);//写入数据的回调函数
	PostNode *m_node;
	static bool m_btag;
};


#endif
