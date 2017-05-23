#include "Get_Cookie.h"


const std::string GetCookie::S_SET_COOKIE_FILE = "Set-Cookie:";

GetCookie::GetCookie(const std::string &getcookieurl, const std::string &userpassword, const std::string &contenttype)
{
	m_getcookieurl = getcookieurl;
	m_userpassword = userpassword;
	m_contenttype = contenttype;
}
GetCookie::~GetCookie(){}

std::string GetCookie::GetCookies()
{
	CURLcode res = CURLE_OK;
	CURL * pCurl;
	const char * pszUrl = m_getcookieurl.c_str();
	std::string strRecvData;             //存放抓取到的html网页
	std::string strHeader;

	curl_global_init(CURL_GLOBAL_ALL);
	pCurl = curl_easy_init();
	if (pCurl == NULL)
	{
		std::cout << "l_pCurl init failed" << std::endl;
		return std::string();
	}

	struct curl_slist* l_headerlist = NULL;
	l_headerlist = curl_slist_append(l_headerlist, m_contenttype.c_str());
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, l_headerlist);
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_URL, pszUrl);    //url
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, m_userpassword.c_str());//post上传的内容

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strRecvData);          //将html保存到strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CallBackWrite);          //回调函数
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, &strHeader);          //将响应头部信息保存到strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, CallBackWrite);          //回调函数

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);//是否检测服务器的域名与证书上的是否一致
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);//是否检测服务器的证书是否由正规浏览器认证过的授权CA颁发的


	if (res == CURLE_OK) res = curl_easy_perform(pCurl);
	curl_easy_cleanup(pCurl);

	std::string l_tmp = GetSetCookieData(strHeader);
	/*cout << "tmp=********" << tmp << "*******" << endl;
	std::cout << "header" << strHeader << endl;*/
	return l_tmp;
}

int GetCookie::GetSetCookieStartIndex(const std::string &ResponceHeader, const std::string &substr)
{
	if (ResponceHeader.empty())
	{
		return -1;
	}
	return (ResponceHeader.find(substr));
}

int GetCookie::GetSetCookieEndIndex(const std::string &ResponceHeader, int StartIndex)//int end = strHeader.find_first_of("\r\n", start);
{
	if (ResponceHeader.empty())
	{
		return -1;
	}
	else
	{
		return ResponceHeader.find_first_of("\r\n", StartIndex);
	}
}

std::string GetCookie::GetSetCookieData(const std::string &ResponceHeader)//获得set-cookie字段的内容
{
	if (ResponceHeader.empty())
	{
		return std::string();
	}
	std::string l_tmp;
	int l_start = GetSetCookieStartIndex(ResponceHeader, S_SET_COOKIE_FILE);//获得ResponceHeader中S_SET_COOKIE_FILE的起始下标
	int l_end = GetSetCookieEndIndex(ResponceHeader, l_start);//获得ResponceHeader中S_SET_COOKIE_FILE的结束下表
	for (int i = l_start + 12; i <l_end; ++i)//12 = strlen("Set-Cookie: ");
	{
		l_tmp += ResponceHeader[i];
	}
	return l_tmp;
}

size_t GetCookie::CallBackWrite(const char *pdata, size_t size, int nmember, std::string  *pstrData)//写入数据的回调函数
{
	size_t l_sizes = size * nmember;
	pstrData->append(pdata, l_sizes);
	return l_sizes;
}

std::string GetCookie::readFileIntoString(std::string &filename)//将文件的内容读到String中
{
	std::ifstream l_ifile(filename.c_str());//将文件读入到ostringstream对象buf中  
	std::ostringstream l_buf;
	char l_ch;
	while (l_buf  &&  l_ifile.get(l_ch))
	{
		l_buf.put(l_ch);
	}
	return l_buf.str();//返回与流对象buf关联的字符串  
}
