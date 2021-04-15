// OleDemoView.h : interface of the COleDemoView class
//
/////////////////////////////////////////////////////////////////////////////
#include <Inventor/mfc/SoMfcView.h>
#include <Inventor/mfc/SoMfcClipboardhelper.h>

class COleDemoView : public SoMfcView
{
protected: // create from serialization only
	COleDemoView();
	DECLARE_DYNCREATE(COleDemoView)

// Attributes
public:
	COleDemoDoc* GetDocument();

// Operations
protected:

	COleDropTarget   m_dropTarget;
	DROPEFFECT       m_prevDropEffect;

	virtual BOOL OnDrop(COleDataObject* pDataObject,
		DROPEFFECT dropEffect, CPoint point);
	
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
		DWORD grfKeyState, CPoint point);
	
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
		DWORD grfKeyState, CPoint point);
	
	virtual void OnDragLeave();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COleDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COleDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    // Paste callback - invoked when paste data transfer is complete
    void    	    	PasteDone(SoPathList *pathList);
    static void    		PasteDoneCB(void *userData, SoPathList *pathList);


private :
	SoMfcClipboardHelper  *m_pClipBoard;
	void DoPasteNative(COleDataObject *pDataObject);

// Generated message map functions
protected:
	//{{AFX_MSG(COleDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg void OnInventorCopy();
		afx_msg void OnInventorPaste();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnCancelEditSrvr();
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OleDemoView.cpp
inline COleDemoDoc* COleDemoView::GetDocument()
   { return (COleDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
