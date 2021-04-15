/*----------------------------------------------------------------
 *  This example program demonstrates Dragger Callbacks.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *----------------------------------------------------------------*/

#include <Inventor/engines/SoCompose.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>

#include <Inventor/draggers/SoTranslate1Dragger.h>

void
dragStartCB(void *mat, SoDragger *)
{
  ((SoMaterial *)mat)->diffuseColor.setValue(1.0, 0.5, 0.5);
}
  
void
dragEndCB(void *mat, SoDragger *)
{
  ((SoMaterial *)mat)->diffuseColor.setValue(0.5, 1.0, 1.0);
}
  
void
main(int argc, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoTranslate1Dragger *dragger = new SoTranslate1Dragger;
  root->addChild(dragger);
  dragger->translation.setValue(1,0,0);

  SoTransform *dragX = new SoTransform;
  dragX->translation.setValue(0,3,0);
  SoMaterial *mat = new SoMaterial;
  mat->diffuseColor.setValue(0.5, 1.0, 1.0);
  SoCube *cube = new SoCube;
  root->addChild(dragX);
  root->addChild(mat);
  root->addChild(cube);

  // SoDecomposeVec3f engine extracts dragger's x-component
  // The result is connected to cube's width.
  SoDecomposeVec3f *decomp = new SoDecomposeVec3f;
  decomp->vector.connectFrom(&dragger->translation);
  cube->width.connectFrom(&decomp->x);

  // add start and end callbacks
  dragger->addStartCallback(dragStartCB, mat);
  dragger->addFinishCallback(dragEndCB, mat);

  SoXtExaminerViewer *viewer 
     = new SoXtExaminerViewer(window);
  viewer->setSize(SbVec2s(640, 480));
  viewer->setSceneGraph(root);
  viewer->setTitle("Dragger Callbacks");
  viewer->viewAll();
  viewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
