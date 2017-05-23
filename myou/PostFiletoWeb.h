#ifndef _POSTFILETOWEB_H
#define _POSTFILETOWEB_H

#include <iostream>
#include <curl/curl.h>

typedef struct PostNode
{
	const std::string m_cvteurl;
	const std::string m_cookie;
	const std:: string m_postfilename;
	const std::string m_postfilepath;
	const std::string m_appversionname;
	const std::string m_appversion;
}PostNode;

class PostFiletoWeb
{
public:
	PostFiletoWeb(PostNode * const node);
	~PostFiletoWeb();

	void PostHttp();

	static void GetZipPath( std::string &path);
private:
	static const std::string S_SUFFIX_RENAME;

	PostNode *m_node;
};


#endif
