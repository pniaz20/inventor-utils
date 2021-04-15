/*--------------------------------------------------------------
 *  This example program demonstrates a very simple Node Kit
 *
 *  Copyright 1995 Chris Buckalew   mod5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>

void
main(int , char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoShapeKit *sphereKit = new SoShapeKit;
  root->addChild(sphereKit);
  sphereKit->setPart("shape", new SoSphere);
  sphereKit->set("transform {scaleFactor 2.0  1.0  1.0}"
  "material {diffuseColor 0.5  0.5  1.0}");

  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));

  exViewer->setSceneGraph(root);
  exViewer->setTitle("Simple Node Kit Example");
  exViewer->viewAll();
  exViewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
