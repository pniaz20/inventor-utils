/*--------------------------------------------------------------
 *  This example demonstrates the use of different
 *  camera fields and methods.
 *
 *  Copyright 1996 Chris Buckalew  mod5/5/96
 *------------------------------------------------------------*/

#include <Inventor/SoInput.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoKeyboardEvent.h>

#define MAXSTEP 12  // number of steps in cycle
int step = 0;
SbViewportRegion viewportRegion;

void
keyPressCB(void *userData, SoEventCallback *eventCB)
{
  /* This function changes camera parameters with each
   * press of the space bar
   */

  SoSwitch *selection = (SoSwitch *) userData;
  const SoEvent *event = eventCB->getEvent();

  // check for space bar
  if (SO_KEY_PRESS_EVENT(event, SPACE)) {
    step++;
    if (step>MAXSTEP) step = 0;   // reset
    selection->whichChild = step;
    eventCB->setHandled();
  }
}

SoSeparator *
makeHead()
{
  SoSeparator *clown = new SoSeparator;

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
  
  // eyes subgraph
  SoSeparator *eyes = new SoSeparator;

  // eye material
  SoMaterial *eyeM = new SoMaterial;
    eyeM->diffuseColor.setValue(0.1, 0.1, 0.1);
    eyeM->specularColor.setValue(0.7, 0.7, 0.7);
    eyeM->shininess = 0.9;

  // left eye transform
  SoTransform *eye1X = new SoTransform;
    eye1X->translation.setValue(-0.75, -2.0, 1.5);
    eye1X->scaleFactor.setValue(0.25, 0.25, 0.25);

  // eyeball shape
  SoSphere *eyeSphere = new SoSphere;

  // right eye transform
  SoTransform *eye2X = new SoTransform;
    eye2X->translation.setValue(6.0, 0.0, 0.0);
 
  // put eyes together
  eyes->addChild(eyeM);
  eyes->addChild(eye1X);
  eyes->addChild(eyeSphere);
  eyes->addChild(eye2X);
  eyes->addChild(eyeSphere);

  // head separator
  SoSeparator *head = new SoSeparator;

  // head scale
  SoTransform *headX = new SoTransform;
    headX->translation.setValue(0.0, -3.0, 0.0);
    headX->scaleFactor.setValue(1.66, 2.33, 1.66);

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

  // now put all the groups together
  clown->addChild(hat);
  clown->addChild(eyes);
  clown->addChild(head);
  clown->addChild(nose);
  return clown;
}

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();
  SoXtRenderArea *exViewer = new SoXtRenderArea(window);

  SoSwitch *selection = new SoSwitch;
  root->addChild(selection);
  selection->whichChild = 0;

  // create several cameras
  SoGroup *group1 = new SoGroup;
  SoPerspectiveCamera *persp1 = new SoPerspectiveCamera;
  group1->addChild(persp1);
  selection->addChild(group1);

  SoGroup *group2 = new SoGroup;
  SoPerspectiveCamera *persp2 = new SoPerspectiveCamera;
  persp2->position.setValue(0.0, 0.0, 10.0);
  persp2->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp2->farDistance.setValue(50.0);
  group2->addChild(persp2);
  selection->addChild(group2);

  SoGroup *group3 = new SoGroup;
  SoPerspectiveCamera *persp3 = new SoPerspectiveCamera;
  persp3->position.setValue(0.0, 0.0, 20.0);
  persp3->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp3->farDistance.setValue(50.0);
  group3->addChild(persp3);
  selection->addChild(group3);

  SoGroup *group4 = new SoGroup;
  SoPerspectiveCamera *persp4 = new SoPerspectiveCamera;
  persp4->position.setValue(0.0, 5.0, 10.0);
  persp4->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp4->farDistance.setValue(50.0);
  group4->addChild(persp4);
  selection->addChild(group4);

  SoGroup *group5 = new SoGroup;
  SoPerspectiveCamera *persp5 = new SoPerspectiveCamera;
  persp5->position.setValue(0.0, -5.0, 10.0);
  persp5->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp5->farDistance.setValue(50.0);
  group5->addChild(persp5);
  selection->addChild(group5);

  SoGroup *group6 = new SoGroup;
  SoPerspectiveCamera *persp6 = new SoPerspectiveCamera;
  persp6->position.setValue(10.0, -5.0, 10.0);
  persp6->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp6->farDistance.setValue(50.0);
  group6->addChild(persp6);
  selection->addChild(group6);

  SoGroup *group7 = new SoGroup;
  SoPerspectiveCamera *persp7 = new SoPerspectiveCamera;
  persp7->position.setValue(10.0, -5.0, 10.0);
  persp7->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp7->farDistance.setValue(14.0);
  group7->addChild(persp7);
  selection->addChild(group7);

  SoGroup *group8 = new SoGroup;
  SoOrthographicCamera *ortho1 = new SoOrthographicCamera;
  ortho1->position.setValue(10.0, -5.0, 10.0);
  ortho1->pointAt(SbVec3f(0.0, 0.0, 0.0));
  ortho1->farDistance.setValue(20.0);
  group8->addChild(ortho1);
  selection->addChild(group8);

  SoGroup *group9 = new SoGroup;
  SoPerspectiveCamera *persp9 = new SoPerspectiveCamera;
  persp9->viewportMapping.setValue(SoCamera::CROP_VIEWPORT_FILL_FRAME);
  group9->addChild(persp9);
  selection->addChild(group9);

  SoGroup *group10 = new SoGroup;
  SoPerspectiveCamera *persp10 = new SoPerspectiveCamera;
  persp10->viewportMapping.setValue(SoCamera::CROP_VIEWPORT_LINE_FRAME);
  group10->addChild(persp10);
  selection->addChild(group10);

  SoGroup *group11 = new SoGroup;
  SoPerspectiveCamera *persp11 = new SoPerspectiveCamera;
  persp11->viewportMapping.setValue(SoCamera::CROP_VIEWPORT_NO_FRAME);
  group11->addChild(persp11);
  selection->addChild(group11);

  SoGroup *group12 = new SoGroup;
  SoPerspectiveCamera *persp12 = new SoPerspectiveCamera;
  persp12->viewportMapping.setValue(SoCamera::ADJUST_CAMERA);
  group12->addChild(persp12);
  selection->addChild(group12);

  SoGroup *group13 = new SoGroup;
  SoPerspectiveCamera *persp13 = new SoPerspectiveCamera;
  persp13->viewportMapping.setValue(SoCamera::LEAVE_ALONE);
  group13->addChild(persp13);
  selection->addChild(group13);

  // create a light
  root->addChild(new SoDirectionalLight);

  // create something to look at
  root->addChild(makeHead());

  SoEventCallback *eventCB = new SoEventCallback;
  eventCB->addEventCallback(
           SoKeyboardEvent::getClassTypeId(),
           keyPressCB, selection);
  root->addChild(eventCB);

  exViewer->setSize(SbVec2s(640, 480));
  SbViewportRegion region(exViewer->getSize());
  persp1->viewAll(root, region);
  persp9->viewAll(root, region);
  persp10->viewAll(root, region);
  persp11->viewAll(root, region);
  persp12->viewAll(root, region);
  persp13->viewAll(root, region);
  ortho1->viewAll(root, region);

  exViewer->setSceneGraph(root);
  exViewer->setTitle("Camera Fields and Methods");
  exViewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}

