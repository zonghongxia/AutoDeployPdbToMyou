#ifndef _CONSTANT_H
#define _CONSTANT_H
#include <string>

const std::string G_GLOBAL_CHANGE_FOLDER_NAME = "symbols";
const std::string UNZIP_FILE_NAME = "\\sym.zip";

const std::string getcookieurl = "https://myou.cvte.com/api/in/auth/login";
const std::string userpassword("{\"loginName\":\"iip.fwq\", \"password\":\"11111111\"}");//设置用户名和密码
const std::string contenttype("Content-Type:application/json;charset=UTF-8");//设置头部信息的Content_Type字段

const std::string postfilename("symbol_file");
const std::string appversionname("app_version");
//const std::string url = "http://myou.cvte.com/api/in/applications/cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b/crashdumps/upload_symbols";

const std::string myouurl = "http://myou.cvte.com/api/in/applications/{appKey}/crashdumps/upload_symbols";

const std::string myouappkey = "{appKey}";

#endif
