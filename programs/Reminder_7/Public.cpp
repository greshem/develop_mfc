// public.cpp: implementation of the public.h
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Public.h"
#include "remind.h"
#include "./library/mars.h"

char m_sInifilename[128];	/*INI文件路径*/
char m_spath[128];			/*文件存放路径*/
int nBeep;					/*是否蜂鸣提示*/
int m_nIspicture;			/*有无背景图片*/

CheckMail *maillist;
ProgramInfo *proglist;
MessageInfo *msglist;
ProcessInfo *proclist;

int DateToString(COleDateTime datetime, char * sdatetime)
{
	//格式化日期字符串
	strcpy(sdatetime, datetime.Format(_T("%Y-%m-%d")));
	return 0;
}

int TimeToString(COleDateTime time, char * stime)
{
	//格式化时间字符串
	strcpy(stime, time.Format(_T("%H:%M")));
	return 0;
}

int DateTimeToString(COleDateTime datetime, char *sdatetime)
{
	//格式化日期时间字符串
	strcpy(sdatetime,datetime.Format(_T("%Y-%m-%d %H:%M")));
	return 0;
}

void BeepPrompt(int nBeep)
{
	if(nBeep)
	{
		Beep(50,500);
	}
}

int StrToDate(char *sDate, COleDateTime *date)
{
	//字符串转换为日期
	int nYear, nMonth, nDay;
	sscanf(sDate,"%d-%d-%d", &nYear, &nMonth, &nDay);
	date->SetDate(nYear, nMonth, nDay);
	return 1;
}

int StrToTime(char *sTime, COleDateTime *time)
{
	//if(sTime=="")
	//	return -1;
	//字符串转换为时间
	int nHour, nMinute, nSecond;
	sscanf(sTime,"%d:%d:%d", &nHour, &nMinute, &nSecond);
	time->SetTime(nHour, nMinute, 0);
	return 1;
}

int StrToDateTime(char *sDatetime, COleDateTime *date)
{
	int nYear, nMonth, nDay;
	int nHour, nMinute, nSecond;
	sscanf(sDatetime,"%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	date->SetDate(nYear, nMonth, nDay);
	date->SetTime(nHour, nMinute, 0);
	return 1;
}

int FormatCheckedString(const int *array,int nCheckedCount, char *dststr)
{
	//选择的日期转换成可保存的字符串
	int arr[7];

	for(int i=0;i<7;i++)
	{
		arr[i] = 0;
		for(int j=0;j<nCheckedCount;j++)
		{
			if(i==array[j])
			{
				arr[i] = i + 1;
				break;
			}
		}
	}
	sprintf(dststr, "%d%d%d%d%d%d%d",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6]);
	return 0;
}

int NumstringToChnstring(char *scheck, char *dststr)
{
	//保存的字符串转换成可显示的字符串
	if(strlen(scheck) != 7 && strlen(scheck) != 0)
	{
		MessageBox(NULL,"字符串转换出错！请检查Remind.ini文件","警告",MB_OK+MB_ICONEXCLAMATION);
		exit(0);
	}

	char cstr[7];
	strncpy(cstr,scheck,sizeof(cstr));

	for(int i=0;i<7;i++)
	{
		switch(cstr[i])
		{
		case '1':
			strcat(dststr, "日");
			break;
		case '2':
			strcat(dststr, "一");
			break;
		case '3':
			strcat(dststr, "二");
			break;
		case '4':
			strcat(dststr, "三");
			break;
		case '5':
			strcat(dststr, "四");
			break;
		case '6':
			strcat(dststr, "五");
			break;
		case '7':
			strcat(dststr, "六");
			break;
		default:
			break;
		}
	}
	return 0;
}

int CheckStringToIntArray(char *str, int arr[7])
{
	char cstr[8];
	strncpy(cstr,str,sizeof(cstr));

	for(int i=0;i<7;i++)
	{
		if(cstr[i]=='0')
			arr[i] = 0;
		else
			arr[i] = i + 1;
	}

	return 1;
}

int Endecrypt_Mars(char *srcstr, char *dststr, int ed)
{
	mars Mars;
	string enstr;
	enstr = Mars.encrypt(srcstr,ed);
	strcpy(dststr, enstr.c_str());
	return 0;
}

int getfld(char * sour,char * des, int index, char ch)
{
   char *p;
   int j, i, k, len;

   i = 0; j = 0; k = 0;

   p = sour;
   
   while( i < index )
   {
      if( p[j++] == ch ) i++; 
   }
   k = j;
   while( p[j++] != ch );
   
   len = j - k- 1;

   strncpy( des, p+k, len);
   des[len] = 0;

   return 0;
}

/***read key value from registry***/
int GetRegValue(char *subkey, char *keyname, char *keyvalue, HKEY hKeyIn)
{
	ULONG regsize = 0;
	HKEY  hKeyOut;
	LPBYTE pValue;

	if( ERROR_SUCCESS != RegOpenKeyEx(hKeyIn, subkey, 0, KEY_CREATE_LINK | KEY_WRITE | KEY_READ | KEY_NOTIFY, &hKeyOut))
	{
		return -1;
	}
	if(ERROR_SUCCESS != RegQueryValueEx(hKeyOut, keyname, NULL, NULL, NULL, &regsize))
	{
		return -1;
	}
	pValue = (LPBYTE)malloc(regsize);
	memset(pValue, 0x00, regsize);
	if(ERROR_SUCCESS != RegQueryValueEx(hKeyOut, keyname, NULL, NULL, pValue, &regsize))
	{
		return -1;
	}
	
	strcpy(keyvalue, (char *)pValue);
	free(pValue);
	pValue = NULL;
	RegCloseKey(hKeyOut);

	return 0;
}

/***set registry key value***/
int SetRegValue(char *subkey, char *keyname, char *keyvalue, HKEY hKeyIn)
{
	HKEY hKeyOut;
	if( ERROR_SUCCESS != RegOpenKeyEx(hKeyIn, subkey, 0, KEY_ALL_ACCESS, &hKeyOut))
	{
		return -1;
	}

	if (ERROR_SUCCESS != RegSetValueEx(hKeyOut,		// subkey handle 
            keyname,								// value name 
            0L,										// must be zero 
            REG_SZ,									// value type 
            (const BYTE*)keyvalue,					// pointer to value data 
            strlen(keyvalue) + 1))					// length of value data 
	{
        AfxMessageBox("Could not set the supported types."); 
		return -1;
	}
 
    RegCloseKey(hKeyOut); 

	return 0;
}

/***delete registry key***/
int DelRegKey(char *subkey, char *keyname, HKEY hKeyIn)
{
	HKEY hKeyOut;
	if( ERROR_SUCCESS != RegOpenKeyEx(hKeyIn, subkey, 0, KEY_ALL_ACCESS, &hKeyOut))
	{
		return -1;
	}

	if (ERROR_SUCCESS != RegDeleteValue(hKeyOut,keyname))
	{
        AfxMessageBox("Could not set the supported types."); 
		return -1;
	}
 
    RegCloseKey(hKeyOut);
	return 0;
}

int OnCloseProg()
{
	//格式化日期时间字符串
	char sDatetime[17];
	COleDateTime dShuttime = COleDateTime::GetCurrentTime();
	memset(sDatetime, 0, sizeof(sDatetime));
	strcpy(sDatetime, dShuttime.Format(_T("%Y-%m-%d %H:%M")));
	WritePrivateProfileString(SHUTFIELD,"LastShutTime",sDatetime,m_sInifilename);
	return 0;
}
