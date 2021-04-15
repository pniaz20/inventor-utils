// SrvrItem.h : interface of the COleDemoSrvrItem class
//
#include <Inventor/mfc/SoMfcSrvrItem.h>

class COleDemoSrvrItem : public SoMfcSrvrItem
{
	DECLARE_DYNAMIC(COleDemoSrvrItem)

// Constructors
public:
	COleDemoSrvrItem(COleDemoDoc* pContainerDoc);
	COleDemoSrvrItem(SoMfcView *pView, SoPathList *pPathList);

// Attributes
	COleDemoDoc* GetDocument() const
		{ return (COleDemoDoc*)SoMfcSrvrItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COleDemoSrvrItem)
	//}}AFX_VIRTUAL

// Implementation
public:
	~COleDemoSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

/////////////////////////////////////////////////////////////////////////////
