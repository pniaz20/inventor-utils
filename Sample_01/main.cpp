/***************************************************************
 * Sample Graphical Project
 * Creates a SoWin Window 
 * Author: Pouya Pourakbarian Niaz
 ***************************************************************/

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSphere.h>
#include <iostream>
using namespace std;

int main(int, char ** argv)
{
	// Draw the object read from the file
  	HWND window = SoWin::init(argv[0]);
  	if ( window == NULL ) 
  		exit(1);

  	SoWinExaminerViewer *viewer = new SoWinExaminerViewer(window);
    SoSeparator* root = new SoSeparator;;
    SoSeparator* sphereSep = new SoSeparator;
    SoSphere* sphere = new SoSphere;
    sphere->radius = 0.00001;
    SoSeparator* object = new SoSeparator;
    SoTransform* trans = new SoTransform;

	SoInput sceneInput;
	if ( !sceneInput.openFile( "jackbox.iv" ) ) {
        cout << "Cannot open input file, displaying empty scene" << endl;
	}
	else
	{
  		object = SoDB::readAll( &sceneInput );
	}


    root->addChild(object);
    root->addChild(trans);
    root->addChild(sphere);


    
	
  	viewer->setSceneGraph(root);
  	viewer->setTitle("Sample Project");
  	viewer->show();

  	SoWin::show(window);
  	SoWin::mainLoop();

  	return 0;
}
