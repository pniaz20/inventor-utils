/*--------------------------------------------------------------
 *  This example program demonstrates the Rotor, Pendulum, 
 *  Shuttle, and Blinker nodes.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *------------------------------------------------------------*/

#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/nodes/SoRotor.h>
#include <Inventor/nodes/SoPendulum.h>
#include <Inventor/nodes/SoShuttle.h>
#include <Inventor/nodes/SoBlinker.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSphere.h>

void
main(int argc, char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);  
  if (window == NULL) exit(1);     

  SoSeparator *root = new SoSeparator;
  root->ref();

  SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
  myCamera->position.setValue(0.0, 0.0, 12.0);
  myCamera->pointAt(SbVec3f(0.0, 0.0, 0.0));
  myCamera->heightAngle = M_PI/2.5; 
  myCamera->nearDistance = 1.0;
  myCamera->farDistance = 50.0;
  root->addChild(myCamera);
  root->addChild(new SoDirectionalLight);

  SoSphere *ball = new SoSphere;

  SoSeparator *rotorSep = new SoSeparator;
  SoMaterial *rotorMat = new SoMaterial;
  rotorMat->diffuseColor.setValue(1.0, 1.0, 0.5);
  rotorMat->specularColor.setValue(0.7, 0.7, 0.7);
  rotorMat->shininess = 0.8;
  rotorSep->addChild(rotorMat);
  SoRotor *rotor = new SoRotor;
  rotor->rotation.setValue(SbVec3f(0, 0, 1), 0);
  rotor->speed = 0.2;
  rotorSep->addChild(rotor);
  SoTranslation *rotorX = new SoTranslation;
  rotorX->translation.setValue(6.0, 0.0, 0.0);
  rotorSep->addChild(rotorX);
  rotorSep->addChild(ball);
  root->addChild(rotorSep);

  SoSeparator *pendulumSep = new SoSeparator;
  SoMaterial *pendulumMat = new SoMaterial;
  pendulumMat->diffuseColor.setValue(1.0, 0.5, 1.0);
  pendulumMat->specularColor.setValue(0.7, 0.7, 0.7);
  pendulumMat->shininess = 0.8;
  pendulumSep->addChild(pendulumMat);
  SoPendulum *pendulum = new SoPendulum;
  pendulum->rotation0.setValue(SbVec3f(0, 0, 1), M_PI*1.5 - (M_PI/4));
  pendulum->rotation1.setValue(SbVec3f(0, 0, 1), M_PI*1.5 + (M_PI/4));
  pendulum->speed = 0.2;
  pendulumSep->addChild(pendulum);
  SoTranslation *pendulumX = new SoTranslation;
  pendulumX->translation.setValue(4.0, 0.0, 0.0);
  pendulumSep->addChild(pendulumX);
  pendulumSep->addChild(ball);
  root->addChild(pendulumSep);

  SoSeparator *shuttleSep = new SoSeparator;
  SoMaterial *shuttleMat = new SoMaterial;
  shuttleMat->diffuseColor.setValue(0.5, 1.0, 0.5);
  shuttleMat->specularColor.setValue(0.7, 0.7, 0.7);
  shuttleMat->shininess = 0.8;
  shuttleSep->addChild(shuttleMat);
  SoShuttle *shuttle = new SoShuttle;
  shuttle->translation0.setValue(-3.0, 3.0, 0.0);
  shuttle->translation1.setValue( 3.0, 3.0, 0.0);
  shuttle->speed = 0.2;
  shuttleSep->addChild(shuttle);
  shuttleSep->addChild(ball);
  root->addChild(shuttleSep);

  SoSeparator *blinkerSep = new SoSeparator;
  SoBlinker *blinker = new SoBlinker;
  blinker->speed = 0.2;
  blinkerSep->addChild(blinker);

  SoSeparator *blink1 = new SoSeparator;
  SoMaterial *blinkerMat1 = new SoMaterial;
  blinkerMat1->diffuseColor.setValue(0.5, 0.7, 1.0);
  blinkerMat1->specularColor.setValue(0.7, 0.7, 0.7);
  blinkerMat1->shininess = 0.8;
  blink1->addChild(blinkerMat1);
  SoTranslation *blink1X = new SoTranslation;
  blink1X->translation.setValue(3.0, 0.0, 0.0);
  blink1->addChild(blink1X); 
  blink1->addChild(ball); 
  blinker->addChild(blink1);

  SoSeparator *blink2 = new SoSeparator;
  SoMaterial *blinkerMat2 = new SoMaterial;
  blinkerMat2->diffuseColor.setValue(0.7, 0.5, 1.0);
  blinkerMat2->specularColor.setValue(0.7, 0.7, 0.7);
  blinkerMat2->shininess = 0.8;
  blink2->addChild(blinkerMat2);
  SoTranslation *blink2X = new SoTranslation;
  blink2X->translation.setValue(-3.0, 0.0, 0.0);
  blink2->addChild(blink2X); 
  blink2->addChild(ball); 
  blinker->addChild(blink2);

  root->addChild(blinkerSep);

  SoXtRenderArea *renderArea = new SoXtRenderArea(window);
  renderArea->setSize(SbVec2s(640, 480));

  SbViewportRegion region(renderArea->getSize()); 
  renderArea->setSceneGraph(root);
  renderArea->setTitle("Rotor, Pendulum, Shuttle, and Blinker Example");
  renderArea->show();

  SoXt::show(window);
  SoXt::mainLoop();
}
