// EnumThreads.h: interface for the CThreads class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADS_H__DF8C3131_6EC5_4F7D_8208_DA1EF509190B__INCLUDED_)
#define AFX_THREADS_H__DF8C3131_6EC5_4F7D_8208_DA1EF509190B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <winperf.h>
#include <stdlib.h>
#include <winperf.h>

#define PN_PROCESS					TEXT("Process")
#define PN_THREAD					TEXT("Thread")
#define PN_THREAD_CPU				TEXT("% Processor Time")
#define PN_THREAD_PRIV				TEXT("% Privileged Time")
#define INDEX_STR_LEN				10

typedef PERF_DATA_BLOCK             PERF_DATA,      *PPERF_DATA;
typedef PERF_OBJECT_TYPE            PERF_OBJECT,    *PPERF_OBJECT;
typedef PERF_INSTANCE_DEFINITION    PERF_INSTANCE,  *PPERF_INSTANCE;
typedef PERF_COUNTER_DEFINITION     PERF_COUNTER,   *PPERF_COUNTER;


struct _THREADS_INFO
{
	TCHAR	szTemp[100];
	int		PcntPRIV;
	int		PcntUSER;
};

class CThreads : public CObject
{
public:	
	PPERF_DATA RefreshPerfData (HKEY        hPerfKey,LPTSTR      szObjectIndex,PPERF_DATA  pData,DWORD       *pDataSize);
	BOOL GetThreadList(struct _THREADS_INFO * threadlist);
	PVOID CounterData (PPERF_INSTANCE pInst, PPERF_COUNTER pCount);
	PPERF_COUNTER FindCounter (PPERF_OBJECT pObject, DWORD TitleIndex);
	PPERF_COUNTER NextCounter (PPERF_COUNTER pCounter);
	PPERF_COUNTER FirstCounter (PPERF_OBJECT pObject);
	LPTSTR InstanceName (PPERF_INSTANCE pInst);
	PPERF_INSTANCE FindInstanceParent (PPERF_INSTANCE pInst, PPERF_DATA pData);
	PPERF_INSTANCE FindInstanceN (PPERF_OBJECT pObject, DWORD N);
	PPERF_INSTANCE NextInstance (PPERF_INSTANCE pInst);
	PPERF_INSTANCE FirstInstance (PPERF_OBJECT pObject);
	PPERF_OBJECT FindObjectN (PPERF_DATA pData, DWORD N);
	PPERF_OBJECT FindObject (PPERF_DATA pData, DWORD TitleIndex);
	PPERF_OBJECT NextObject (PPERF_OBJECT pObject);
	PPERF_OBJECT FirstObject (PPERF_DATA pData);
	CThreads();
	CThreads(DWORD nIndex);
	virtual ~CThreads();

private:
	DWORD			parentIndex;						//index of process
	PPERF_OBJECT	pObject;
	PPERF_DATA      gpPerfData;

	//PPERF_OBJECT    gpProcessObject;                    // pointer to process objects
	//PPERF_OBJECT    gpThreadObject;                     // pointer to thread objects
	//PPERF_OBJECT    gpThreadDetailsObject;              // pointer to thread detail objects
protected:
	DWORD GetPerfData    (HKEY        hPerfKey,LPTSTR      szObjectIndex,PPERF_DATA  *ppData,DWORD       *pDataSize);
	DWORD GetTitleIdx (LPTSTR Title[], DWORD LastIndex, LPTSTR Name);
	DWORD GetPerfTitleSz (HKEY    hKeyMachine,HKEY    hKeyPerf,LPTSTR  *TitleBuffer,LPTSTR  *TitleSz[],DWORD   *TitleLastIdx);
};

#endif // !defined(AFX_THREADS_H__DF8C3131_6EC5_4F7D_8208_DA1EF509190B__INCLUDED_)
