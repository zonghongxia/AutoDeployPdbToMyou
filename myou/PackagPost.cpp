#include "PackagPost.h"


bool PackagPost::IsPostFiletoWeb()
{
	int ch;
	std::cout << "���������Ƿ�Ը���ϴ������ļ�,0:��ʾ�񣻣�0����ʾ��" << std::endl;
	std::cin >> ch;
	if (ch)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PackagPost::PostToWeb(const std::vector<std::string> &file_vec)
{
	std::map<std::string, std::string> apmap;
	ExtractPathandAppversion(apmap,file_vec);

	for (std::map<std::string,std::string>::iterator it = apmap.begin();  it!=apmap.end();  ++it)
	{
		//��ȡcookie
		GetCookie  gcookie(getcookieurl, userpassword, contenttype);
		std::string cookie = gcookie.GetCookies();
		//std::cout << cookie << std::endl;

		std::string path;//����ѹ���ļ��ľ���·��
		std::string absolutepath;//����ѹ����ѹʱ��Ŀ¼
		std::string unzippathbuf;
		std::string unzipbuf;
		unzippathbuf = (*it).second;//ѹ���ļ����ڵľ���·��
		path = unzippathbuf;

		//��ѹ
		UNZIP unzip(unzippathbuf);//��ѹ���ļ�����·�����Զ����ѹ��ʲô·������ѹ������ǰ��Ŀ����Ŀ¼�£�
		unzip.CreateZip();

		//�޸��ļ�������
		ChangePath lpath;
		lpath.GetUnzipFolderPath(path);//��ȡ��ѹ�Ժ���ļ������ڵľ���·��
		lpath.CopyPath(absolutepath, path);
		lpath.GetZipFolderPath(absolutepath, G_GLOBAL_CHANGE_FOLDER_NAME);
		Rename rename(path, absolutepath);//old,new
		rename.RenameFolder();

		//ѹ��
		ZIP zip(absolutepath);
		zip.CreateMyZip();

		////�ϴ��ļ���web
		PostFiletoWeb::GetZipPath(absolutepath);
		std::string postfilepath = absolutepath;
		std::string appversion = (*it).first;
		PostNode postnode = { url,cookie, postfilename, postfilepath, appversionname, appversion };
		PostFiletoWeb posthttp(&postnode);
		posthttp.PostHttp();
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