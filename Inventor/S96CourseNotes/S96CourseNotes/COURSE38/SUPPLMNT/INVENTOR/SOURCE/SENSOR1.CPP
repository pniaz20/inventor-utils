/*--------------------------------------------------------------
 *  This example program demonstrates Timer Sensors.
 *
 *  One timer rotates a cube while the other timer turns
 *  a green light on and off.
 * 
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/sensors/SoTimerSensor.h>

static void
rotatingSensorCallback(void *data, SoSensor *)
{
  // Rotate an object...
  SoRotation *rotation = (SoRotation *)data;
  SbRotation currentRotation = rotation->rotation.getValue();
  currentRotation = SbRotation( SbVec3f(0,0,1), M_PI/90.0) * currentRotation;
  rotation->rotation.setValue(currentRotation);
}

static void
lightSensorCallback(void *data, SoSensor *)
{
  // toggle the light...
  SoDirectionalLight *light = (SoDirectionalLight *)data;
  if (light->on.getValue() == TRUE)
    light->on = FALSE;
  else
    light->on = TRUE;
}

void
main(int argc, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoDirectionalLight *light = new SoDirectionalLight;
  light->on = FALSE;
  light->color.setValue(0.0, 1.0, 0.0);
  root->addChild(light);
  
  SoRotation *rotation = new SoRotation;
  root->addChild(rotation);

  SoTimerSensor *rotatingSensor =
     new SoTimerSensor(rotatingSensorCallback, rotation);
  rotatingSensor->setInterval(1.0); // scheduled once per second
  rotatingSensor->schedule();

  SoTimerSensor *lightSensor =
     new SoTimerSensor(lightSensorCallback, light);
  lightSensor->setInterval(5.0); // once per 5 seconds
  lightSensor->schedule();

  SoCube *cube = new SoCube;
  root->addChild(cube);

  SoXtExaminerViewer *viewer = new SoXtExaminerViewer(window);
  viewer->setSize(SbVec2s(640, 480));
  viewer->setSceneGraph(root);
  viewer->setTitle("Timer Sensors");
  viewer->show();

  SoXt::show(window); 
  SoXt::mainLoop();   
}
