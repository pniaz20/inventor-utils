/**************************************************************************
 *               Copyright (C) 1991-94, Silicon Graphics, Inc.            *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 **************************************************************************/

// Modified by Chris Buckalew  4/25/95

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/manips/SoHandleBoxManip.h>
#include <Inventor/manips/SoSpotLightManip.h>
#include <Inventor/manips/SoTransformBoxManip.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoResetTransform.h>

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>

// function prototypes
void selectionCallback(void *, SoPath *);
void deselectionCallback(void *, SoPath *);
void dragStartCallback(void *, SoDragger *);
void dragFinishCallback(void *, SoDragger *);

// global data
SoSeparator *root;
SoHandleBoxManip    *myHandleBox;
SoSpotLightManip    *spot;
SoTransformBoxManip *myTransformBox;
SoPath *handleBoxPath    = NULL;
SoPath *spotLightPath    = NULL;
SoPath *transformBoxPath = NULL;

void
main(int, char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  // create and set up the selection node
  SoSelection *selectionRoot = new SoSelection;
  selectionRoot->ref();
  selectionRoot->
     addSelectionCallback(selectionCallback, NULL);
  selectionRoot->
     addDeselectionCallback(deselectionCallback, NULL);

  // create the scene graph
  root = new SoSeparator;
  selectionRoot->addChild(root);

  // Create a cube with its own transform.
  SoGroup *cubeRoot = new SoGroup;
  SoTransform *cubeXform = new SoTransform;
  cubeXform->translation.setValue(-4, 0, 0);
  cubeXform->scaleFactor.setValue(0.25, 0.25, 0.25);
  root->addChild(cubeRoot);
  cubeRoot->addChild(cubeXform);

  SoSpotLight *spotLight = new SoSpotLight;
  spotLight->color.setValue(1.0, 0.5, 0.5);
  cubeRoot->addChild(spotLight);

  SoMaterial *cubeMat = new SoMaterial;
  cubeMat->diffuseColor.setValue(.5, 1.0, 1.0);
  cubeRoot->addChild(cubeMat);
  cubeRoot->addChild(new SoCube);

  // add a sphere node without a transform
  // (one will be added when we attach the manipulator)
  SoSeparator *sphereRoot = new SoSeparator;
  SoMaterial *sphereMat = new SoMaterial;
  root->addChild(new SoResetTransform);
  root->addChild(sphereRoot);
  //sphereRoot->addChild(new SoResetTransform);
  sphereRoot->addChild(sphereMat);
  SoComplexity *complexity = new SoComplexity;
  sphereRoot->addChild(complexity);
  complexity->value = 1.0;
  sphereRoot->addChild(new SoSphere);
  sphereMat->ambientColor.setValue(.4, .4, .4);
  sphereMat->diffuseColor.setValue(.8, .8, .8);

  // create the manipulators
  myHandleBox = new SoHandleBoxManip;
  myHandleBox->ref();
  spot = new SoSpotLightManip;
  spot->ref();

  // Get the draggers and add callbacks to them. Note
  // that you don't put callbacks on manipulators. You put
  // them on the draggers which handle events for them. 
  SoDragger *myDragger;
  myDragger = spot->getDragger();
  myDragger->addStartCallback(dragStartCallback,cubeMat);
  myDragger->addFinishCallback(dragFinishCallback,cubeMat);

  myDragger = myHandleBox->getDragger();
  myDragger->addStartCallback(dragStartCallback,sphereMat);
  myDragger->addFinishCallback(dragFinishCallback,sphereMat);

  SoXtExaminerViewer *myViewer 
     = new SoXtExaminerViewer(window);
  myViewer->setSize(SbVec2s(640, 480));

  myViewer->setSceneGraph(selectionRoot);
  myViewer->setTitle("Manipulators");
  myViewer->show();
  myViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}

