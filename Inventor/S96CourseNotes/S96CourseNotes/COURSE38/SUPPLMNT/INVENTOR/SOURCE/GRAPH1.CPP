/*--------------------------------------------------------------
 *  This example program builds a simple scene graph
 *  consisting of just a head.
 *
 *  This code shows how nodes are created.
 *
 *  Copyright 1996 Chris Buckalew  mod4/28/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoComplexity.h>

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoGroup *head = new SoGroup;
  head->ref();

  // this node tesselates the sphere more finely
  SoComplexity *complex = new SoComplexity;
  complex->value = 0.7;

  // head scale
  SoTransform *headX = new SoTransform;
    headX->scaleFactor.setValue(5.0, 7.0, 5.0);

  // head material
  SoMaterial *headM = new SoMaterial;
    headM->diffuseColor.setValue(0.9, 0.7, 0.6);
    headM->specularColor.setValue(0.7, 0.7, 0.7);
    headM->shininess = 0.9;

  // oval for head
  SoSphere *hSphere = new SoSphere;

  // put head together
  head->addChild(complex);
  head->addChild(headX);
  head->addChild(headM);
  head->addChild(hSphere);

  // open the screen viewer
  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(head);
  exViewer->setTitle("Creating Nodes");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}

