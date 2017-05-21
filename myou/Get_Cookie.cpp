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

size_t CallBackWrite(const char *data, size_t size, int nmember, string  * strData)//д�����ݵĻص�����
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
	string strRecvData;             //���ץȡ����html��ҳ
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
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, name_and_password.c_str());//post�ϴ�������

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strRecvData);          //��html���浽strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CallBackWrite);          //�ص�����
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, &strHeader);          //����Ӧͷ����Ϣ���浽strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, CallBackWrite);          //�ص�����

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);//�Ƿ����������������֤���ϵ��Ƿ�һ��
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);//�Ƿ����������֤���Ƿ��������������֤������ȨCA�䷢��


	if (res == CURLE_OK) res = curl_easy_perform(pCurl);
	curl_easy_cleanup(pCurl);

	string tmp = Get_SetCookie_Data(strHeader);
	/*cout << "tmp=********" << tmp << "*******" << endl;
	std::cout << "header" << strHeader << endl;*/
	return tmp;
}



string readFileIntoString(string filename)
{
	std::ifstream ifile(filename.c_str());//���ļ����뵽ostringstream����buf��  
	std::ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
	{
		buf.put(ch);
	}
	return buf.str();//������������buf�������ַ���  
}
