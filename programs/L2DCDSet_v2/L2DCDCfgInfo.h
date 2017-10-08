// L2DCDCfgInfo.h: interface for the L2DCDCfgInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_L2DCDCFGINFO_H__85DE5C04_2593_43AE_AF5E_2D1ACEE77B1F__INCLUDED_)
#define AFX_L2DCDCFGINFO_H__85DE5C04_2593_43AE_AF5E_2D1ACEE77B1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Header.h"
typedef struct _L2DCDCfgData
{
	//page 1
	//�Ͻ���
	char						shopentime[50];				//	����ʱ��
	char						shclosetime[50];				//	����ʱ��
	char						shenableday[50];			//	������
	char						shenablemin[50];			//	�շ�����					
	//���
	char						szopentime[50];				//	����ʱ��
	char						szclosetime[50];				//	����ʱ��
	char						szenableday[50];			//	������
	char						szenablemin[50];			//	�շ�����
	char						tranfs[50];					// ת���ر�ת��
	//page 2
	//ʹ���Ϻ���ͨ����������
	char						shanghainormalenable[50];
	char						shanghainormalmarketaddr[128];	//�Ϻ���ͨ��������������Դ��ַ
	char						shanghainormalmarketresponseport[50];//�Ϻ���ͨ������������ԴӦ��˿�
	char						shanghainormalmarketpushport[50];//�Ϻ���ͨ������������Դ���Ͷ˿�
	char						shanghainormalmarketusername[50];//�Ϻ���ͨ������������Դ��½�û���
	char						shanghainormalmarketuserpsw[50];//�Ϻ���ͨ������������Դ��½�û���
	//ʹ��������ͨ����������
	char						shenzhennormalenable[50];
	
	char						shenzhen_normalmarketaddr[128];	//������ͨ��������������Դ��ַ
	char						shenzhen_normalmarketresponseport[50];//������ͨ������������ԴӦ��˿�
	char						shenzhen_normalmarketpushport[50];//������ͨ������������Դ���Ͷ˿�
	char						shenzhen_normalmarketusername[50];//������ͨ������������Դ��½�û���
	char						shenzhen_normalmarketuserpsw[50];//������ͨ������������Դ��½�û���
	//page 3
	//ʹ��Level2������
	char						l2normalenable[50];
	
	char						l2marketaddr[128];				//Level2��������Դ��ַ
	char						l2marketresponseport[50];		//Level2��������ԴӦ��˿�
	char						l2marketopushport[50];			//Level2��������Դ���Ͷ˿�
	char						l2marketusername[50];			//Level2��������Դ��½�û���
	char						l2marketuserpsw[50];			//Level2��������Դ��½����
	
}L2DCDCfgData;
class L2DCDCfgInfo  
{
public:
	L2DCDCfgInfo();
	virtual ~L2DCDCfgInfo();
private:
	L2DCDCfgData*	m_pL2DCDCfgData;
};

#endif // !defined(AFX_L2DCDCFGINFO_H__85DE5C04_2593_43AE_AF5E_2D1ACEE77B1F__INCLUDED_)
