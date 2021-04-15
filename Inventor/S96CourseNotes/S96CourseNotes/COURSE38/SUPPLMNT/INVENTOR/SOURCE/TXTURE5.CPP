/*--------------------------------------------------------------
 *  This example program demonstrates the Blend Texture
 *
 *  Copyright 1995 Chris Buckalew  modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoCube.h>
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

  SoTexture2 *texture = new SoTexture2;

  // this is an intensity texture for the blend
  unsigned char image1 [] = {
    255, 0, 255, 0, 255, 0, 255, 0,
    0, 255, 0, 255, 0, 255, 0, 255,
    255, 0, 255, 0, 255, 0, 255, 0,
    0, 255, 0, 255, 0, 255, 0, 255,
    255, 0, 255, 0, 255, 0, 255, 0,
    0, 255, 0, 255, 0, 255, 0, 255,
    255, 0, 255, 0, 255, 0, 255, 0,
    0, 255, 0, 255, 0, 255, 0, 255
  };

  // this is an RGB texture for the color on the texture card 
  unsigned char image2 [] = {
    255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,  
    0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255,  
    255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 
    0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 
    255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,  
    0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255,  
    255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 
    0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255
  };

  texture->image.setValue(SbVec2s(8,8), 1, image1);
  texture->model = SoTexture2::BLEND;
  texture->blendColor.setValue(0.0, 0.0, 1.0);
  SoComplexity *comp = new SoComplexity;
  comp->textureQuality = 0.25;
  root->addChild(comp);

  // the untextured cube
  SoMaterial *mat = new SoMaterial;
  mat->diffuseColor.setValue(0.3, 1.0, 0.3);
  root->addChild(mat);
  SoTranslation *x1 = new SoTranslation;
  x1->translation.setValue(-2.0, 2.0, 0.0);
  root->addChild(x1);
  root->addChild(new SoCube);

  // the texture card
  SoSeparator *pattern = new SoSeparator;
  root->addChild(pattern);

  SoTranslation *x3 = new SoTranslation;
  x3->translation.setValue(0.0, -4.0, 0.0);
  pattern->addChild(x3);
  SoTexture2 *texture2 = new SoTexture2;
  texture2->image.setValue(SbVec2s(8,8), 3, image2);
  texture2->model = SoTexture2::DECAL;
  pattern->addChild(texture2);
  SoCube *cube = new SoCube;
  cube->depth.setValue(0.01);
  pattern->addChild(cube);

  // textured cube
  SoTranslation *x = new SoTranslation;
  x->translation.setValue(4.0, -2.0, 0.0);
  root->addChild(x);
  root->addChild(texture);
  root->addChild(new SoCube);

  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Blend Texture");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


