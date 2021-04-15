/*--------------------------------------------------------------
 *  This example program demonstrates Reflection Texture Maps.
 *  It displays an untextured sphere, a reflection texture
 *  on a card, and the reflection texture mapped onto the
 *  sphere.
 *
 *  Copyright 1995 Chris Buckalew  mod 2/6/96 CB
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTextureCoordinateEnvironment.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoComplexity.h>

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  // the texture
  SoTexture2 *texture = new SoTexture2;
  texture->filename.setValue("church.bmp");
  texture->model = SoTexture2::DECAL;
  SoComplexity *comp = new SoComplexity;
  comp->textureQuality = 0.75;
  root->addChild(comp);

  // the untextured sphere
  SoTransform *x1 = new SoTransform;
  x1->translation.setValue(-2.0, 2.0, 0.0);
  root->addChild(x1);
  root->addChild(new SoSphere);

  // the texture card
  SoSeparator *pattern = new SoSeparator;
  root->addChild(pattern);

  SoTransform *x3 = new SoTransform;
  x3->translation.setValue(0.0, -4.0, 0.0);
  pattern->addChild(x3);

  pattern->addChild(texture);

  SoCube *cube = new SoCube;
  cube->depth.setValue(0.01);
  pattern->addChild(cube);

  // textured sphere 
  SoTransform *x = new SoTransform;
  x->translation.setValue(4.0, -2.0, 0.0);
  root->addChild(x);
  SoTransform *x2 = new SoTransform;
  x2->rotation.setValue(SbVec3f(1,0,0), M_PI/2);
  root->addChild(x2);
  root->addChild(new SoTextureCoordinateEnvironment);
  root->addChild(texture);
  root->addChild(new SoSphere);

  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setBackgroundColor(SbColor(0.3, 0.3, 0.3));
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Reflection Texture");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


