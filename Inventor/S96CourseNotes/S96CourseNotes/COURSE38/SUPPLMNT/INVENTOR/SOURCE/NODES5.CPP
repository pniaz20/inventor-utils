/*--------------------------------------------------------------
 *  This example program demonstrates the SoComplexity node.
 *
 *  Copyright 1996 Chris Buckalew   mod5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/engines/SoCompose.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/nodes/SoRotor.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoComplexity.h>

void
main(int argc, char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
  myCamera->position.setValue(0.0, 20.0, 0);
  myCamera->pointAt(SbVec3f(0.0, 0.0, 0.0));
  myCamera->heightAngle = M_PI/2.5;
  myCamera->nearDistance = 1.0;
  myCamera->farDistance = 500.0;
  root->addChild(myCamera);
  root->addChild(new SoDirectionalLight);

  // this rotor will tesselate in screen space
  SoComplexity *complex1 = new SoComplexity;
  complex1->type.setValue(SoComplexity::SCREEN_SPACE);
  complex1->value.setValue(0.2);
  root->addChild(complex1);

  SoSphere *ball = new SoSphere;

  SoSeparator *rotor1Sep = new SoSeparator;
  SoMaterial *rotorMat = new SoMaterial;
  rotorMat->diffuseColor.setValue(0.3, 0.8, 0.8);
  rotorMat->specularColor.setValue(0.7, 0.7, 0.7);
  rotorMat->shininess = 0.8;
  rotor1Sep->addChild(rotorMat);
  SoRotor *rotor = new SoRotor;
  rotor->rotation.setValue(SbVec3f(0, 0, 1), 0);
  rotor->speed = 0.1;
  rotor1Sep->addChild(rotor);
  SoTranslation *rotor1X = new SoTranslation;
  rotor1X->translation.setValue(6.0, 0.0, 0.0);
  rotor1Sep->addChild(rotor1X);
  rotor1Sep->addChild(ball);
  root->addChild(rotor1Sep);

  // this rotor will tesselate in object space
  SoComplexity *complex2 = new SoComplexity;
  complex2->type.setValue(SoComplexity::OBJECT_SPACE);
  complex2->value.setValue(0.2);
  root->addChild(complex2);

  SoSeparator *rotor2Sep = new SoSeparator;
  SoMaterial *rotor2Mat = new SoMaterial;
  rotor2Mat->diffuseColor.setValue(0.8, 0.3, 0.8);
  rotor2Mat->specularColor.setValue(0.7, 0.7, 0.7);
  rotor2Mat->shininess = 0.8;
  rotor2Sep->addChild(rotor2Mat);
  rotor2Sep->addChild(rotor);
  SoTranslation *rotor2X = new SoTranslation;
  rotor2X->translation.setValue(6.0, 0.0, 3.0);
  rotor2Sep->addChild(rotor2X);
  rotor2Sep->addChild(ball);
  root->addChild(rotor2Sep);

  SoXtExaminerViewer *exViewer =
           new SoXtExaminerViewer(window);
  exViewer->setCamera(myCamera);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("SoComplexity Example");
  exViewer->show();

  SoXt::show(window);
  SoXt::mainLoop();
}

