// SdkLog.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tchar.h>
#include "SdkWriteLog.h"

#define LOG_FILENAME _T("sdk_log.log")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR buff[256] = _T("中华人民共和国");
	int i = 10;
	WriteLog(_T("%s--%d"),buff,i);
	return 0;
}

