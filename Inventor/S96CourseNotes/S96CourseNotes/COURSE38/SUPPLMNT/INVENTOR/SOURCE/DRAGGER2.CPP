/*----------------------------------------------------------------
 *  This example program demonstrates the construction of a
 *  Simple Dragger.
 *
 *  This code creates a dragger and uses it to modify
 *  the width of a box.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *----------------------------------------------------------------*/

#include <Inventor/engines/SoCompose.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>

#include <Inventor/draggers/SoTranslate1Dragger.h>

void
main(int argc, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  // move in one direction only
  SoTranslate1Dragger *dragger = new SoTranslate1Dragger;
  root->addChild(dragger);
  dragger->translation.setValue(1,0,0);

  SoTransform *dragX = new SoTransform;
  SoCube *cube = new SoCube;
  root->addChild(dragX);
  root->addChild(cube);
  dragX->translation.setValue(0,3,0);

  // SoDecomposeVec3f engine extracts dragger's x-component
  // The result is connected to cube's width.
  SoDecomposeVec3f *decomp = new SoDecomposeVec3f;
  decomp->vector.connectFrom(&dragger->translation);
  cube->width.connectFrom(&decomp->x);

  SoXtExaminerViewer *viewer 
     = new SoXtExaminerViewer(window);
  viewer->setSize(SbVec2s(640, 480));
  viewer->setSceneGraph(root);
  viewer->setTitle("Simple Dragger");
  viewer->viewAll();
  viewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
