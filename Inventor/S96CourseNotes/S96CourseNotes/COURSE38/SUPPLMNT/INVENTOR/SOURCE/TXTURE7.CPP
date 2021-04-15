/*--------------------------------------------------------------
 *  This example program demonstrates Transforming Texture Maps
 *
 *  Copyright 1995 Chris Buckalew  modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTransform.h>
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
  unsigned char image [] = {
    255, 255, 0, 0, 0, 0,  
    0, 0, 0,  255, 255, 0  
  };

  texture->image.setValue(SbVec2s(2,2), 3, image);
  texture->model = SoTexture2::MODULATE;

  SoComplexity *comp = new SoComplexity;
  comp->textureQuality = 0.25;
  root->addChild(comp);

  SoTexture2Transform *transX = new SoTexture2Transform;
  transX->scaleFactor.setValue(8.0, 8.0);
  transX->rotation.setValue(M_PI/6.0);
  root->addChild(transX);

  SoMaterial *mat = new SoMaterial;
  mat->diffuseColor.setValue(0.3, 1.0, 0.3);
  root->addChild(mat);

  SoTransform *x = new SoTransform;
  x->translation.setValue(4.0, 0.0, 0.0);
  root->addChild(texture);
  root->addChild(new SoCube);

  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Transforming Textures");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


