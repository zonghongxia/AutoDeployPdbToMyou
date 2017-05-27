#include "PostFiletoWeb.h"

const std::string PostFiletoWeb::S_SUFFIX_RENAME = ".zip";

bool PostFiletoWeb::m_btag = false;

PostFiletoWeb::PostFiletoWeb(PostNode * const node)
{
	if (NULL == node)
	{
		std::cout << "Please delivery vaild data" << std::endl;
		exit(1);
	}
	m_node = node;
}
PostFiletoWeb::~PostFiletoWeb()  
{
	m_btag = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int PostFiletoWeb::older_progress(void *p, double dltotal, double dlnow, double ultotal, double ulnow)
{
	if ((ulnow == ultotal && ulnow == 0) || (dltotal != 0 && dlnow != 0))
	{
		;
	}
	else if (ulnow == ultotal && dltotal == 0 && dlnow == 0 && !m_btag)
	{
		std::cout << std::endl;
		m_btag = true;
	}
	else
	{
		MoveCursor movecursor;
		COORD coord = movecursor.getxy();
		double tmpnum = (ulnow / ultotal) * 100.0;
		char input[10] = { 0 };
		sprintf(input, "%0.1f", tmpnum);
		input[strlen(input)] = '%';
		input[strlen(input)] = '\0';

		/*std::cout << input << std::endl;*/
		std::cout << input << "   ";
		movecursor.gotoxy(coord.X, coord.Y);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////

size_t PostFiletoWeb::CallBackWrite(const char *data, size_t size, int nmember, std::string  * strData)//写入数据的回调函数
{
	size_t sizes = size * nmember;
	strData->append(data, sizes);
	return sizes;
}
////////////////////////////////////////////////


void PostFiletoWeb::PostHttp()
{
	CURL* curl;
	CURLcode res;
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist* headerlist = NULL;

	curl_global_init(CURL_GLOBAL_ALL);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		m_node->m_appversionname.c_str(),
		CURLFORM_COPYCONTENTS,
		m_node->m_appversion.c_str(),
		CURLFORM_END
	);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		m_node->m_postfilename.c_str(),
		CURLFORM_FILE,
		m_node->m_postfilepath.c_str(),
		CURLFORM_END
	);

	std::string strHeader;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, m_node->m_cvteurl.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, m_node->m_cookie.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);

		//////////////////////////////////////////////////////////////////

		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &strHeader);          //将响应头部信息保存到strRecvData
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, CallBackWrite);

		/////////////////////////////////////////////////////////////////


		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

		/********************************************************************/
		//进度条的实现
		struct myprogress prog;

		prog.lastruntime = 0;
		prog.curl = curl;

		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);

		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, older_progress);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &prog);

		/********************************************************************/


		
		std::cout << "开始上传" << std::endl;
		res = curl_easy_perform(curl);//此函数以阻塞的方式进行了上传并返回服务器所返回的内容
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		curl_formfree(formpost);
		std::cout << std::endl;
		std::cout << "上传完毕" <<std:: endl;
		std::cout << std::endl;
	}
	std::cout<<strHeader<<std::endl;
}
void PostFiletoWeb::GetZipPath(std::string &path)
{
	path += S_SUFFIX_RENAME;
}
