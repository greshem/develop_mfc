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
	//上交所
	char						shopentime[50];				//	开盘时间
	char						shclosetime[50];				//	收盘时间
	char						shenableday[50];			//	收日线
	char						shenablemin[50];			//	收分钟线					
	//深交所
	char						szopentime[50];				//	开盘时间
	char						szclosetime[50];				//	收盘时间
	char						szenableday[50];			//	收日线
	char						szenablemin[50];			//	收分钟线
	char						tranfs[50];					// 转让特别转让
	//page 2
	//使用上海普通行情流驱动
	char						shanghainormalenable[50];
	char						shanghainormalmarketaddr[128];	//上海普通行情流驱动行情源地址
	char						shanghainormalmarketresponseport[50];//上海普通行情流驱动情源应答端口
	char						shanghainormalmarketpushport[50];//上海普通行情流驱动情源推送端口
	char						shanghainormalmarketusername[50];//上海普通行情流驱动情源登陆用户名
	char						shanghainormalmarketuserpsw[50];//上海普通行情流驱动情源登陆用户名
	//使用深圳普通行情流驱动
	char						shenzhennormalenable[50];
	
	char						shenzhen_normalmarketaddr[128];	//深圳普通行情流驱动行情源地址
	char						shenzhen_normalmarketresponseport[50];//深圳普通行情流驱动情源应答端口
	char						shenzhen_normalmarketpushport[50];//深圳普通行情流驱动情源推送端口
	char						shenzhen_normalmarketusername[50];//深圳普通行情流驱动情源登陆用户名
	char						shenzhen_normalmarketuserpsw[50];//深圳普通行情流驱动情源登陆用户名
	//page 3
	//使用Level2流驱动
	char						l2normalenable[50];
	
	char						l2marketaddr[128];				//Level2流驱行情源地址
	char						l2marketresponseport[50];		//Level2流驱行情源应答端口
	char						l2marketopushport[50];			//Level2流驱行情源推送端口
	char						l2marketusername[50];			//Level2流驱行情源登陆用户名
	char						l2marketuserpsw[50];			//Level2流驱行情源登陆密码
	
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
