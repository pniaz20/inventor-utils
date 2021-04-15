/*--------------------------------------------------------------
 *  This example program demonstrates different light
 *  types and their parameters.
 *
 *  Copyright 1995 Chris Buckalew   mod5/5/96
 *------------------------------------------------------------*/

#include <Inventor/SoInput.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoResetTransform.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoEnvironment.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoKeyboardEvent.h>

// three faces for corner
// need lots of facets because lights operate on vertices
#define SIDE 51
#define SIDESQUARE 2601
static float face1[SIDESQUARE][3];
static float face2[SIDESQUARE][3];
static float face3[SIDESQUARE][3];

#define MAXSTEP 7   // number of steps in cycle
int step = 0;
SbViewportRegion viewportRegion;

void
keyPressCB(void *userData, SoEventCallback *eventCB)
{
  // This function steps through the different light types
   
  SoSwitch *selection = (SoSwitch *) userData;
  const SoEvent *event = eventCB->getEvent();

  // check for the space bar
  if (SO_KEY_PRESS_EVENT(event, SPACE)) {
    step++;
    if (step>MAXSTEP) step = 0;         //reset
    selection->whichChild = step;
    eventCB->setHandled();
  }
}

SoSeparator *
generateCorner()
{
  // This generates three faces that make a corner, each a SIDExSIDE
  // quadmesh
  int i, j;

  for (i=0; i<SIDE; i++) 
    for (j=0; j<SIDE; j++) {
      face1[i*SIDE + j][0] = i/(SIDE-1.0);
      face1[i*SIDE + j][1] = j/(SIDE-1.0);
      face1[i*SIDE + j][2] = 0.0;

      face2[i*SIDE + j][0] = j/(SIDE-1.0);
      face2[i*SIDE + j][1] = 0;
      face2[i*SIDE + j][2] = i/(SIDE-1.0);

      face3[i*SIDE + j][0] = 0.0;
      face3[i*SIDE + j][1] = i/(SIDE-1.0);
      face3[i*SIDE + j][2] = j/(SIDE-1.0);
    }
  SoSeparator *walls = new SoSeparator;
  SoMaterial *faceMat = new SoMaterial;
  faceMat->ambientColor.setValue(0.4, 0.4, 0.4);
  faceMat->diffuseColor.setValue(1.0, 1.0, 1.0);
  walls->addChild(faceMat);

  // first face
  SoCoordinate3 *verts1 = new SoCoordinate3;
  verts1->point.setValues(0, SIDESQUARE, (const SbVec3f*) face1);
  walls->addChild(verts1);
  SoQuadMesh *mesh1 = new SoQuadMesh;
  mesh1->verticesPerRow = SIDE;
  mesh1->verticesPerColumn = SIDE;
  walls->addChild(mesh1);

  // second face
  SoCoordinate3 *verts2 = new SoCoordinate3;
  verts2->point.setValues(0, SIDESQUARE, (const SbVec3f*) face2);
  walls->addChild(verts2);
  SoQuadMesh *mesh2 = new SoQuadMesh;
  mesh2->verticesPerRow = SIDE;
  mesh2->verticesPerColumn = SIDE;
  walls->addChild(mesh2);

  // third face
  SoCoordinate3 *verts3 = new SoCoordinate3;
  verts3->point.setValues(0, SIDESQUARE, (const SbVec3f*) face3);
  walls->addChild(verts3);
  SoQuadMesh *mesh3 = new SoQuadMesh;
  mesh3->verticesPerRow = SIDE;
  mesh3->verticesPerColumn = SIDE;
  walls->addChild(mesh3);

  return walls;
}

SoSeparator *
generateMarker(SbVec3f location, SbColor color)
{
  // This function draws a little sphere to mark the location
  // of the light source
  SoSeparator *pt = new SoSeparator;
  SoMaterial *mat = new SoMaterial;
  mat->emissiveColor.setValue(color);
  SoTranslation *X = new SoTranslation;
  X->translation.setValue(location);
  SoSphere *point = new SoSphere;
  point->radius = 0.02;
  pt->addChild(mat);
  pt->addChild(new SoResetTransform);
  pt->addChild(X);
  pt->addChild(point);
  return pt;
}

