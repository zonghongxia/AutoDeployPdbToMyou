#include "PostFiletoWeb.h"

void PostHttp(const string cvte_url, const string cookie, const string postfilename, const string postfilepath, const string app_version_name, const string app_version)
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
		app_version_name.c_str(),
		CURLFORM_COPYCONTENTS,
		app_version.c_str(),
		CURLFORM_END
	);

	curl_formadd
	(
		&formpost,
		&lastptr,
		CURLFORM_COPYNAME,
		postfilename.c_str(),
		CURLFORM_FILE,
		postfilepath.c_str(),
		CURLFORM_END
	);

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, cvte_url.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);

		curl_formfree(formpost);
	}
}