#include "Get_Cookie.h"

int Get_SetCookie_Start_Index(const string ResponceHeader, const string substr)
{
	if (ResponceHeader.empty())
	{
		return -1;
	}
	return (ResponceHeader.find(substr));
}

int Get_SetCookie_End_Index(const string ResponceHeader, int StartIndex)//int end = strHeader.find_first_of("\r\n", start);
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

string Get_SetCookie_Data(const string ResponceHeader)
{
	if (ResponceHeader.empty())
	{
		return string();
	}
	string tmp;
	int start = Get_SetCookie_Start_Index(ResponceHeader, SET_COOKIE_FILE);
	int end = Get_SetCookie_End_Index(ResponceHeader, start);
	for (int i = start + 12; i <end; ++i)
	{
		tmp += ResponceHeader[i];
	}
	return tmp;
}

size_t CallBackWrite(const char *data, size_t size, int nmember, string  * strData)//写入数据的回调函数
{
	size_t sizes = size * nmember;
	strData->append(data, sizes);
	return sizes;
}

string GetCookies(const string strurl, const string name_and_password, string content_type)
{
	CURLcode res = CURLE_OK;
	CURL * pCurl;
	const char * pszUrl = strurl.c_str();
	string strRecvData;             //存放抓取到的html网页
	string strHeader;

	curl_global_init(CURL_GLOBAL_ALL);
	pCurl = curl_easy_init();
	if (pCurl == NULL)
	{
		std::cout << "pCurl init failed" << endl;
		return string();
	}

	struct curl_slist *headerlist = NULL;
	headerlist = curl_slist_append(headerlist, content_type.c_str());
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, headerlist);
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_URL, pszUrl);    //url
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, name_and_password.c_str());//post上传的内容

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strRecvData);          //将html保存到strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CallBackWrite);          //回调函数
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, &strHeader);          //将响应头部信息保存到strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, CallBackWrite);          //回调函数

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);//是否检测服务器的域名与证书上的是否一致
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);//是否检测服务器的证书是否由正规浏览器认证过的授权CA颁发的


	if (res == CURLE_OK) res = curl_easy_perform(pCurl);
	curl_easy_cleanup(pCurl);

	string tmp = Get_SetCookie_Data(strHeader);
	/*cout << "tmp=********" << tmp << "*******" << endl;
	std::cout << "header" << strHeader << endl;*/
	return tmp;
}



string readFileIntoString(string filename)
{
	std::ifstream ifile(filename.c_str());//将文件读入到ostringstream对象buf中  
	std::ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
	{
		buf.put(ch);
	}
	return buf.str();//返回与流对象buf关联的字符串  
}
