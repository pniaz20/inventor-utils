/*--------------------------------------------------------------
 *  This example program demonstrates the Elapsed Time engine.
 *  The elapsed time engine controls the rotation angle of an
 *  airplane model.
 *  
 *  Copyright 1995 Chris Buckalew
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCube.h>

void
main(int argc, char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);  
  if (window == NULL) exit(1);     

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
  myCamera->position.setValue(0.0, 2.0, 8.0);
  myCamera->pointAt(SbVec3f(0.0, 0.0, 0.0));
  myCamera->heightAngle = M_PI/2.5; 
  myCamera->nearDistance = 1.0;
  myCamera->farDistance = 50.0;
  root->addChild(myCamera);
  root->addChild(new SoDirectionalLight);

  // rotation of plane around center
  SoRotationXYZ *rot = new SoRotationXYZ;
  rot->axis = SoRotationXYZ::Y;
  root->addChild(rot);

  // initial orientation of plane
  SoTransform *initialTransform = new SoTransform;
  initialTransform->translation.setValue(-5., 0., 0.);
  initialTransform->scaleFactor.setValue(0.02, 0.02, 0.02);
  initialTransform->rotation.setValue(SbVec3f(0,1,0), M_PI/2.);
  root->addChild(initialTransform);
  
  // give the plane a bank
  SoRotationXYZ *roll = new SoRotationXYZ;
  roll->axis = SoRotationXYZ::X;
  roll->angle = M_PI/6.0;
  root->addChild(roll);

  // Read the plane from a file 
  SoInput planeFile;
  if (!planeFile.openFile("p707.iv")) 
     exit(-1);
  SoSeparator *plane = SoDB::readAll(&planeFile);
  if (plane == NULL) exit(-1);
  root->addChild(plane);

  // revolve over time...
  SoElapsedTime *counter = new SoElapsedTime;
  // ...but slowly
  counter->speed = 0.25;
  rot->angle.connectFrom(&counter->timeOut);   // pass into angle

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));
  SbViewportRegion region(renderArea->getSize()); 
  renderArea->setSceneGraph(root);
  renderArea->setTitle("ElapsedTime Example");
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