// Is this node of a type that is influenced by transforms?
SbBool
isTransformable(SoNode *myNode)
{
   if (myNode->isOfType(SoGroup::getClassTypeId())
      || myNode->isOfType(SoShape::getClassTypeId())
      || myNode->isOfType(SoCamera::getClassTypeId())
      || myNode->isOfType(SoLight::getClassTypeId()))
      return TRUE;
   else 
      return FALSE;
}

//  Create a path to the transform node that affects the tail
//  of the input path.  Three possible cases:
//   [1] The path-tail is a node kit. Just ask the node kit for
//       a path to the part called "transform"
//   [2] The path-tail is NOT a group.  Search siblings of path
//       tail from right to left until you find a transform. If
//       none is found, or if another transformable object is 
//       found (shape,group,light,or camera), then insert a 
//       transform just to the left of the tail. This way, the 
//       manipulator only effects the selected object.
//   [3] The path-tail IS a group.  Search its children left to
//       right until a transform is found. If a transformable
//       node is found first, insert a transform just left of 
//       that node.  This way the manip will affect all nodes
//       in the group.
SoPath *
createSpotLightPath(SoPath *inputPath)
{
   int pathLength = inputPath->getLength();
   if (pathLength < 2) // Won't be able to get parent of tail
      return NULL;

   SoNode *tail = inputPath->getTail();

   SoSpotLight *editXf = NULL;
   SoGroup     *parent;
   SbBool      existedBefore = FALSE;

   // CASE 2: The tail is not a group.
   SbBool isTailGroup;
   isTailGroup = tail->isOfType(SoGroup::getClassTypeId());
   if (!isTailGroup) {
      // 'parent' is node above tail. Search under parent right
      // to left for a . 
      parent = (SoGroup *) inputPath->getNode(pathLength - 2);
      int tailIndx = parent->findChild(tail);

      for (int i = tailIndx; (i >= 0) && (editXf == NULL);i--){
         SoNode *myNode = parent->getChild(i);
         if (myNode->isOfType(SoSpotLight::getClassTypeId()))
            editXf = (SoSpotLight *) myNode;
      }
   }
   // CASE 3: The tail is a group.
   else {
      // Search the children from left to right for 
      // nodes. 
      parent = (SoGroup *) tail;
      for (int i = 0;
         (i < parent->getNumChildren()) && (editXf == NULL); 
	 i++) {
         SoNode *myNode = parent->getChild(i);
         if (myNode->isOfType(SoSpotLight::getClassTypeId()))
            editXf = (SoSpotLight *) myNode;
      }
   }

   // Create 'pathToXform.' Copy inputPath, then make last
   // node be editXf.
   SoPath *pathToSpotLight = NULL;
   pathToSpotLight = inputPath->copy();
   pathToSpotLight->ref();
   if (!isTailGroup) // pop off the last entry.
      pathToSpotLight->pop();
   // add editXf to the end
   int xfIndex   = parent->findChild(editXf);
   pathToSpotLight->append(xfIndex);
   pathToSpotLight->unrefNoDelete();

   return(pathToSpotLight);
}

