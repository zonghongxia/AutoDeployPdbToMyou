#ifndef _GET_COOKIE_H
#define _GET_COOKIE_H
#include <fstream>  
#include <sstream>
#include <iostream>
#include <curl/curl.h>

using std::string;
using std::cout;
using std::endl;

static const char* SET_COOKIE_FILE = "Set-Cookie:";

int Get_SetCookie_Start_Index(const string ResponceHeader, const string substr);

int Get_SetCookie_End_Index(const string ResponceHeader, int StartIndex);//int end = strHeader.find_first_of("\r\n", start);

string Get_SetCookie_Data(const string ResponceHeader);

size_t CallBackWrite(const char *data, size_t size, int nmember, string  * strData);//写入数据的回调函数

string GetCookies(const string strurl, const string name_and_password, string content_type);


string readFileIntoString(string filename);

#endif
