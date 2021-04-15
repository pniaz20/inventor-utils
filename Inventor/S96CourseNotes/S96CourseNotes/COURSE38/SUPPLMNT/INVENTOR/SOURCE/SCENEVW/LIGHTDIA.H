// lightdia.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CLightDialog dialog

class CLightDialog : public CDialog
{
// Construction
public:

	SoSceneViewer* p_SV;
	CLightDialog(SoSceneViewer* p_SV); // modeless  constructor
	CLightDialog(CWnd* pParent = NULL);   // standard constructor

	BOOL Create();

// Dialog Data
	//{{AFX_DATA(CLightDialog)
	enum { IDD = IDD_DIALOG6 };
	CString	m_light;
	BOOL	m_iconon;
	BOOL	m_lighton;
	//}}AFX_DATA

	int m_lightlistIndex;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightDialog)
	afx_msg void OnCancelLightDialog();
	afx_msg void OnOKLightDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateDirectionallight();
	afx_msg void OnCreatePointlight();
	afx_msg void OnCreateSpotlight();
	afx_msg void OnDeleteLight();
	afx_msg void OnIconOn();
	afx_msg void OnLightOn();
	afx_msg void OnSelchangeLightList();
	afx_msg void OnInventorEditLight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
