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
#include "GetSatisfyDiffHour.h"


int main(int argc, char ** argv)//appkey,path,hour
{
	/*std::string tp;
	double hour = 0.0;
	std::string appkey;*///cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b D://myouser/6.0/SeewoService/symbols 1
	std::string appkey("cf167a622948a3b42a7d7aacfcf3dd64f6e4d81b");
	std::string tp("D://myouser/6.0/SeewoService/symbols");
	double hour = 3;
	
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
		else if(i == 3)
		{
			hour = atof(argv[i]);
		}
	}
	if (!tp.empty() || 0.0 != hour)
	{
		GetSatisfyDiffHour satisfy(tp, hour);//Â·¾¶£¬Ê±¼ä
		std::vector<std::string> file_vec;
		satisfy.GetHourList(file_vec);
		satisfy.show(file_vec);
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
	//getchar();
	return 0;
}
