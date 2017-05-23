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
	std::string strRecvData;             //���ץȡ����html��ҳ
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
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, m_userpassword.c_str());//post�ϴ�������

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &strRecvData);          //��html���浽strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CallBackWrite);          //�ص�����
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, &strHeader);          //����Ӧͷ����Ϣ���浽strRecvData
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, CallBackWrite);          //�ص�����

	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0);//�Ƿ����������������֤���ϵ��Ƿ�һ��
	if (res == CURLE_OK) res = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0);//�Ƿ����������֤���Ƿ��������������֤������ȨCA�䷢��


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

std::string GetCookie::GetSetCookieData(const std::string &ResponceHeader)//���set-cookie�ֶε�����
{
	if (ResponceHeader.empty())
	{
		return std::string();
	}
	std::string l_tmp;
	int l_start = GetSetCookieStartIndex(ResponceHeader, S_SET_COOKIE_FILE);//���ResponceHeader��S_SET_COOKIE_FILE����ʼ�±�
	int l_end = GetSetCookieEndIndex(ResponceHeader, l_start);//���ResponceHeader��S_SET_COOKIE_FILE�Ľ����±�
	for (int i = l_start + 12; i <l_end; ++i)//12 = strlen("Set-Cookie: ");
	{
		l_tmp += ResponceHeader[i];
	}
	return l_tmp;
}

size_t GetCookie::CallBackWrite(const char *pdata, size_t size, int nmember, std::string  *pstrData)//д�����ݵĻص�����
{
	size_t l_sizes = size * nmember;
	pstrData->append(pdata, l_sizes);
	return l_sizes;
}

std::string GetCookie::readFileIntoString(std::string &filename)//���ļ������ݶ���String��
{
	std::ifstream l_ifile(filename.c_str());//���ļ����뵽ostringstream����buf��  
	std::ostringstream l_buf;
	char l_ch;
	while (l_buf  &&  l_ifile.get(l_ch))
	{
		l_buf.put(l_ch);
	}
	return l_buf.str();//������������buf�������ַ���  
}
