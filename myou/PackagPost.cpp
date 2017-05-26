#include "PackagPost.h"

void PackagPost::PostToWeb(const std::vector<std::string> &file_vec,const std::string &appkey)
{
	std::map<std::string, std::string> apmap;
	ExtractPathandAppversion(apmap,file_vec);

	size_t tnum = myouurl.find(myouappkey);
	const_cast<std::string &>(myouurl).replace(tnum, myouappkey.size(), appkey);

	//获取cookie
	GetCookie  gcookie(getcookieurl, userpassword, contenttype);
	std::string cookie = gcookie.GetCookies();
	//std::cout << cookie << std::endl;

	std::vector<std::string> deletevector;//保存删除临时文件夹的路径

	for (std::map<std::string,std::string>::iterator it = apmap.begin();  it!=apmap.end();  ++it)
	{
		std::string path;//保存压缩文件的绝对路径
		std::string absolutepath;//保存压缩解压时的目录
		std::string unzippathbuf;
		std::string unzipbuf;
		unzippathbuf = (*it).second;//压缩文件所在的绝对路径
		path = unzippathbuf;
		//解压
		UNZIP unzip(unzippathbuf);//（压缩文件所在路径，自定义解压到什么路径否则压缩到当前项目所在目录下）
		unzip.CreateZip();

		//修改文件夹名字
		ChangePath lpath;
		lpath.GetUnzipFolderPath(path);//获取解压以后的文件夹所在的绝对路径
		lpath.CopyPath(absolutepath, path);
		lpath.GetZipFolderPath(absolutepath, G_GLOBAL_CHANGE_FOLDER_NAME);
		Rename rename(path, absolutepath);//old,new
		rename.RenameFolder();
		
		//压缩
		ZIP zip(absolutepath);
		zip.CreateMyZip();

		////上传文件到web
		std::string deletepath = absolutepath;
		//std::cout << deletepath << std::endl;
		PostFiletoWeb::GetZipPath(absolutepath);
		std::string postfilepath = absolutepath;
		std::string appversion = (*it).first;
		PostNode postnode = { myouurl,cookie, postfilename, postfilepath, appversionname, appversion };
		PostFiletoWeb posthttp(&postnode);
		posthttp.PostHttp();

		//删除临时生成的文件夹和压缩包
		/////////////////////////
		DeleteFolderorFile deletezip(postfilepath);
		deletezip.DeleteDir();


		DeleteFolderorFile deletefolder(deletepath);
		deletefolder.DeleteDir();
		deletevector.push_back(deletepath);
		/////////////////////////////////////////////
	}
	//删除空目录
	for (std::vector<std::string>::iterator it = deletevector.begin(); it != deletevector.end(); ++it)
	{
		DeleteFolderorFile tmp(*it);
		tmp.DeleteDir();
	}
}



void PackagPost::ExtractPathandAppversion(std::map<std::string, std::string> &apmap,const std::vector<std::string> &file_vec)
{
	for (std::vector<std::string>::const_iterator it = file_vec.begin(); it < file_vec.end(); ++it)
	{
		std::string tmp = *it;
		int i;
		for (i = tmp.size() - 1; i >= 0; --i)
		{
			if (tmp[i] == '\\')
			{
				break;
			}
		}
		std::string path = tmp;
		path += UNZIP_FILE_NAME;
		std::string appversion;
		appversion = tmp.assign(tmp, i+1, tmp.size()-1);
		apmap.insert(std::pair<std::string,std::string>(appversion,path));
	}
}