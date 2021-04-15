/*--------------------------------------------------------------
 *  This example program demonstrates the use of Texture 
 *  Coordinate Plane Functions
 *
 *  Copyright 1995 Chris Buckalew   modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTextureCoordinatePlane.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTranslation.h>
 
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

  SoTexture2 *texture = new SoTexture2;
  unsigned char image [] = {
    255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0,  
    255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255,  
    255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 
    255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 
    255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0,  
    255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255,  
    255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 
    255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255
  };

  texture->image.setValue(SbVec2s(8,8), 3, image);
  texture->model = SoTexture2::MODULATE;
  root->addChild(texture);

  // default texture
  root->addChild(new SoSphere);

  // coordinate plane texture
  SoTranslation *rightX = new SoTranslation;
  rightX->translation.setValue(3.0, 0.0, 0.0);
  root->addChild(rightX);

  SoTextureCoordinatePlane *texPlane1 = new SoTextureCoordinatePlane;
  texPlane1->directionS.setValue(SbVec3f(1,0,0));
  texPlane1->directionT.setValue(SbVec3f(0,1,0));
  root->addChild(texPlane1);
  root->addChild(new SoSphere);

  // skewed coordinate plane texture
  root->addChild(rightX);

  SoTextureCoordinatePlane *texPlane2 = new SoTextureCoordinatePlane;
  texPlane2->directionS.setValue(SbVec3f(1,1,0));
  texPlane2->directionT.setValue(SbVec3f(0,1,1));
  root->addChild(texPlane2);
  root->addChild(new SoSphere);

  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Texture Coordinate Plane Functions");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


