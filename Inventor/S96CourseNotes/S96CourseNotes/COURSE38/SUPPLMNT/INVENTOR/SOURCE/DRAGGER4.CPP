/*----------------------------------------------------------------
 *  This example program demonstrates Multiple Draggers.
 *
 *  This code creates several draggers and uses them to modify
 *  the dimensions of a box.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *----------------------------------------------------------------*/

#include <Inventor/engines/SoCalculator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

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

  SoSeparator *xDrag = new SoSeparator;
  SoSeparator *yDrag = new SoSeparator;
  SoSeparator *zDrag = new SoSeparator;
  SoTransform *xDragX = new SoTransform;
  SoTransform *yDragX = new SoTransform;
  SoTransform *zDragX = new SoTransform;
  
  // these will place the draggers in the right places
  xDragX->translation.setValue(0.0, -2.0, 4.0);
  yDragX->translation.setValue(-4.0, 0.0, 4.0);
  yDragX->rotation.setValue(SbVec3f(0, 0, 1), M_PI/2);
  zDragX->translation.setValue(-4.0, -2.0, 0.0);
  zDragX->rotation.setValue(SbVec3f(0, 1, 0), M_PI/2);
  xDrag->addChild(xDragX);
  yDrag->addChild(yDragX);
  zDrag->addChild(zDragX);

  // these are the draggers
  SoTranslate1Dragger *xDragger = new SoTranslate1Dragger;
  SoTranslate1Dragger *yDragger = new SoTranslate1Dragger;
  SoTranslate1Dragger *zDragger = new SoTranslate1Dragger;
  xDragger->translation.setValue(SbVec3f(1.0, 0.0, 0.0));
  yDragger->translation.setValue(SbVec3f(1.0, 0.0, 0.0));
  zDragger->translation.setValue(SbVec3f(1.0, 0.0, 0.0));
  xDrag->addChild(xDragger);
  yDrag->addChild(yDragger);
  zDrag->addChild(zDragger);

  root->addChild(xDrag);
  root->addChild(yDrag);
  root->addChild(zDrag);

  // box to be sized
  SoCube *cube = new SoCube;
  SoMaterial *mat = new SoMaterial;
  mat->diffuseColor.setValue(0.5, 1.0, 1.0);
  mat->specularColor.setValue(1.0, 1.0, 1.0);
  mat->shininess = 0.7;
  // this is the transformation that will actually modify the object
  SoTransform *cubeX = new SoTransform;
  root->addChild(cubeX); 
  root->addChild(mat);
  root->addChild(cube);

  SoCalculator *calc = new SoCalculator;
  calc->ref();
  calc->A.connectFrom(&xDragger->translation); 
  calc->B.connectFrom(&yDragger->translation); 
  calc->C.connectFrom(&zDragger->translation); 
  calc->expression = "oA = vec3f(A[0], B[0], C[0])";
  cubeX->scaleFactor.connectFrom(&calc->oA);

  SoXtExaminerViewer *viewer 
     = new SoXtExaminerViewer(window);
  viewer->setSize(SbVec2s(640, 480));

  viewer->setSceneGraph(root);
  viewer->setTitle("Multiple Draggers");
  viewer->viewAll();
  viewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
