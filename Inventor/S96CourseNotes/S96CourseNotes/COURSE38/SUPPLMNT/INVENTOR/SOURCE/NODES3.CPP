/*--------------------------------------------------------------
 *  This example program demonstrates the Light-Model Node
 *
 *  This code displays models in BASE_COLOR and PHONG lighting
 *  model rendering
 *
 *  Copyright 1995 Chris Buckalew   mod5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoLightModel.h>
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

  SoTranslation *phongX = new SoTranslation;
  phongX->translation.setValue(-10.0, 0.0, 20.0);
  root->addChild(phongX);
  root->addChild(node);

  SoLightModel *lightModel = new SoLightModel;
  lightModel->model.setValue(SoLightModel::BASE_COLOR);
  root->addChild(lightModel);
  SoTranslation *baseX = new SoTranslation;
  baseX->translation.setValue(20.0, 0.0, -20.0);
  root->addChild(baseX);
  root->addChild(node);

  SoXtExaminerViewer *sv = new SoXtExaminerViewer;
  sv->setSize(SbVec2s(640, 480));
  sv->setSceneGraph(root);
  sv->setTitle("Light Model Example");
  sv->show();

  SoXt::show(appWindow);  
  SoXt::mainLoop();	
}
