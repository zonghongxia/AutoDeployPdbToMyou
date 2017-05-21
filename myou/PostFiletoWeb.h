#ifndef _POSTFILETOWEB_H
#define _POSTFILETOWEB_H

#include <iostream>
#include <curl/curl.h>

using std::string;

void PostHttp
(
	const string cvte_url,
	const string cookie, 
	const string postfilename, 
	const string postfilepath, 
	const string app_version_name, 
	const string app_version
);

#endif
