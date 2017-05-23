#ifndef _GET_COOKIE_H
#define _GET_COOKIE_H
#include <fstream>  
#include <sstream>
#include <iostream>
#include <curl/curl.h>

class GetCookie
{
public:
	GetCookie(const std::string &getcookieurl,const std::string &userpassword,const std::string &contenttype);
	~GetCookie();

	std::string GetCookies();

private:
	int GetSetCookieStartIndex(const std::string &ResponceHeader, const std::string &substr);
	int GetSetCookieEndIndex(const std::string &ResponceHeader, int StartIndex);
	std::string GetSetCookieData(const std::string &ResponceHeader);
	std::string readFileIntoString(std::string &filename);

	static size_t CallBackWrite(const char *pdata, size_t size, int nmember, std::string  *pstrData);//回调函数的libcurl接口
private:
	static const std::string S_SET_COOKIE_FILE;
	std::string m_getcookieurl;
	std::string m_userpassword;
	std::string m_contenttype;
};


#endif
