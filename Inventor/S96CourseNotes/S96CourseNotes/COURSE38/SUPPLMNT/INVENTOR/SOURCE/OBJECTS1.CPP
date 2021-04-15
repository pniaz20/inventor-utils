/*--------------------------------------------------------------
 *  This example program demonstrates the construction of
 *  a Face Set.  The clown's ears are faceted pyramidal
 *  face sets.
 *
 *  Copyright 1996 Chris Buckalew  mod5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoComplexity.h>

static const float earVerts[24][3] = {
	{1, 0, 0}, {0, 1, 0}, {0, 0.7, 0.7},
	{1, 0, 0}, {0, 0.7, 0.7}, {0, 0, 1},
	{1, 0, 0}, {0, 0, 1}, {0, -0.7, 0.7},
	{1, 0, 0}, {0, -0.7, 0.7}, {0, -1, 0},
	{1, 0, 0}, {0, -1, 0}, {0, -0.7, -0.7},
	{1, 0, 0}, {0, -0.7, -0.7}, {0, 0, -1},	
	{1, 0, 0}, {0, 0, -1}, {0, 0.7, -0.7},
	{1, 0, 0}, {0, 0.7, -0.7}, {0, 1, 0}
};

static int numEarVerts[8] = {3, 3, 3, 3, 3, 3, 3, 3};

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoGroup *root = new SoGroup;
  root->ref();

  // Face Set for ears
  SoSeparator *ears = new SoSeparator;

  // ear material
  SoMaterial *earM = new SoMaterial;
    earM->diffuseColor.setValue(0.7, 0.3, 0.3);
    earM->specularColor.setValue(0.2, 0.2, 0.2);

  // left ear transform
  SoTransform *ear1X = new SoTransform;
    ear1X->translation.setValue(-1.3, -2.5, 0.0);
	// rotate so point is to left
	ear1X->rotation.setValue(SbVec3f(0,1,0), M_PI);
    ear1X->scaleFactor.setValue(0.85, 0.95, 0.95);

  // ear shape Face Set
  // first define the coordinates
  SoCoordinate3 *earCoords = new SoCoordinate3;
  earCoords->point.setValues(0, 28, earVerts);
  // now the actual shape
  SoFaceSet *earFaceSet = new SoFaceSet;
  earFaceSet->numVertices.setValues(0, 8, numEarVerts);

  // right ear transform
  SoTransform *ear2X = new SoTransform;
    ear2X->translation.setValue(-3.05, 0.0, 0.0);
	// rotate again so point is to right
	ear2X->rotation.setValue(SbVec3f(0,1,0), M_PI);
 
  // put ears together
  ears->addChild(earM);
  ears->addChild(ear1X);
  ears->addChild(earCoords);
  ears->addChild(earFaceSet);
  ears->addChild(ear2X);
  ears->addChild(earFaceSet);

  // hat
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
  root->addChild(ears);
  root->addChild(hat);
  root->addChild(eyes);
  root->addChild(head);
  root->addChild(nose);

  // open the screen viewer
  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Face Set Example");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}

