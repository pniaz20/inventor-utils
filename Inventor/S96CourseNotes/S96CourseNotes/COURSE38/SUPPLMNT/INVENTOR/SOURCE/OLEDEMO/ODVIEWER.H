#include <Inventor/mfc/viewers/SoMfcExamViewer.h>


class SoSelection;
class SoBoxHighlightRenderAction;

class COleDemoViewer : public SoMfcExaminerViewer 
{
  public:
 	
  DECLARE_DYNCREATE(COleDemoViewer)

  COleDemoViewer();
  ~COleDemoViewer();
  SoSelection *GetSelectionNode() { return m_pSelection;}

  virtual void    SetSceneGraph(SoNode *pNewScene);

  private :

  SoSelection *m_pSelection;
  SoBoxHighlightRenderAction *m_pHighlightRA;
  SoSeparator *m_pPrevScene;
};