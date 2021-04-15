/*-------------------------------------------------------------
 *  This example program creates and displays beveled 3-D text
 *
 *  Copyright 1995 Chris Buckalew   mod5/10/96
 *-----------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoProfileCoordinate2.h>
#include <Inventor/nodes/SoLinearProfile.h>
#include <Inventor/nodes/SoText3.h>

SoSeparator *
threeDText() 
{
  SoSeparator *text = new SoSeparator;

  const float pts[5][2] = {{0.0, 0.0}, {0.25, 0.25}, {0.5, 0.15}, {0.75, 0.25}, {1.0, 0.0}};
  const int indices[5] = {0, 1, 2, 3, 4};

  SoProfileCoordinate2 *profCoords = new SoProfileCoordinate2;
  profCoords->point.setValues(0, 5, pts);
  text->addChild(profCoords);

  SoLinearProfile *linearProf = new SoLinearProfile;
  linearProf->index.setValues(0, 5, indices);
  text->addChild(linearProf);

  SoMaterial *mat = new SoMaterial;
  mat->diffuseColor.setValue(0.5, 1.0, 1.0);
  text->addChild(mat);

  // Choose a font
  SoFont *font1 = new SoFont;
  font1->name.setValue("Times New Roman");
  font1->size.setValue(8.0);
  text->addChild(font1);

  SoText3 *word = new SoText3;
  word->string = "Open Inventor";
  word->parts = SoText3::ALL;
  text->addChild(word);

  SoFont *font2 = new SoFont;
  font2->name.setValue("Times New Roman");
  font2->size.setValue(0.1);
  text->addChild(font2);

  text->addChild(word);

  return text;
}

void
main(int, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if(window == NULL) exit(1);

  SoGroup *root = new SoGroup;
  root->ref();

  root->addChild(threeDText());

  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Beveled 3D Text");
  exViewer->show();
  exViewer->viewAll();
  
  SoXt::show(window);
  SoXt::mainLoop();
}
