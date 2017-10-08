// L2DCDCfgInfo.cpp: implementation of the L2DCDCfgInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "L2DCDSet.h"
#include "L2DCDCfgInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

L2DCDCfgInfo::L2DCDCfgInfo()
{
	m_pL2DCDCfgData = new L2DCDCfgData();
}

L2DCDCfgInfo::~L2DCDCfgInfo()
{
	if (m_pL2DCDCfgData != NULL)
	{
		delete m_pL2DCDCfgData;
		m_pL2DCDCfgData = NULL;
	}
}
