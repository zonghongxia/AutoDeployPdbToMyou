#include "PostFiletoWeb.h"

const std::string PostFiletoWeb::S_SUFFIX_RENAME = ".zip";

PostFiletoWeb::PostFiletoWeb(PostNode * const node)
{
	if (NULL == node)
	{
		std::cout << "Please delivery vaild data" << std::endl;
		exit(1);
	}
	m_node = node;
}
PostFiletoWeb::~PostFiletoWeb()   {}

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

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, m_node->m_cvteurl.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, m_node->m_cookie.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

		res = curl_easy_perform(curl);//此函数以阻塞的方式进行了上传并返回服务器所返回的内容
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		curl_formfree(formpost);
	}
}
void PostFiletoWeb::GetZipPath(std::string &path)
{
	path += S_SUFFIX_RENAME;
	/*strcat(path, S_SUFFIX_RENAME);
	path[strlen(path)] = '\0';*/
}