SoSeparator *
demoLights()
{
  SbVec3f loc;
  SbColor color;

  SoSeparator *result = new SoSeparator;  
  SoSwitch *selection = new SoSwitch;
  result->addChild(selection);
  selection->whichChild = 0;

  SoEventCallback *eventCB = new SoEventCallback;
  eventCB->addEventCallback(
           SoKeyboardEvent::getClassTypeId(),
           keyPressCB, selection);
  result->addChild(eventCB);

  result->addChild(generateCorner());

  // define all the lights
  SoGroup *group0 = new SoGroup;
  SoDirectionalLight *light0 = new SoDirectionalLight;
  light0->direction.setValue(-4.0, -1.0, -0.3);
  light0->color.setValue(0.3, 0.8, 0.8);
  group0->addChild(light0);
  selection->addChild(group0);

  SoGroup *group1 = new SoGroup;
  SoDirectionalLight *light1 = new SoDirectionalLight;
  light1->direction.setValue(-1.0, -3.0, -2.0);
  light1->color.setValue(0.3, 0.8, 0.8);
  group1->addChild(light1);
  selection->addChild(group1);

  SoGroup *group2 = new SoGroup;
  SoGroup *b2 = new SoGroup;
  SoPointLight *light2 = new SoPointLight;
  loc.setValue(0.2, 0.2, 0.1);
  color.setValue(1.0, 0.2, 0.2);
  light2->location.setValue(loc);
  light2->color.setValue(color);
  b2->addChild(light2);
  b2->addChild(generateMarker(loc, color));
  group2->addChild(b2);
  selection->addChild(group2);

  SoGroup *group3 = new SoGroup;
  SoGroup *b3 = new SoGroup;
  SoPointLight *light3 = new SoPointLight;
  loc.setValue(0.5, 0.1, 0.5);
  color.setValue(0.2, 0.7, 0.2);
  light3->location.setValue(loc);
  light3->color.setValue(color);
  b3->addChild(light3);
  b3->addChild(generateMarker(loc, color));
  group3->addChild(b3);
  selection->addChild(group3);
  
  SoGroup *group4 = new SoGroup;
  SoGroup *b4 = new SoGroup;
  SoPointLight *light4 = new SoPointLight;
  loc.setValue(0.5, 0.1, 0.5);
  color.setValue(0.2, 0.7, 0.2);
  light4->location.setValue(loc);
  light4->color.setValue(color);
  SoEnvironment *attenuate = new SoEnvironment;
  attenuate->attenuation.setValue(5.0, 0.0, 0.0);
  b4->addChild(attenuate);
  b4->addChild(light4);
  b4->addChild(generateMarker(loc, color));
  group4->addChild(b4);
  selection->addChild(group4);

  SoGroup *group5 = new SoGroup;
  SoGroup *b5 = new SoGroup;
  SoSpotLight *light5 = new SoSpotLight;
  loc.setValue(0.4, 0.05, 0.4);
  color.setValue(1.0, 0.2, 1.0);
  light5->location.setValue(loc);
  light5->direction.setValue(-1.0, 0.0, 0.0);
  light5->dropOffRate = 0.1;
  light5->cutOffAngle = 0.5;
  light5->color.setValue(color);
  b5->addChild(light5);
  b5->addChild(generateMarker(loc, color));
  group5->addChild(b5);
  selection->addChild(group5);

  SoGroup *group6 = new SoGroup;
  SoGroup *b6 = new SoGroup;
  SoSpotLight *light6 = new SoSpotLight;
  loc.setValue(0.4, 0.05, 0.4);
  color.setValue(1.0, 0.2, 1.0);
  light6->location.setValue(loc);
  light6->direction.setValue(-1.0, 0.0, 0.0);
  light6->dropOffRate = 0.4;
  light6->cutOffAngle = 0.3;
  light6->color.setValue(color);
  b6->addChild(light6);
  b6->addChild(generateMarker(loc, color));
  group6->addChild(b6);
  selection->addChild(group6);

  SoGroup *group7 = new SoGroup;
  SoGroup *b7 = new SoGroup;
  SoSpotLight *light7 = new SoSpotLight;
  loc.setValue(0.4, 0.05, 0.4);
  color.setValue(1.0, 0.2, 1.0);
  light7->location.setValue(loc);
  light7->direction.setValue(-1.0, 0.0, 0.0);
  light7->dropOffRate = 0.7;
  light7->cutOffAngle = 0.1;
  light7->color.setValue(color);
  b7->addChild(light7);
  b7->addChild(generateMarker(loc, color));
  group7->addChild(b7);
  selection->addChild(group7);

  return result;
}

void  
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *persp = new SoPerspectiveCamera;
  persp->position.setValue(3.0, 3.0, 3.0);
  persp->pointAt(SbVec3f(0.0, 0.0, 0.0));
  persp->farDistance.setValue(20.0);
  root->addChild(persp);

  SoXtRenderArea *exViewer = 
           new SoXtRenderArea(window);

  exViewer->setSize(SbVec2s(640, 480));
  SbViewportRegion region(exViewer->getSize());
  persp->viewAll(root, region);

  // this function contains our code fragment
  root->addChild(demoLights());

  exViewer->setSceneGraph(root);
  exViewer->setTitle("Light Fields");
  exViewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}