SoPath *
createTransformPath(SoPath *inputPath)
{
   int pathLength = inputPath->getLength();
   if (pathLength < 2) // Won't be able to get parent of tail
      return NULL;

   SoNode *tail = inputPath->getTail();

   SoTransform *editXf = NULL;
   SoGroup     *parent;
   SbBool      existedBefore = FALSE;

   // CASE 2: The tail is not a group.
   SbBool isTailGroup;
   isTailGroup = tail->isOfType(SoGroup::getClassTypeId());
   if (!isTailGroup) {
      // 'parent' is node above tail. Search under parent right
      // to left for a transform. If we find a 'movable' node
      // insert a transform just left of tail.  
      parent = (SoGroup *) inputPath->getNode(pathLength - 2);
      int tailIndx = parent->findChild(tail);

      for (int i = tailIndx; (i >= 0) && (editXf == NULL);i--){
         SoNode *myNode = parent->getChild(i);
         if (myNode->isOfType(SoTransform::getClassTypeId()))
            editXf = (SoTransform *) myNode;
         else if (i != tailIndx && (isTransformable(myNode)))
            break;
      }
      if (editXf == NULL) {
	 existedBefore = FALSE;
         editXf = new SoTransform;
         parent->insertChild(editXf, tailIndx);
      }
      else
	 existedBefore = TRUE;
   }
   // CASE 3: The tail is a group.
   else {
      // Search the children from left to right for transform 
      // nodes. Stop the search if we come to a movable node.
      // and insert a transform before it.
      parent = (SoGroup *) tail;
      for (int i = 0;
         (i < parent->getNumChildren()) && (editXf == NULL); 
	 i++) {
         SoNode *myNode = parent->getChild(i);
         if (myNode->isOfType(SoTransform::getClassTypeId()))
            editXf = (SoTransform *) myNode;
         else if (isTransformable(myNode))
            break;
      }
      if (editXf == NULL) {
	 existedBefore = FALSE;
         editXf = new SoTransform;
         parent->insertChild(editXf, i);
      }
      else 
	 existedBefore = TRUE;
   }

   // Create 'pathToXform.' Copy inputPath, then make last
   // node be editXf.
   SoPath *pathToXform = NULL;
   pathToXform = inputPath->copy();
   pathToXform->ref();
   if (!isTailGroup) // pop off the last entry.
      pathToXform->pop();
   // add editXf to the end
   int xfIndex   = parent->findChild(editXf);
   pathToXform->append(xfIndex);
   pathToXform->unrefNoDelete();

   return(pathToXform);
}

// This routine is called when an object
// gets selected. We determine which object
// was selected, then call replaceNode()
// to replace the object's transform with
// a manipulator.
void
selectionCallback(
   void *, // user data is not used
   SoPath *selectionPath)
{
   // Attach the manipulator.
   // Use the convenience routine to get a path to
   // the transform that effects the selected object.

   // Attach the handle box to the sphere,
   // the trackball to the cube
   if (selectionPath->getTail()->isOfType(
        SoSphere::getClassTypeId())) {
      SoPath *xformPath = createTransformPath(selectionPath);
      if (xformPath == NULL) return;
      xformPath->ref();
      handleBoxPath = xformPath;
      myHandleBox->replaceNode(xformPath);
   }
   else if (selectionPath->getTail()->
        isOfType(SoCube::getClassTypeId())) {
      SoPath *xformPath = createSpotLightPath(selectionPath);
      if (xformPath == NULL) return;
      xformPath->ref();
      spotLightPath = xformPath;
      spot->replaceNode(xformPath);
   }
}

// This routine is called whenever an object gets
// deselected. It detaches the manipulator from
// the transform node, and removes it from the 
// scene graph that will not be visible.
void
deselectionCallback(
   void *, // user data is not used
   SoPath *deselectionPath)
{
   if (deselectionPath->getTail()->
        isOfType(SoSphere::getClassTypeId())) {
      myHandleBox->replaceManip(handleBoxPath,NULL);
      handleBoxPath->unref();
   }
   else if (deselectionPath->getTail()->
        isOfType(SoCube::getClassTypeId())) {
      spot->replaceManip(spotLightPath,NULL);
      spotLightPath->unref();
   }
}

// This is called when a manipulator is
// about to begin manipulation.
void
dragStartCallback(
   void *myMaterial, // user data
   SoDragger *)         // callback data not used
{
   ((SoMaterial *) myMaterial)->diffuseColor=SbColor(1,.2,.2);
}

// This is called when a manipulator is
// done manipulating.
void
dragFinishCallback(
   void *myMaterial, // user data
   SoDragger *)    // callback data not used
{
   ((SoMaterial *) myMaterial)->diffuseColor=SbColor(.8,.8,.8);
}
