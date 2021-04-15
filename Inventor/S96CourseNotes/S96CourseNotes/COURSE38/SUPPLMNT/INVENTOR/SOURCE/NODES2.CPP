/*--------------------------------------------------------------
 *  This example program demonstrates the Draw-Style node.
 *
 *  This code displays models in FILLED, LINE, and POINT modes
 *
 *  Copyright 1995 Chris Buckalew   mod5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/SoDB.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoDrawStyle.h>
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

  SoTranslation *polysX = new SoTranslation;
  polysX->translation.setValue(-10.0, 0.0, 20.0);
  root->addChild(polysX);
  root->addChild(node);

  SoDrawStyle *lineStyle = new SoDrawStyle;
  lineStyle->style.setValue(SoDrawStyle::LINES);
  root->addChild(lineStyle);
  SoTranslation *linesX = new SoTranslation;
  linesX->translation.setValue(10.0, 0.0, -10.0);
  root->addChild(linesX);
  root->addChild(node);

  SoDrawStyle *pointStyle = new SoDrawStyle;
  pointStyle->style.setValue(SoDrawStyle::POINTS);
  root->addChild(pointStyle);
  SoTranslation *pointsX = new SoTranslation;
  pointsX->translation.setValue(10.0, 0.0, -10.0);
  root->addChild(pointsX);
  root->addChild(node);

  SoXtExaminerViewer *viewer = new SoXtExaminerViewer;
  viewer->setSize(SbVec2s(640, 480));
  viewer->setSceneGraph(root);
  viewer->setTitle("Draw-Style Example");
  viewer->show();

  SoXt::show(appWindow); 
  SoXt::mainLoop();	
}
