/*--------------------------------------------------------------
 *  This example program demonstrates Alarm Sensors
 *
 *  This code turns a green light on when the alarm goes off.
 *
 *  Copyright 1995 Chris Buckalew modified 5/11/95
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/sensors/SoAlarmSensor.h>

static void
alarmCallback(void *data, SoSensor *)
{
  // the light node is passed in
  SoDirectionalLight *light = (SoDirectionalLight *)data;

  // turn it on
  light->on = TRUE;
}

void
main(int , char **argv)
{
  Widget window = SoXt::init(argv[0]); 
  if (window == NULL) exit(1);

  SoDirectionalLight *light = new SoDirectionalLight;
  light->on = FALSE;
  light->color.setValue(0.0, 1.0, 0.0);

  // Create an alarm that will turn the light on
  SoAlarmSensor *alarm = new SoAlarmSensor(alarmCallback, light);
  alarm->setTimeFromNow(10.0);
  alarm->schedule();

  SoSeparator *root = new SoSeparator;
  root->ref();
  root->addChild(light);
  SoCube *cube = new SoCube;
  root->addChild(cube);

  SoXtExaminerViewer *viewer = new SoXtExaminerViewer(window);
  viewer->setSize(SbVec2s(640, 480));
  viewer->setSceneGraph(root);
  viewer->setTitle("Alarm Sensors");
  viewer->show();

  SoXt::show(window);  // Display main window
  SoXt::mainLoop();      // Main Inventor event loop
}

