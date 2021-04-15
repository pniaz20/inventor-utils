/*-------------------------------------------------------------
 *  This example program creates and displays 2-D text
 *
 *  Copyright 1995 Chris Buckalew   mod5/10/96
 *-----------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoText2.h>

SoSeparator *
twoDText() 
{
  SoSeparator *text = new SoSeparator;
  // Choose a font
  SoFont *font = new SoFont;
  font->name.setValue("Times New Roman");
  font->size.setValue(72.0);
  text->addChild(font);

  SoText2 *word1 = new SoText2;
  word1->string = "Open Inventor";
  text->addChild(word1);

  return text;
}

void
main(int, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if(window == NULL) exit(1);

  SoGroup *root = new SoGroup;
  root->ref();

  root->addChild(twoDText());

  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("2D Text");
  exViewer->show();
  exViewer->viewAll();
  
  SoXt::show(window);
  SoXt::mainLoop();
}
