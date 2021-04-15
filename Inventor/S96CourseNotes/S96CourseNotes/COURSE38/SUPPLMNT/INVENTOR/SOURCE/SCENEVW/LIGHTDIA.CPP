// lightdia.cpp : implementation file
//

#include "stdafx.h"
#include "SceneVw.h"
#include "SoSV.h"
#include "lightdia.h"
#include "svDefMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightDialog dialog


CLightDialog::CLightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLightDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightDialog)
	m_light = _T("");
	m_iconon = FALSE;
	m_lighton = FALSE;
	//}}AFX_DATA_INIT

	p_SV = NULL;
}


CLightDialog::CLightDialog(SoSceneViewer* pView)
	: CDialog()
{
	p_SV = pView;
}


BOOL CLightDialog::Create()
{
	return CDialog::Create(CLightDialog::IDD);
}


void CLightDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightDialog)
	DDX_LBString(pDX, IDC_LIGHT_LIST, m_light);
	DDX_Check(pDX, IDC_ICON_ON, m_iconon);
	DDX_Check(pDX, IDC_LIGHT_ON, m_lighton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightDialog, CDialog)
	//{{AFX_MSG_MAP(CLightDialog)
	ON_BN_CLICKED(IDCANCEL, OnCancelLightDialog)
	ON_BN_CLICKED(IDOK, OnOKLightDialog)
	ON_BN_CLICKED(IDC_CREATE_DIRECTIONALLIGHT, OnCreateDirectionallight)
	ON_BN_CLICKED(IDC_CREATE_POINTLIGHT, OnCreatePointlight)
	ON_BN_CLICKED(IDC_CREATE_SPOTLIGHT, OnCreateSpotlight)
	ON_BN_CLICKED(IDC_DELETE_LIGHT, OnDeleteLight)
	ON_BN_CLICKED(IDC_ICON_ON, OnIconOn)
	ON_BN_CLICKED(IDC_LIGHT_ON, OnLightOn)
	ON_LBN_SELCHANGE(IDC_LIGHT_LIST, OnSelchangeLightList)
	ON_BN_CLICKED(ID_INVENTOR_EDIT_LIGHT_ATTR, OnInventorEditLight )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLightDialog message handlers

void CLightDialog::OnCancelLightDialog() 
{
	if (p_SV != NULL) {
		p_SV->PostMessage(WM_LIGHT_GOODBYE, IDCANCEL);
	}
	
}

void CLightDialog::OnOKLightDialog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (p_SV != NULL) {
		p_SV->PostMessage(WM_LIGHT_GOODBYE, IDOK);
	}
	
}

