/*--------------------------------------------------------------
 *  This example program demonstrates a Motion Hierarchy
 *  built with Node Kits.
 *
 *  Copyright 1995 Chris Buckalew   mod5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoDirectionalLight.h>

// callback rotates gears one notch
void
rotateGears(
  void *userData, SoEventCallback *eventCB) 
{
  const SoEvent *ev = eventCB->getEvent();

  if (SO_KEY_PRESS_EVENT(ev, RIGHT_ARROW) ||
      SO_KEY_PRESS_EVENT(ev, LEFT_ARROW)) {
    SoShapeKit *gears, *leftGear, *rightGear;
    SbRotation startRot, leftIncr, rightIncr;

	// pass in top level
    gears = (SoShapeKit *) userData;
    leftGear = (SoShapeKit *) gears->getPart("childList[0]", TRUE);
    rightGear = (SoShapeKit *) gears->getPart("childList[1]", TRUE);

    if (SO_KEY_PRESS_EVENT(ev, RIGHT_ARROW)) {
      leftIncr.setValue(SbVec3f(0, 0, 1), -0.1);
      rightIncr.setValue(SbVec3f(0, 0, 1), 0.05);
    }
    else {
      leftIncr.setValue(SbVec3f(0, 0, 1), 0.1);
      rightIncr.setValue(SbVec3f(0, 0, 1), -0.05);
    }

    SoTransform *rotX;
    rotX = SO_GET_PART(leftGear, "transform", SoTransform);
    startRot = rotX->rotation.getValue();
    rotX->rotation.setValue(startRot * leftIncr);

    rotX = SO_GET_PART(rightGear, "transform", SoTransform);
    startRot = rotX->rotation.getValue();
    rotX->rotation.setValue(startRot * rightIncr);

    eventCB->setHandled();
  }
}

void
main(int argc, char **argv)
{
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *camera = new SoPerspectiveCamera;
  root->addChild(camera);
  root->addChild(new SoDirectionalLight);

  // top level
  SoShapeKit *gears = new SoShapeKit;
  // remove shape
  gears->setPart("shape", NULL);
  gears->set("transform {rotation 1 0 0 -0.7854}");
  root->addChild(gears);
  
  // this is the gear itself
  SoShapeKit *leftGear = new SoShapeKit;
  leftGear->setPart("shape", new SoCylinder);
  SoCylinder *cyl = (SoCylinder *)leftGear->getPart("shape", TRUE);
  cyl->radius = 2.0;
  cyl->height = 0.3;
  leftGear->set("transform {translation -2.0 0.0 0.0}"
                "transform {rotation 1 0 0 1.5708}"
				"material  {diffuseColor 0.4 0.9 0.4}");
  gears->setPart("childList[0]", leftGear);

  // marker on left gear
  SoShapeKit *leftGearMark = new SoShapeKit;
  leftGearMark->setPart("shape", new SoCylinder);
  cyl = (SoCylinder *)leftGearMark->getPart("shape", TRUE);
  cyl->radius = 0.1;
  cyl->height = 0.6;
  leftGearMark->set("transform {translation 1.5 0.0 0.0}"
                    "material {diffuseColor 0.1 0.1 0.1}");
  leftGear->setPart("childList[0]", leftGearMark);

  // shaft on left gear
  SoShapeKit *leftGearShaft = new SoShapeKit;
  leftGearShaft->setPart("shape", new SoCylinder);
  cyl = (SoCylinder *)leftGearShaft->getPart("shape", TRUE);
  cyl->radius = 0.3;
  cyl->height = 1.0;
  leftGearShaft->set("material {diffuseColor 1.0 0.4 0.4}");
  leftGear->setPart("childList[1]", leftGearShaft);

  // the right gear itself
  SoShapeKit *rightGear = new SoShapeKit;
  rightGear->setPart("shape", new SoCylinder);
  cyl = (SoCylinder *)rightGear->getPart("shape", TRUE);
  cyl->radius = 4.0;
  cyl->height = 0.3;
  rightGear->set("transform {translation 4.0 0.0 0.0}"
                 "transform {rotation 1 0 0 1.5708}"
			  	 "material  {diffuseColor 0.4 0.9 0.4}");
  gears->setPart("childList[1]", rightGear);

  // marker on right gear
  SoShapeKit *rightGearMark = new SoShapeKit;
  rightGearMark->setPart("shape", new SoCylinder);
  cyl = (SoCylinder *)rightGearMark->getPart("shape", TRUE);
  cyl->radius = 0.1;
  cyl->height = 0.6;
  rightGearMark->set("transform {translation -3.5 0.0 0.0}"
                     "material {diffuseColor 0.1 0.1 0.1}");
  rightGear->setPart("childList[0]", rightGearMark);

  // shaft on right gear
  SoShapeKit *rightGearShaft = new SoShapeKit;
  rightGearShaft->setPart("shape", new SoCylinder);
  cyl = (SoCylinder *)rightGearShaft->getPart("shape", TRUE);
  cyl->radius = 0.5;
  cyl->height = 1.0;
  rightGearShaft->set("material {diffuseColor 1.0 0.4 0.4}");
  rightGear->setPart("childList[1]", rightGearShaft);

  SoEventCallback *callbackNode = new SoEventCallback;
  callbackNode->addEventCallback(
    SoKeyboardEvent::getClassTypeId(), rotateGears, gears);
  gears->setPart("callbackList[0]", callbackNode);

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));

  SbViewportRegion region(renderArea->getSize());
  camera->pointAt(SbVec3f(0, 0, 0));
  camera->position.setValue(0, 0, 17);
  camera->farDistance.setValue(50.0);

  renderArea->setSceneGraph(root);
  renderArea->setTitle("Motion Hierarchy using Node Kits");
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}

