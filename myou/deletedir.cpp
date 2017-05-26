#include "deletedir.h"

DeleteFolderorFile::DeleteFolderorFile(std::string &path)
{
	m_pDir = path;
}
bool DeleteFolderorFile::DeleteDir()
{
	if (m_pDir.empty())
	{
		return false;
	}
	//判断是文件还是文件夹
	struct _stat sfile;
	if (_stat(m_pDir.c_str(), &sfile) == 0)
	{
		if (_S_IFREG&sfile.st_mode)
		{
			if (DeleteFile(m_pDir.c_str()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (_S_IFDIR & sfile.st_mode)
		{

			if (DeleteDirectory(m_pDir.c_str()))////////////////////
			{
				return true;
			}
		}
	}
	return true;
}

bool DeleteFolderorFile::DeleteDirectory(LPCTSTR lpszDir, bool noRecycleBin)
{
	int len = _tcslen(lpszDir);
	TCHAR *pszFrom = new TCHAR[len + 2];
	_tcscpy(pszFrom, lpszDir);
	pszFrom[len] = 0;
	pszFrom[len + 1] = 0;


	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL;			// no status display
	fileop.wFunc = FO_DELETE;	// delete operation
	fileop.pFrom = pszFrom;		// source file name as double null terminated string
	fileop.pTo = NULL;			// no destination needed
	fileop.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;	// do not prompt the user

	if (!noRecycleBin)
		fileop.fFlags |= FOF_ALLOWUNDO;

	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle = NULL;
	fileop.hNameMappings = NULL;

	int ret = SHFileOperation(&fileop);

	delete[] pszFrom;

	return (ret == 0);
}
