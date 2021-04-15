// SrvrItem.cpp : implementation of the COleDemoSrvrItem class
//

#include "stdafx.h"
#include "OleDemo.h"

#include "ODDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleDemoSrvrItem implementation

IMPLEMENT_DYNAMIC(COleDemoSrvrItem, SoMfcSrvrItem)

COleDemoSrvrItem::COleDemoSrvrItem(COleDemoDoc* pContainerDoc)
	: SoMfcSrvrItem(pContainerDoc)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}

COleDemoSrvrItem::COleDemoSrvrItem(SoMfcView *pView, SoPathList *pPathList)
	: SoMfcSrvrItem(pView, pPathList)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}


COleDemoSrvrItem::~COleDemoSrvrItem()
{
	// TODO: add cleanup code here
}

/////////////////////////////////////////////////////////////////////////////
// COleDemoSrvrItem diagnostics

#ifdef _DEBUG
void COleDemoSrvrItem::AssertValid() const
{
	SoMfcSrvrItem::AssertValid();
}

void COleDemoSrvrItem::Dump(CDumpContext& dc) const
{
	SoMfcSrvrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
