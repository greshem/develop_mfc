// L2DCDSetDlg.h : header file
//

#if !defined(AFX_L2DCDSETDLG_H__88308C3A_C1BB_4A38_9C4B_CF602D52ABF8__INCLUDED_)
#define AFX_L2DCDSETDLG_H__88308C3A_C1BB_4A38_9C4B_CF602D52ABF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Header.h"
/////////////////////////////////////////////////////////////////////////////
// CL2DCDSetDlg dialog

class CL2DCDSetDlg : public CDialog
{
// Construction
public:
	CL2DCDSetDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CL2DCDSetDlg)
	enum { IDD = IDD_L2DCDSET_DIALOG };
	CButton	m_ButtonMainDataPath;
	CString	m_strOpenTime;
	CString	m_strCloseTime;
	BOOL	m_bBackupDataLine;
	BOOL	m_bBackupMinuteLine;
	BOOL	m_bHKStockExchange;
	BOOL	m_bSpecialStockExchange;
	CString	m_strDelayMinute;
	CString	m_strReadDBFrequency;
	CString	m_strBackTrendDate;
	CString	m_strSourceDataPath;
	BOOL	m_bStartMode;
	CString	m_strL1RequestPort;
	CString	m_L1SendPacketPort;
	CString	m_L1UserName;
	CString	m_strL1Psw;
	CString	m_strDataFlowSrvAddr;
	CString	m_strDataFlowProxyPort;
	CString	m_strDataFlowUserName;
	CString	m_strDataFlowPwd;
	CString	m_strL2DataLoginAddr;
	CString	m_strL2DataLoginPort;
	CString	m_strL2DataSourcePath;
	CString	m_strL2DataRequestPort;
	CString	m_strL2DataPushPort;
	CString	m_strL2DataUserName;
	CString	m_strL2DataPsw;
	CString	m_strServerSetSrvPort;
	CString	m_strServerSetDealDataCount;
	CString	m_strServerSetComUnitCount;
	CString	m_strServerSetMaxLinkCount;
	CString	m_strMarketCount;
	CString	m_strMainDataPath;
	int		m_iMarketSet;
	int		m_iDCDSendPacket;
	int		m_iServerSetComProtocol;
	int		m_iDataFlowProxy;
	int		m_iL1MarketSet;
	int		m_iHKRecvPacket;
	int		m_iJimiDogMode;
	BOOL	m_bEnableShort;
	CString	m_strBackTrendMinute;
	CString	m_strNetWorkNumber;
	CString	m_strNodeAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CL2DCDSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	int	 LoadDefaultConfig();
	int	 SaveL2DCDCfg();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CL2DCDSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditOpenTime();
	afx_msg void OnChangeEditCloseTime();
	afx_msg void OnCheckBackupDataLime();
	afx_msg void OnCheckBackupMinuteLine();
	afx_msg void OnEditchangeComboMarketSet();
	afx_msg void OnDropdownComboMarketSet();
	afx_msg void OnCheckHkStockExchange();
	afx_msg void OnCheckSpecialStockExchange();
	afx_msg void OnEditchangeComboDcdSendPacket();
	afx_msg void OnDropdownComboDcdSendPacket();
	afx_msg void OnEditchangeComboHkRecvPacket();
	afx_msg void OnDropdownComboHkRecvPacket();
	afx_msg void OnChangeEditDelayMinute();
	afx_msg void OnChangeEditReadDbFrequency();
	afx_msg void OnChangeEditBackTrendDate();
	afx_msg void OnEditchangeComboL1MarketSet();
	afx_msg void OnDropdownComboL1MarketSet();
	afx_msg void OnChangeEditSourceDataPath();
	afx_msg void OnCheckStartMode();
	afx_msg void OnChangeEditL1RequestPort();
	afx_msg void OnChangeEditL1SendPacketPort();
	afx_msg void OnChangeEditL1UserNmae();
	afx_msg void OnChangeEditL1Psw();
	afx_msg void OnEditchangeComboDataFlowProxy();
	afx_msg void OnDropdownComboDataFlowProxy();
	afx_msg void OnChangeEditDataFlowSrvAddr();
	afx_msg void OnChangeEditDataFlowProxyPort();
	afx_msg void OnChangeEditDataFlowUserName();
	afx_msg void OnChangeEditDataFlowPwd();
	afx_msg void OnChangeEditL2DataLoginAddr();
	afx_msg void OnChangeEditL2DataLoginPort();
	afx_msg void OnChangeEditL2DataSourcePath();
	afx_msg void OnChangeEditL2DataRequestPort();
	afx_msg void OnChangeEditL2DataPushPort();
	afx_msg void OnChangeEditL2DataUserName();
	afx_msg void OnChangeEDITL2DATAPsw();
	afx_msg void OnChangeEdit1ServerSetSrvProt();
	afx_msg void OnChangeEditServerSetDealDataCount();
	afx_msg void OnChangeEditServerSetComUnitCount();
	afx_msg void OnChangeEditServerSetMaxLinkCount();
	afx_msg void OnButtonMainDataPath();
	afx_msg void OnChangeEditMainDataPath();
	afx_msg void OnEditchangeComboServerSetComProtocol();
	afx_msg void OnDropdownComboServerSetComProtocol();
	afx_msg void OnChangeEditMarketCount();
	afx_msg void OnSelchangeComboMarketSet();
	afx_msg void OnSelchangeComboDcdSendPacket();
	afx_msg void OnSelchangeComboHkRecvPacket();
	afx_msg void OnSelchangeComboL1MarketSet();
	afx_msg void OnSelchangeComboDataFlowProxy();
	afx_msg void OnSelchangeComboServerSetComProtocol();
	virtual void OnOK();
	afx_msg void OnSelchangeComboJimiDogMode();
	afx_msg void OnCheckEnableShort();
	afx_msg void OnChangeEditBackTrendMinute();
	afx_msg void OnChangeEditNetWorkNumber();
	afx_msg void OnChangeEditNodeAddress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_L2DCDSETDLG_H__88308C3A_C1BB_4A38_9C4B_CF602D52ABF8__INCLUDED_)
