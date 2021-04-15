/*--------------------------------------------------------------
 *  This example program maps a scanned texture on a cube.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoCube.h>

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

  // read in texture
  SoTexture2 *texture = new SoTexture2;
  texture->filename.setValue("postcard.bmp");
  texture->model = SoTexture2::DECAL;
  root->addChild(texture);

  root->addChild(new SoCube);

  exViewer->setSize(SbVec2s(640, 480));

  exViewer->setSceneGraph(root);
  exViewer->setTitle("Simple Scanned Texture");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}


