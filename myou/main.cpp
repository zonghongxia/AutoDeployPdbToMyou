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

int main(int argc, char ** argv)
{
	std::string tp;
	double hour = 0.0;
	/*std::string tp("D://myouser/6.0/SeewoService/symbols");
	double hour = 6.9;*/
	for (int i = 1; i < argc; ++i)
	{
		if (i == 1)
		{
			tp = argv[i];
		}
		else if (i == 2)
		{
			hour = atof(argv[i]);
		}
		else
		{
			;
		}
	}
	if (!tp.empty() || 0.0 != hour)
	{
		GetSatisfyDiffHour satisfy(tp, hour);//Â·¾¶£¬Ê±¼ä
		std::vector<std::string> file_vec;
		satisfy.GetHourList(file_vec);
		satisfy.show(file_vec);
		PackagPost post;
		if (post.IsPostFiletoWeb())
		{
			post.PostToWeb(file_vec);
		}
		getchar();
	}
	return 0;
}
