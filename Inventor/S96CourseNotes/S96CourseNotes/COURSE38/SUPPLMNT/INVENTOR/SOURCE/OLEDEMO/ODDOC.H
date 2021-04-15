// OleDemoDoc.h : interface of the COleDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include <Inventor/mfc/SoMfcOleSrvrDoc.h>

class COleDemoSrvrItem;

class COleDemoDoc : public SoMfcOleSrvrDoc
{
protected: // create from serialization only
	COleDemoDoc();
	DECLARE_DYNCREATE(COleDemoDoc)


//attributes
public:
	COleDemoSrvrItem* GetEmbeddedItem()
		{ return (COleDemoSrvrItem*)SoMfcOleSrvrDoc::GetEmbeddedItem(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COleDemoDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COleDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COleDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
