/*----------------------------------------------------------------
 *  This example program demonstrates many Inventor Draggers.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *----------------------------------------------------------------*/

#include <Inventor/engines/SoCompose.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>

#include <Inventor/draggers/SoJackDragger.h>
#include <Inventor/draggers/SoHandleBoxDragger.h>
#include <Inventor/draggers/SoTrackballDragger.h>
#include <Inventor/draggers/SoTransformBoxDragger.h>
#include <Inventor/draggers/SoCenterballDragger.h>
#include <Inventor/draggers/SoRotateCylindricalDragger.h>
#include <Inventor/draggers/SoRotateDiscDragger.h>
#include <Inventor/draggers/SoScaleUniformDragger.h>
#include <Inventor/draggers/SoTabBoxDragger.h>
#include <Inventor/draggers/SoTabPlaneDragger.h>
#include <Inventor/draggers/SoDirectionalLightDragger.h>
#include <Inventor/draggers/SoTranslate2Dragger.h>
#include <stdio.h>

#define MAXSTEP 11 
int step = 0;
SbViewportRegion viewportRegion;

void
keyPressCB(void *userData, SoEventCallback *eventCB)
{
  SoSwitch *selection = (SoSwitch *) userData;
  const SoEvent *event = eventCB->getEvent();

  // check for the Up and Down arrow keys being pressed
  if (SO_KEY_PRESS_EVENT(event, SPACE)) {
    step++;
    if (step>MAXSTEP) step = 0;
    selection->whichChild = step;
    eventCB->setHandled();
  }
}

void
main(int argc , char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *camera = new SoPerspectiveCamera;
  root->addChild(camera);
  root->addChild(new SoDirectionalLight);

  SoSwitch *selection = new SoSwitch;
  root->addChild(selection);
  selection->whichChild = 0;

  SoGroup *group0 = new SoGroup;
  SoJackDragger *dragger0 = new SoJackDragger;
  SoTransform *drag0X = new SoTransform;
  group0->addChild(dragger0);
  group0->addChild(drag0X);
  drag0X->translation.connectFrom(&dragger0->translation);
  drag0X->scaleFactor.connectFrom(&dragger0->scaleFactor);
  drag0X->rotation.connectFrom(&dragger0->rotation);
  selection->addChild(group0);

  SoGroup *group1 = new SoGroup;
  SoHandleBoxDragger *dragger1 = new SoHandleBoxDragger;
  SoTransform *drag1X = new SoTransform;
  group1->addChild(dragger1);
  group1->addChild(drag1X);
  drag1X->translation.connectFrom(&dragger1->translation);
  drag1X->scaleFactor.connectFrom(&dragger1->scaleFactor);
  selection->addChild(group1);

  SoGroup *group2 = new SoGroup;
  SoTrackballDragger *dragger2 = new SoTrackballDragger;
  SoTransform *drag2X = new SoTransform;
  group2->addChild(dragger2);
  group2->addChild(drag2X);
  drag2X->scaleFactor.connectFrom(&dragger2->scaleFactor);
  drag2X->rotation.connectFrom(&dragger2->rotation);
  selection->addChild(group2);

  SoGroup *group3 = new SoGroup;
  SoTransformBoxDragger *dragger3 = new SoTransformBoxDragger;
  SoTransform *drag3X = new SoTransform;
  group3->addChild(dragger3);
  group3->addChild(drag3X);
  drag3X->translation.connectFrom(&dragger3->translation);
  drag3X->scaleFactor.connectFrom(&dragger3->scaleFactor);
  drag3X->rotation.connectFrom(&dragger3->rotation);
  selection->addChild(group3);

  SoGroup *group4 = new SoGroup;
  SoCenterballDragger *dragger4 = new SoCenterballDragger;
  SoTransform *drag4X = new SoTransform;
  group4->addChild(dragger4);
  group4->addChild(drag4X);
  drag4X->translation.connectFrom(&dragger4->center);
  drag4X->rotation.connectFrom(&dragger4->rotation);
  selection->addChild(group4);

  SoGroup *group5 = new SoGroup;
  SoRotateCylindricalDragger *dragger5 = new SoRotateCylindricalDragger;
  SoTransform *drag5X = new SoTransform;
  group5->addChild(dragger5);
  group5->addChild(drag5X);
  drag5X->rotation.connectFrom(&dragger5->rotation);
  selection->addChild(group5);

  SoGroup *group6 = new SoGroup;
  SoTabBoxDragger *dragger6 = new SoTabBoxDragger;
  SoTransform *drag6X = new SoTransform;
  group6->addChild(dragger6);
  group6->addChild(drag6X);
  drag6X->translation.connectFrom(&dragger6->translation);
  drag6X->scaleFactor.connectFrom(&dragger6->scaleFactor);
  selection->addChild(group6);

  SoGroup *group7 = new SoGroup;
  SoScaleUniformDragger *dragger7 = new SoScaleUniformDragger;
  SoTransform *drag7X = new SoTransform;
  group7->addChild(dragger7);
  group7->addChild(drag7X);
  drag7X->scaleFactor.connectFrom(&dragger7->scaleFactor);
  selection->addChild(group7);

  SoGroup *group8 = new SoGroup;
  SoDirectionalLightDragger *dragger8 = new SoDirectionalLightDragger;
  SoTransform *drag8X = new SoTransform;
  group8->addChild(dragger8);
  group8->addChild(drag8X);
  drag8X->rotation.connectFrom(&dragger8->rotation);
  selection->addChild(group8);

  SoGroup *group9 = new SoGroup;
  SoTranslate2Dragger *dragger9 = new SoTranslate2Dragger;
  SoTransform *drag9X = new SoTransform;
  group9->addChild(dragger9);
  group9->addChild(drag9X);
  drag9X->translation.connectFrom(&dragger9->translation);
  selection->addChild(group9);

  SoGroup *group10 = new SoGroup;
  SoRotateDiscDragger *dragger10 = new SoRotateDiscDragger;
  SoTransform *drag10X = new SoTransform;
  group10->addChild(dragger10);
  group10->addChild(drag10X);
  drag10X->rotation.connectFrom(&dragger10->rotation);
  selection->addChild(group10);

  SoGroup *group11 = new SoGroup;
  SoTabPlaneDragger *dragger11 = new SoTabPlaneDragger;
  SoTransform *drag11X = new SoTransform;
  group11->addChild(dragger11);
  group11->addChild(drag11X);
  drag11X->translation.connectFrom(&dragger11->translation);
  drag11X->scaleFactor.connectFrom(&dragger11->scaleFactor);
  selection->addChild(group11);

  SoCone      *cone = new SoCone;
  root->addChild(cone);

  SoEventCallback *eventCB = new SoEventCallback;
  eventCB->addEventCallback(
           SoKeyboardEvent::getClassTypeId(),
           keyPressCB, selection);
  root->addChild(eventCB);

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));

  renderArea->setSceneGraph(root);
  renderArea->setTitle("Different Draggers");

  viewportRegion = renderArea->getViewportRegion();
  camera->viewAll(root, viewportRegion, 2.0);

  // Show our application window, and loop forever...
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
