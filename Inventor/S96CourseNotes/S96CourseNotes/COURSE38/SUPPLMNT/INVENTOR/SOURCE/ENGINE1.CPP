/*--------------------------------------------------------------
 *  This example program demonstrates the use of Field 
 *  Connections.  One engine increases the sphere's radius, 
 *  and a field connection automatically increases the width
 *  of a cube
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>

void
main(int argc, char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);  
  if (window == NULL) exit(1);     

  SoSeparator *root = new SoSeparator;
  root->ref();

  // set up camera and light
  SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
  myCamera->position.setValue(0.0, 2.0, 8.0);
  myCamera->pointAt(SbVec3f(0.0, 0.0, 0.0));
  myCamera->heightAngle = M_PI/2.5; 
  myCamera->nearDistance = 1.0;
  myCamera->farDistance = 50.0;
  root->addChild(myCamera);
  SoDirectionalLight *dir = new SoDirectionalLight;
  dir->direction.setValue(1.0, -0.5, -0.8);
  root->addChild(dir);

  // cube and sphere
  SoSphere *ball = new SoSphere;
  SoCube *box = new SoCube;
  SoTranslation *left = new SoTranslation;
  left->translation.setValue(-3.0, 0.0, 0.0);
  root->addChild(left);
  root->addChild(ball);
  SoTranslation *right = new SoTranslation;
  right->translation.setValue(6.0, 0.0, 0.0);
  root->addChild(right);
  root->addChild(box);

  // connect the cube width to sphere radius
  box->width.connectFrom(&ball->radius); 

  // this engine increases sphere radius
  SoElapsedTime *counter = new SoElapsedTime;
  counter->speed = 0.125;
  ball->radius.connectFrom(&counter->timeOut);

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));

  SbViewportRegion region(renderArea->getSize()); 
  renderArea->setSceneGraph(root);
  renderArea->setTitle("Field Connection Example");
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
