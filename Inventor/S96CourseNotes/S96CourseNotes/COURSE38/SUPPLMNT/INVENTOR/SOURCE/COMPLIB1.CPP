/*--------------------------------------------------------------
 *  This example program demonstrates the SoXtMaterialEditor
 *  component.
 *
 *  Copyright 1996 Chris Buckalew  mod5/10/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/Xt/SoXtMaterialEditor.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoTriangleStripSet.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoComplexity.h>

static const float earVerts[9][3] = {
	{1, 0, 0}, {0, 1, 0}, {0, 0.7, 0.7},
	{0, 0, 1}, {0, -0.7, 0.7}, {0, -1, 0},
	{0, -0.7, -0.7}, {0, 0, -1}, {0, 0.7, -0.7}
};

static const int earIndex[32] = {
	0, 1, 2, SO_END_FACE_INDEX,
	0, 2, 3, SO_END_FACE_INDEX,
	0, 3, 4, SO_END_FACE_INDEX,
	0, 4, 5, SO_END_FACE_INDEX,
	0, 5, 6, SO_END_FACE_INDEX,
	0, 6, 7, SO_END_FACE_INDEX,
	0, 7, 8, SO_END_FACE_INDEX,
	0, 8, 1, SO_END_FACE_INDEX
};

//colors for the faces - alternating red and white
static const float earColors[8][3] = {
    {0.8, 0.3, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.3}, {0.9, 0.9, 0.9}
};

static const float smileVerts[28][3] = {
	// front of smile
	{1, 0.8, 1}, {0.5, 1.25, 1}, {0.5, 0.25, 1},
	{0, 1, 1}, {-0, 0, 1}, {-0.5, 1.25, 1}, 
	{-0.5, 0.25, 1}, {-1, 0.8, 1},
	// top of smile
	{1, 0.8, 1}, {1, 0.8, 0},
    {0.5, 1.25, 1}, {0.5, 1.25, 0},
	{0, 1, 1}, {0, 1, 0}, 
	{-0.5, 1.25, 1}, {-0.5, 1.25, 0},
	{-1, 0.8, 1}, {-1, 0.8, 0},
	// bottom of smile
	{-1, 0.8, 1}, {-1, 0.8, 0},
	{-0.5, 0.25, 1}, {-0.5, 0.25, 0},
 	{0, 0, 1}, {0, 0, 0}, 
    {0.5, 0.25, 1}, {0.5, 0.25, 0},
	{1, 0.8, 1}, {1, 0.8, 0}

};

static const int smileIndex[3] = {
	8, 10, 10
};

static const float ruffVerts[34][3] = {
	{0, 2, 1}, {0.38, 2, 0.92}, {0.7, 2, 0.7}, {0.92, 2, 0.38}, 
	{1, 2, 0}, {0.92, 2, -0.38}, {0.7, 2, -0.7}, {0.38, 2, -0.92}, 
	{0, 2, -1}, {-0.38, 2, -0.92}, {-0.7, 2, -0.7}, {-0.92, 2, -0.38}, 
	{-1, 2, 0}, {-0.92, 2, 0.38}, {-0.7, 2, 0.7}, {-0.38, 2, 0.92}, {0, 2, 1}, 
	{0, 0, 2}, {0.57, 1, 1.38}, {1.84, 0, 1.84}, {1.38, 1, 0.57}, 
	{2, 0, 0}, {1.38, 1, -0.57}, {1.84, 0, -1.84}, {0.57, 1, -1.38}, 
	{0, 0, -2}, {-0.57, 1, -1.38}, {-1.84, 0, -1.84}, {-1.38, 1, -0.57}, 
	{-2, 0, 0}, {-1.38, 1, 0.57}, {-1.84, 0, 1.84}, {-0.57, 1, 1.38}, {0, 0, 2} 
};

static const float ruffColors[16][3] = {
    {0.8, 0.8, 0.3}, {0.9, 0.9, 0.9},
    {0.3, 0.8, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.8}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.8, 0.3}, {0.9, 0.9, 0.9},
    {0.3, 0.8, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.3}, {0.9, 0.9, 0.9},
    {0.8, 0.3, 0.8}, {0.9, 0.9, 0.9},
};

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  // this is the selection node
  SoSeparator *root = new SoSeparator;
  root->ref();

  // Face Set for ears
  SoSeparator *ears = new SoSeparator;

  // ear material
  SoMaterial *earM = new SoMaterial;
    earM->specularColor.setValue(0.2, 0.2, 0.2);
    earM->diffuseColor.setValues(0, 8, earColors);

  // each diffuse color is applied to a face in sequence
  SoMaterialBinding *earBind = new SoMaterialBinding;
  earBind->value = SoMaterialBinding::PER_FACE;
 
  // left ear transform
  SoTransform *ear1X = new SoTransform;
    ear1X->translation.setValue(-1.3, -2.5, 0.0);
	// rotate so point is to left
	ear1X->rotation.setValue(SbVec3f(0,1,0), M_PI);
    ear1X->scaleFactor.setValue(0.85, 0.95, 0.95);

  // ear shape Indexed Face Set
  // first define the coordinates
  SoCoordinate3 *earCoords = new SoCoordinate3;
  earCoords->point.setValues(0, 9, earVerts);
  // now the actual shape
  SoIndexedFaceSet *earFaceSet = new SoIndexedFaceSet;
  earFaceSet->coordIndex.setValues(0, 32, earIndex);

  // right ear transform
  SoTransform *ear2X = new SoTransform;
    ear2X->translation.setValue(-3.05, 0.0, 0.0);
	// rotate again so point is to right
	ear2X->rotation.setValue(SbVec3f(0,1,0), M_PI);
 
  // put ears together
  ears->addChild(earM);
  ears->addChild(earBind);
  ears->addChild(ear1X);
  ears->addChild(earCoords);
  ears->addChild(earFaceSet);
  ears->addChild(ear2X);
  ears->addChild(earFaceSet);

  // Clown's smile
  SoSeparator *smile = new SoSeparator;

  // smile material
  SoMaterial *smileM = new SoMaterial;
    smileM->specularColor.setValue(0.2, 0.2, 0.2);
    smileM->diffuseColor.setValue(1.0, 0.4, 0.2);

  // smile transform
  SoTransform *smileX = new SoTransform;
    smileX->translation.setValue(0.0, -4.4, 0.6);
    smileX->scaleFactor.setValue(0.7, 0.5, 1.0);
 
  // smile shape Triangle Set
  // first define the coordinates
  SoCoordinate3 *smileCoords = new SoCoordinate3;
  smileCoords->point.setValues(0, 28, smileVerts);
  // now the actual shape
  SoTriangleStripSet *smileStripSet = new SoTriangleStripSet;
  smileStripSet->numVertices.setValues(0, 3, smileIndex);

  // put smile together
  smile->addChild(smileM);
  smile->addChild(smileX);
  smile->addChild(smileCoords);
  smile->addChild(smileStripSet);

   // neck ruffle
  SoSeparator *ruff = new SoSeparator;

  // neck ruff material
  SoMaterial *ruffM = new SoMaterial;
    ruffM->specularColor.setValue(0.2, 0.2, 0.2);
    ruffM->diffuseColor.setValues(0, 16, ruffColors);

  // each diffuse color is applied to a face in sequence
  SoMaterialBinding *ruffBind = new SoMaterialBinding;
  ruffBind->value = SoMaterialBinding::PER_FACE;
 
  // nect ruff transform
  SoTransform *ruffX = new SoTransform;
    ruffX->translation.setValue(0.0, -6, 0.0);
    ruffX->scaleFactor.setValue(1.2, 0.7, 1.2);
 
  // neck ruffle Quad Mesh
  // first define the coordinates
  SoCoordinate3 *ruffCoords = new SoCoordinate3;
  ruffCoords->point.setValues(0, 34, ruffVerts);
  // now the actual shape
  SoQuadMesh *ruffMesh = new SoQuadMesh;
  ruffMesh->verticesPerRow = 17;
  ruffMesh->verticesPerColumn = 2;

  // put ruff together
  ruff->addChild(ruffM);
  ruff->addChild(ruffBind);
  ruff->addChild(ruffX);
  ruff->addChild(ruffCoords);
  ruff->addChild(ruffMesh);

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
  root->addChild(smile);
  root->addChild(ruff);
  root->addChild(hat);
  root->addChild(eyes);
  root->addChild(head);
  root->addChild(nose);

  // open the screen viewer
  SoXtMaterialEditor *headEdit = new SoXtMaterialEditor;
  headEdit->attach(headM);

  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Material Editor Example");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  headEdit->show();
  SoXt::mainLoop();
}

