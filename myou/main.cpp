#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <fstream>  
#include <sstream>
#include <vector>
#include "PackagPost.h"
#include "GetRangeFolder.h"


int main(int argc, char ** argv)//appkey,path,range1,range2
{
	//cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b D://myouser/6.0/SeewoService/symbols 6.0.8.5551 6.0.8.5600
	/*std::string appkey("cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b");
	std::string tp("D://myouser/6.0/SeewoService/symbols");
	std::string range1("6.0.8.5551");
	std::string range2("6.0.8.5600");*/
	std::string appkey;
	std::string tp;
	std::string range1;
	std::string range2;

	for (int i = 1; i < argc; ++i)
	{
		if (i == 1)
		{
			appkey = argv[i];
		}
		else if (i == 2)
		{
			tp = argv[i];
		}
		else if (i == 3)
		{
			range1 = argv[i];
		}
		else if (i == 4)
		{
			range2 = argv[i];
		}
	}
	if (!tp.empty())
	{
		GetRangeFolder folder(tp, range1, range2);
		std::vector<std::string> file_vec;
		folder.GetPathtoVec(file_vec);
		folder.show(file_vec);
		if (!file_vec.empty())
		{
			PackagPost post;
			post.PostToWeb(file_vec, appkey);
		}
		else
		{
			std::cout << "No File Can Post" << std::endl;
		}
	}
	return 0;
}
