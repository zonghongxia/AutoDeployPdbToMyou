#ifndef _POSTFILETOWEB_H
#define _POSTFILETOWEB_H

#include <iostream>
#include <curl/curl.h>
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

struct myprogress
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
	static int older_progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow);//»Øµ÷º¯Êý
	PostNode *m_node;
	static bool m_btag;
};


#endif
