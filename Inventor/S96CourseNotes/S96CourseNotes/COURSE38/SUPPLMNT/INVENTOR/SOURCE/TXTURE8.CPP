/*--------------------------------------------------------------
 *  This example program demonstrates the use of Explicit 
 *  Texture Coordinates
 *
 *  Copyright 1995 Chris Buckalew    modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoComplexity.h>

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

  // checkerboard texture
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

  SoComplexity *comp = new SoComplexity;
  comp->textureQuality = 0.05;
  root->addChild(comp);

  // these coordinates define the card
  SoCoordinate3 *coords = new SoCoordinate3;
  root->addChild(coords);
  coords->point.set1Value(0, SbVec3f(-2.0, -2.0, 0.0));
  coords->point.set1Value(1, SbVec3f( 2.0, -2.0, 0.0));
  coords->point.set1Value(2, SbVec3f( 2.0,  2.0, 0.0));
  coords->point.set1Value(3, SbVec3f(-2.0,  2.0, 0.0));

  SoFaceSet *faceSet = new SoFaceSet;
  faceSet->numVertices.set1Value(0, 4);
  root->addChild(faceSet);

  // these are the corresponding texture coordinates
  SoTextureCoordinate2 *texCoord = new SoTextureCoordinate2;
  texCoord->point.set1Value(0, SbVec2f(0.0, 0.0));
  texCoord->point.set1Value(1, SbVec2f(1.0, 0.0));
  texCoord->point.set1Value(2, SbVec2f(1.0, 0.5));
  texCoord->point.set1Value(3, SbVec2f(0.0, 0.25));
  root->addChild(texCoord);

  SoTextureCoordinateBinding *texBind = new SoTextureCoordinateBinding;
  texBind->value.setValue(SoTextureCoordinateBinding::PER_VERTEX);
  root->addChild(texBind);

  SoTranslation *rightX = new SoTranslation;
  rightX->translation.setValue(5.0, 0.0, 0.0);
  root->addChild(rightX);

  root->addChild(faceSet);

  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Explicit Texture Coordinates");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


