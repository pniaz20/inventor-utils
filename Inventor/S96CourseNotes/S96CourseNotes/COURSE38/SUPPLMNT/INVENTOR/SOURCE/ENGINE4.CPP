/*--------------------------------------------------------------
 *  This example program demonstrates the Calculator Engine.
 *
 *  Copyright 1995 Chris Buckalew
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
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
  myCamera->position.setValue(0, 0, 12.0);
  myCamera->pointAt(SbVec3f(0.0, 0.0, 0.0));
  myCamera->heightAngle = M_PI/4; 
  myCamera->nearDistance = 1.0;
  myCamera->farDistance = 50.0;
  root->addChild(myCamera);
  root->addChild(new SoDirectionalLight);

  SoTranslation *jumpX = new SoTranslation;
  root->addChild(jumpX);

  SoTranslation *initialX = new SoTranslation;
  initialX->translation.setValue(-3, -3, 0);
  root->addChild(initialX);

  root->addChild(new SoSphere);

  SoElapsedTime *counter = new SoElapsedTime;
  SoCalculator *calcJump = new SoCalculator;
  calcJump->a.connectFrom(&counter->timeOut);                    // get the time
  calcJump->expression.set1Value(0, "ta = 0.25 * a");            // x coordinate
  calcJump->expression.set1Value(1, "tb=5 * fabs(cos(a/2.0))");  // y coordinate
  calcJump->expression.set1Value(2, "oA = vec3f(ta, tb, 0)");    // output vector
  jumpX->translation.connectFrom(&calcJump->oA);

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));
  SbViewportRegion region(renderArea->getSize()); 
  renderArea->setSceneGraph(root);
  renderArea->setTitle("Calculator Engine Example");
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
