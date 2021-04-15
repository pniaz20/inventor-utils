/*--------------------------------------------------------------
 *  This example program maps a photograph onto a sphere using
 *  a plane texture coordinate function.
 *
 *  Copyright 1996 Chris Buckalew   modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoTextureCoordinatePlane.h>
#include <Inventor/nodes/SoSphere.h>

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);

  SoSeparator *root = new SoSeparator;
  root->ref();

  // read in photo
  SoTexture2 *texture = new SoTexture2;
  texture->filename.setValue("buckalew.bmp");
  texture->model = SoTexture2::MODULATE;

  // place in proper location on sphere
  SoTexture2Transform *transX = new SoTexture2Transform;
  transX->translation.setValue(0.5, 0.5);
  root->addChild(transX);

  // double the size 
  SoTextureCoordinatePlane *picture = new SoTextureCoordinatePlane; 
  picture->directionS.setValue(SbVec3f(0.5, 0, 0));
  picture->directionT.setValue(SbVec3f(0, 0.5, 0));
  root->addChild(picture);

  root->addChild(texture);
  root->addChild(new SoSphere);

  exViewer->setSize(SbVec2s(640, 480));

  exViewer->setSceneGraph(root);
  exViewer->setTitle("Plane Texture Coordinate Example");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


