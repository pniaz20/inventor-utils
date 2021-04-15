/**************************************************************************
 * 		 Copyright (C) 1991-94, Silicon Graphics, Inc.		  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 **************************************************************************/

/*--------------------------------------------------------------
 *  This is an example from the Inventor Mentor
 *  chapter 2, example 2.
 *
 *  Use an engine to make the cone spin.
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>

void
main(int , char **argv)
{
   // Initialize Inventor and Xt
   Widget myWindow = SoXt::init(argv[0]);  
   if (myWindow == NULL) exit(1);     

   SoSeparator *root = new SoSeparator;
   root->ref();
   SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
   root->addChild(myCamera);
   root->addChild(new SoDirectionalLight);

   // This transformation is modified to rotate the cone
   SoRotationXYZ *myRotXYZ = new SoRotationXYZ;
   root->addChild(myRotXYZ);

   SoMaterial *myMaterial = new SoMaterial;
   myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);   // Red
   root->addChild(myMaterial);
   root->addChild(new SoCone);

   // An engine rotates the object. The output of myCounter 
   // is the time in seconds since the program started.
   // Connect this output to the angle field of myRotXYZ
   myRotXYZ->axis = SoRotationXYZ::X;     // rotate about X axis
   SoElapsedTime *myCounter = new SoElapsedTime;
   myRotXYZ->angle.connectFrom(&myCounter->timeOut);

   SoXtRenderArea *myRenderArea = new SoXtRenderArea(myWindow);
   myRenderArea->setSize(SbVec2s(640, 480));

   myCamera->viewAll(root, myRenderArea->getViewportRegion());
   myRenderArea->setSceneGraph(root);
   myRenderArea->setTitle("Engine Spin");
   myRenderArea->show();

   SoXt::show(myWindow);
   SoXt::mainLoop();
}