BOOL CLightDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lightlistIndex = -1;
	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);

	// get headlight data 
	pLB->InsertString(-1, p_SV->m_pHeadlightData->name);

	// get any other lights in the scene
	for (int i=0; i < p_SV->m_lightDataList.getLength(); i++ ) {
		SvLightData *data = (SvLightData *) p_SV->m_lightDataList[i];
	 	pLB->InsertString(-1, data->name);
	}

	pLB->SetCurSel(0);

	// light ON checkbox for headlight
	CButton *pB = (CButton *) GetDlgItem(IDC_LIGHT_ON);
	if (p_SV->m_pHeadlightData->lightON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	// icon ON checkbox	for headlight
	pB = (CButton *) GetDlgItem(IDC_ICON_ON);
	if (p_SV->m_pHeadlightData->iconON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLightDialog::OnCreateDirectionallight() 
{
	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);
	p_SV->OnLightingDirectlight();

  	// get the count so we know where to insert
	m_lightlistIndex = pLB->GetCount() - 1;

	SvLightData *data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];

	pLB->InsertString(-1, data->name);
	// light ON checkbox
	CButton *pB = (CButton *) GetDlgItem(IDC_LIGHT_ON);
	if (data->lightON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	// icon ON checkbox
	pB = (CButton *) GetDlgItem(IDC_ICON_ON);
	if (data->iconON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	pLB->SetCurSel(m_lightlistIndex + 1);


}

void CLightDialog::OnCreatePointlight() 
{

	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);
	p_SV->OnLightingPointlight();

	// get the count so we know where to insert
	m_lightlistIndex = pLB->GetCount() - 1;

	SvLightData *data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];

	pLB->InsertString(-1, data->name);
	// light ON checkbox
	CButton *pB = (CButton *) GetDlgItem(IDC_LIGHT_ON);
	if (data->lightON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	// icon ON checkbox
	pB = (CButton *) GetDlgItem(IDC_ICON_ON);
	if (data->iconON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	pLB->SetCurSel(m_lightlistIndex + 1);
	
}

void CLightDialog::OnCreateSpotlight() 
{
	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);
	p_SV->OnLightingSpotlight();

	// get the count so we know where to insert
	m_lightlistIndex = pLB->GetCount() - 1;

	SvLightData *data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];

	pLB->InsertString(-1, data->name);
	// light ON checkbox
	CButton *pB = (CButton *) GetDlgItem(IDC_LIGHT_ON);
	if (data->lightON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	// icon ON checkbox
	pB = (CButton *) GetDlgItem(IDC_ICON_ON);
	if (data->iconON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	pLB->SetCurSel(m_lightlistIndex + 1);


}

void CLightDialog::OnDeleteLight() 
{
   	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);
	m_lightlistIndex = pLB->GetCurSel() - 1;
	if ( m_lightlistIndex >= 0) { // selection is valid light not headlight

		// Delete the current selection
		SvLightData *data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];
		p_SV->RemoveLight( data );
		pLB->DeleteString(m_lightlistIndex + 1);
		pLB->SetCurSel(m_lightlistIndex);
		OnSelchangeLightList();
	 }
}

void CLightDialog::OnIconOn() 
{
	SvLightData *data;

	if (m_lightlistIndex >= 0) { // not headlight case

	   	data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];

		if (data->iconON) {
			p_SV->EditLight( data, 0);
			data->iconON = 0;
		} else {
			p_SV->EditLight( data, 1);
			data->iconON = 1;
		}
	} else { // headlight case

		CButton *pB = (CButton *) GetDlgItem(IDC_ICON_ON);
		pB->SetCheck(0); // FORCE no icon

	}

}

void CLightDialog::OnLightOn() 
{
	SvLightData *data;

	if (m_lightlistIndex < 0) // headlight case
		data = p_SV->m_pHeadlightData;
	else
	   	data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];

	if (data->lightON) {
		 p_SV->TurnLightOnOff( data, 0);
		 data->lightON = 0;
	} else {
		 p_SV->TurnLightOnOff( data, 1);
		 data->lightON = 1;
	}

}

void CLightDialog::OnSelchangeLightList() 
{
	SvLightData* data;
	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);
	m_lightlistIndex = pLB->GetCurSel() - 1;

	if (m_lightlistIndex < 0) // headlight case
		data = p_SV->m_pHeadlightData;
    else
	   	data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];

	// light ON checkbox
	CButton *pB = (CButton *) GetDlgItem(IDC_LIGHT_ON);
	if (data->lightON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

	// icon ON checkbox
	pB = (CButton *) GetDlgItem(IDC_ICON_ON);
	if (data->iconON)
		pB->SetCheck(1);
	else
		pB->SetCheck(0);

}

void CLightDialog::OnInventorEditLight() 
{
	SvLightData* data;
	CListBox *pLB = (CListBox *) GetDlgItem(IDC_LIGHT_LIST);
	m_lightlistIndex = pLB->GetCurSel() - 1;

	if (m_lightlistIndex < 0){ // headlight case
		data = p_SV->m_pHeadlightData;
        p_SV->EditLight( data, TRUE );
    }
	else {
	   	data = (SvLightData *) p_SV->m_lightDataList[m_lightlistIndex];
    	p_SV->EditLightColor(data);
    }

}


