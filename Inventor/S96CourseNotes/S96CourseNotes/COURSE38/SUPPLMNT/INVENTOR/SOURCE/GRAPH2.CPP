/*--------------------------------------------------------------
 *  This example program builds a simple scene graph
 *  consisting of a head with hat and nose.
 *
 *  This code shows how groups are combined.
 *
 *  Copyright 1996 Chris Buckalew  mod4/28/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoComplexity.h>

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoGroup *root = new SoGroup;
  root->ref();

  // first do hat
  SoGroup *hat = new SoGroup;

  // shiny cyan hat
  SoMaterial *hatM = new SoMaterial;
    hatM->diffuseColor.setValue(0.2, 0.8, 0.8);
    hatM->specularColor.setValue(0.9, 0.9, 0.9);
    hatM->shininess = 0.9;
  
  // this is the shape
  SoCone *hCone = new SoCone;

  // add nodes to hat group
  hat->addChild(hatM);
  hat->addChild(hCone);

  // now do nose group
  SoGroup *nose = new SoGroup;

  // nose transform
  SoTransform *noseX = new SoTransform;
    noseX->translation.setValue(0.0, -3.0, 1.75);
    noseX->scaleFactor.setValue(0.33, 0.33, 0.33);

  // nose shape
  SoCube *nBox = new SoCube;

  // put group together
  nose->addChild(noseX);
  nose->addChild(nBox);

  // head group
  SoGroup *head = new SoGroup;

  // head scale
  SoTransform *headX = new SoTransform;
    headX->translation.setValue(0.0, 0.0, -5.25);
    headX->scaleFactor.setValue(5.0, 7.0, 5.0);

  // head material
  SoMaterial *headM = new SoMaterial;
    headM->diffuseColor.setValue(0.9, 0.7, 0.6);
    headM->specularColor.setValue(0.7, 0.7, 0.7);
    headM->shininess = 0.9;

  // oval for head
  SoSphere *hSphere = new SoSphere;

  // this node tesselates the sphere more finely
  SoComplexity *complex = new SoComplexity;
  complex->value = 0.7;

  // put head together
  head->addChild(complex);
  head->addChild(headX);
  head->addChild(headM);
  head->addChild(hSphere);

  // now put all the groups together
  root->addChild(hat);
  root->addChild(nose);
  root->addChild(head);

  // open the screen viewer
  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Combining Groups");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}

