/*--------------------------------------------------------------
 *  This example program attaches a field sensor to the camera's 
 *  position field, and prints the value of the field when the 
 *  position changes.

 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoAlarmSensor.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <iostream.h>

SoDrawStyle *drawStyle;

// Callback senses and prints out camera's new position.
static void
cameraPositionCB(void *data, SoSensor *)
{
  // pass in delay so that it can be rescheduled
  SoAlarmSensor *delay = (SoAlarmSensor *)data;

  drawStyle->style = SoDrawStyle::LINES;

  // schedule a delay before changing back
  delay->unschedule();
  delay->setTimeFromNow(2.0);
  delay->schedule();
}

// this timed callback will refill the object
static void
restoreFillCB(void *data, SoSensor *)
{
  drawStyle->style = SoDrawStyle::FILLED;
}

void
main(int argc, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();
  drawStyle = new SoDrawStyle;
  drawStyle->style = SoDrawStyle::FILLED;
  root->addChild(drawStyle);

  // attach a field sensor to camera's position field:
  SoPerspectiveCamera *camera = new SoPerspectiveCamera;
  root->addChild(camera);

  root->addChild(new SoSphere);
 
  SoAlarmSensor *delay = new SoAlarmSensor(restoreFillCB, drawStyle);

  SoFieldSensor *fieldSensor = 
           new SoFieldSensor(cameraPositionCB, delay);
  fieldSensor->attach(&camera->position);

  SoXtExaminerViewer *myViewer =
          new SoXtExaminerViewer(window);
  myViewer->setSize(SbVec2s(640, 480));
  myViewer->setSceneGraph(root);
  myViewer->setTitle("Field Sensor Example");
  myViewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
