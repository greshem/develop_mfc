#ifndef __PUBLIC__H__
#define __PUBLIC__H__

//字符串常量
#define	PROGFIELD		"PROGRAM"
#define	MSGFIELD		"MESSAGE"
#define	SHUTFIELD		"SHUTDOWN"
#define	OPTFIELD		"OPTION"
#define	MAILFIELD		"MAIL"
#define	MAILCHECKKEY	"checkmail"
#define	MAILINTERVALKEY	"interval"
#define	COUNTKEY		"count"
#define BKGPICKEY		"backgroundpicture"
#define	SHUTKEY			"shutdown"

#define REGKEYNAME		"remind"

//定时器时间间隔,毫秒
#define	INTERVAL		59500		/*提醒定时器时间间隔*/
#define	SHUTDOWN		50000		/*自动关机定时器间隔*/

//邮件检查
typedef struct __CHECK__MAIL
{
	char	mail[64];
	char	host[64];
	char	user[64];
	char	password[64];
	struct __CHECK__MAIL *next;
}CheckMail;

//应用程序提醒
typedef struct __PROGRAM__INFO
{
	char	Name[25];
	int		Kind;
	char	Checkday[8];
	char	Date[11];
	char	Time[6];
	char	Path[128];
	struct __PROGRAM__INFO *next;
}ProgramInfo;

//消息提醒
typedef struct __MESSAGE__INFO
{
	int		Kind;
	char	Checkday[8];
	char	Date[11];
	char	Time[6];
	char	Msg[256];
	struct __MESSAGE__INFO *next;
}MessageInfo;

//关闭进程
typedef struct __PROCESS__INFO
{
	char	PID[8];
	char	Name[32];
	char	Date[11];
	char	Time[6];
	struct __PROCESS__INFO *next;
}ProcessInfo;

template<typename T> int AddToList(T **alllist, T *last)
{
	T *head;
	if(*alllist == NULL)
	{
		*alllist = last;
	}
	else
	{
		head = *alllist;
		while(head->next != NULL)
		{
			head = head->next;
		}
		head->next = last;
		last->next = NULL;
	}
	return 0;
}

template<typename T> int GetListCount(T **alllist)
{
	int ncount = 0;
	T *last;

	last = *alllist;
	while(last != NULL)
	{
		ncount++;
		last = last->next;
	}
	return ncount;
}

template<typename T> int DelAllList(T **alllist)
{
	T *head, *last;
	head = *alllist;
	while(head != NULL)
	{
		last = head;
		head = last->next;
		free(last);
	}
	return 0;
}

template<typename T> int DelListNode(T **alllist, int pos)
{
	int i = 0;
	T *head, *last;
	
	head = *alllist;
	if(pos == 0)
	{
		*alllist = head->next;
		free(head);
	}
	else
	{
		while(i < pos)
		{
			last = head;
			head = last->next;
			i++;
		}
		last->next = head->next;
		free(head);
	}

	return 0;
}

template<typename T> T *GetListNode(T **alllist, int pos)
{
	int i = 0;
	T *posnode;
	posnode = *alllist;
	while(i < pos)
	{
		posnode = posnode->next;
		i++;
	}
	return posnode;
}

int Endecrypt_Mars(char *srcstr, char *dststr, int ed = 1);
int CheckStringToIntArray(char *str,int arr[7]);
int NumstringToChnstring(char *scheck, char *dststr);
int FormatCheckedString(const int *array, int nCheckedCount, char *dststr);
int StrToTime(char *sTime,COleDateTime* time);
int StrToDate(char *sDate,COleDateTime* date);
int StrToDateTime(char *sDatetime, COleDateTime *date);
void BeepPrompt(int nBeep);
int TimeToString(COleDateTime time, char * stime);
int DateToString(COleDateTime datetime, char * sdatetime);
int DateTimeToString(COleDateTime datetime, char *sdatetime);
int OnCloseProg();

int getfld(char * sour,char * des, int index, char ch = '|');

int GetRegValue(char *subkey, char *keyname, char *keyvalue, HKEY hKeyIn = HKEY_LOCAL_MACHINE);
int SetRegValue(char *subkey, char *keyname, char *keyvalue, HKEY hKeyIn = HKEY_LOCAL_MACHINE);
int DelRegKey(char *subkey, char *keyname, HKEY hKeyIn = HKEY_LOCAL_MACHINE);

#endif //__PUBLIC__H__
