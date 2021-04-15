/*--------------------------------------------------------------
 *  This example program demonstrates a 4-component texture
 *  with transparency
 *
 *  Copyright 1995 Chris Buckalew  modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
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

  // something to look at
  SoMaterial *matSphere = new SoMaterial;
  matSphere->diffuseColor.setValue(0.7, 1.0, 0.3);
  root->addChild(matSphere);
  root->addChild(new SoSphere);

  SoTexture2 *texture = new SoTexture2;

  // this is a 4-component texture: RGBA
  const unsigned char image [] = {
    255,255,255,255, 255,255,255,219, 255,255,255,183, 255,255,255,147,
	255,255,255,111, 255,255,255,75,  255,255,255,39,  255,255,255,255
  };

  // 1 row, 8 columns
  texture->image.setValue(SbVec2s(1,8), 4, image);
  texture->model = SoTexture2::MODULATE;
  root->addChild(texture);

  // textured face
  SoTranslation *X = new SoTranslation;
  X->translation.setValue(0.0, 0.0, 2.0);
  root->addChild(X);
  SoMaterial *matCard = new SoMaterial;
  matCard->diffuseColor.setValue(1.0, 1.0, 1.0);
  root->addChild(matCard);
  SoCoordinate3 *coords = new SoCoordinate3;
  coords->point.set1Value(0, SbVec3f(-1,-1,0));
  coords->point.set1Value(1, SbVec3f(1,-1,0));
  coords->point.set1Value(2, SbVec3f(1,1,0));
  coords->point.set1Value(3, SbVec3f(-1,1,0));
  root->addChild(coords);
  SoFaceSet *face = new SoFaceSet;
  face->numVertices.setValue(4);
  root->addChild(face);

  exViewer->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Transparent Texture");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


