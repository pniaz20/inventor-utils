// mytransf.cpp : implementation file
//

#include "stdafx.h"
#include "SceneVw.h"
#include "mytransf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyTransformDialog dialog


MyTransformDialog::MyTransformDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MyTransformDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyTransformDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyTransformDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyTransformDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyTransformDialog, CDialog)
	//{{AFX_MSG_MAP(MyTransformDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MyTransformDialog message handlers
