#include "GetDiffHour.h"

GetDiffHour::GetDiffHour(const std::string &path)
{
	m_path = path;
}

double GetDiffHour::GetPathDiffHour()
{
	int iresult;
	struct _stat buf;
	iresult = _stat(m_path.c_str(), &buf);
	long* m_sencodes = (long *)&buf.st_ctime;
	struct tm* m_localTime = localtime((const time_t *)m_sencodes);

	long* mptr_currentSeconds = new long;
	time((time_t  *)mptr_currentSeconds);
	m_localTime = localtime((const time_t *)mptr_currentSeconds);

	double diffSeconds = difftime(*mptr_currentSeconds, *m_sencodes);

	const int SECONDS_OF_HOUR = 3600;
	double diffhour = diffSeconds / SECONDS_OF_HOUR;
	return diffhour;
}
GetDiffHour::~GetDiffHour() {}