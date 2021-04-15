/*--------------------------------------------------------------
 *  This example program demonstrates the SoEnvironment node.
 *
 *  Copyright 1995 Chris Buckalew   mod5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoEnvironment.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <stdio.h>
#include <stdlib.h>

SoNode* readIvFile()
{
   SoInput mySceneInput;
   if (!mySceneInput.openFile("palm.iv")) exit(-1);

   SoSeparator *node = SoDB::readAll(&mySceneInput);
   if (!node) exit(-1);
   
   mySceneInput.closeFile();

   return node;
}

void
main( int argc, char **argv )
{
  // Initialize Inventor. This will return a main window to use.
  // If unsuccessful, exit.
  Widget appWindow = SoXt::init(argv[0]); 
  if ( appWindow == NULL ) exit( 1 );

  SoSeparator* root = new SoSeparator;
  root->ref();
  SoDirectionalLight *light = new SoDirectionalLight;
  light->direction.setValue(-1.0, -1.0, 1.0);
  root->addChild(light);
  
  SoNode *node = readIvFile();

  SoEnvironment *env = new SoEnvironment;
  env->fogType.setValue(SoEnvironment::FOG);
  env->fogColor.setValue(0.5, 0.5, 0.35);
  root->addChild(env);

  SoTranslation *firstX = new SoTranslation;
  firstX->translation.setValue(-10.0, 0.0, 20.0);
  root->addChild(firstX);
  root->addChild(node);

  SoTranslation *secondX = new SoTranslation;
  secondX->translation.setValue(10.0, 0.0, -10.0);
  root->addChild(secondX);
  root->addChild(node);

  SoTranslation *thirdX = new SoTranslation;
  thirdX->translation.setValue(10.0, 0.0, -10.0);
  root->addChild(thirdX);
  root->addChild(node);

  SoXtExaminerViewer *sv = new SoXtExaminerViewer(appWindow);
  sv->setSize(SbVec2s(640, 480));
  sv->setBackgroundColor(SbColor(0.5, 0.5, 0.35));
  sv->setSceneGraph(root);
  sv->setTitle("SoEnvironment Example");
  sv->show();

  SoXt::show(appWindow); 
  SoXt::mainLoop();	
}
