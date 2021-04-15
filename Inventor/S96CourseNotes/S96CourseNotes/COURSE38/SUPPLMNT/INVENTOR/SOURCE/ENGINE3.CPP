/*--------------------------------------------------------------
 *  This example program demonstrates the Time Counter engine.
 *  Two time counter engines are hooked to the x and y coordinates
 *  of the translation field of a transformation node.
 *  
 *  Copyright 1995 Chris Buckalew
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoTimeCounter.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSphere.h>

void
main(int argc, char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);  
  if (window == NULL) exit(1);     

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
  myCamera->position.setValue(0.0, 0.0, 20.0);
  myCamera->pointAt(SbVec3f(0.0, 0.0, 0.0));
  myCamera->heightAngle = M_PI/3.5; 
  myCamera->nearDistance = 1.0;
  myCamera->farDistance = 50.0;
  root->addChild(myCamera);
  root->addChild(new SoDirectionalLight);

  SoTranslation *jumpX = new SoTranslation;
  root->addChild(jumpX);
  // initial orientation of ball
  SoTransform *initialTransform = new SoTransform;
  initialTransform->translation.setValue(-15.0, -7.0, 0.0);
  root->addChild(initialTransform);

  root->addChild(new SoSphere);

  // Create two counters, and connect to X and Y translations.
  // The Y counter is small and high frequency.
  // The X counter is large and low frequency.
  // This results in small jumps across the screen.
  SoTimeCounter *heightCounter = new SoTimeCounter;
  SoTimeCounter *widthCounter = new SoTimeCounter;
  SoComposeVec3f *jump = new SoComposeVec3f;

  // fields of the time counter engines
  heightCounter->max = 14;
  heightCounter->frequency = 1.0;
  widthCounter->max = 30;
  widthCounter->frequency = 0.15;

  // hook time counters to a compose engine
  jump->x.connectFrom(&widthCounter->output);
  jump->y.connectFrom(&heightCounter->output);
  jumpX->translation.connectFrom(&jump->vector);

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));
  SbViewportRegion region(renderArea->getSize()); 
  renderArea->setSceneGraph(root);
  renderArea->setTitle("TimeCounter Example");
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
