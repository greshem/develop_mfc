// SdkLog.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tchar.h>
#include "SdkWriteLog.h"

#define LOG_FILENAME _T("sdk_log.log")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR buff[256] = _T("�л����񹲺͹�");
	int i = 10;
	WriteLog(_T("%s--%d"),buff,i);
	return 0;
}

