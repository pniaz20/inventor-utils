/*--------------------------------------------------------------
 *  This example program demonstrates normal binding as well
 *  as the effect of the crease angle field of SoShapeHints.
 *
 *  Copyright 1995 Chris Buckalew  modified 5/11/96
 *------------------------------------------------------------*/

#include <Inventor/Xt/SoXt.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoMaterialBinding.h>

static const float vertices[16][3] =
{{0.0, 0.0, 0.0}, {1.3, 0.0, 0.0}, {1.3, 1.1, 0.0}, {0.0, 1.1, 0.0},
 {0.0, 0.0, 0.5}, {1.3, 0.0, 0.5}, {1.3, 1.1, 0.5}, {0.0, 1.1, 0.5},
 {0.2, 0.25, 1.5}, {1.1, 0.25, 1.5}, {1.1, 0.85, 1.5}, {0.2, 0.85, 1.5},
 {0.1, 0.1, -0.01}, {1.2, 0.1, -0.01}, {1.2, 1.0, -0.01}, {0.1, 1.0, -0.01}
};

static const int indices[55] =
{0, 3, 2, 1, SO_END_FACE_INDEX,  //front
 0, 1, 5, 4, SO_END_FACE_INDEX,  //bottom
 3, 0, 4, 7, SO_END_FACE_INDEX,  //left
 1, 2, 6, 5, SO_END_FACE_INDEX,  //right
 2, 3, 7, 6, SO_END_FACE_INDEX,  //top
 //back end
 4, 5, 9, 8, SO_END_FACE_INDEX,   //bottome
 7, 4, 8, 11, SO_END_FACE_INDEX,   //left
 5, 6, 10, 9, SO_END_FACE_INDEX,  //right
 6, 7, 11, 10, SO_END_FACE_INDEX,  //top
 8, 9, 10, 11, SO_END_FACE_INDEX,  //back
 12, 13, 14, 15, SO_END_FACE_INDEX  //screen
};

//colors for the faces
static const float diffColors[11][3] = {
 {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9},
 {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9},
 {0.4, 0.9, 0.9}, {0.4, 0.9, 0.9}, {0.2, 0.2, 0.2}
};

SoSeparator *
generateCRT()
{
  // This function sets up the vertices and data for 
  // a CRT defined by a face set
  SoSeparator *crt = new SoSeparator;

  // plastic colors
  SoMaterial *plastics = new SoMaterial;
  plastics->diffuseColor.setValues(0, 11, diffColors);
  plastics->specularColor.setValue(1.0, 1.0, 1.0);
  plastics->shininess.setValue(0.2);
  crt->addChild(plastics);
  SoMaterialBinding *matBinding = new SoMaterialBinding;
  matBinding->value = SoMaterialBinding::PER_FACE;
  crt->addChild(matBinding);

  // vertex coordinates
  SoCoordinate3 *coords = new SoCoordinate3;
  coords->point.setValues(0, 16, vertices);
  crt->addChild(coords);

  // the faceset itself
  SoIndexedFaceSet *faceSet = new SoIndexedFaceSet;
  faceSet->coordIndex.setValues(0, 55, indices);
  crt->addChild(faceSet);
  
  return crt;
}

void
main(int , char **argv)
{
  // Initialize Inventor and Xt
  Widget window = SoXt::init(argv[0]);
  if (window == NULL) exit(1);

  SoSeparator *root = new SoSeparator;
  root->ref();

  // this function contains our code fragment
  SoSeparator *crt = generateCRT();
  SoShapeHints *hint1 = new SoShapeHints;
  hint1->creaseAngle = 0.0;
  root->addChild(hint1);
  root->addChild(crt);

  SoTranslation *rightX = new SoTranslation;
  rightX->translation.setValue(2.0, 0.0, 0.0);
  root->addChild(rightX);
  SoShapeHints *hint2 = new SoShapeHints;
  hint2->creaseAngle = 0.5;
  root->addChild(hint2);
  root->addChild(crt);
  
  SoXtExaminerViewer *exViewer = 
           new SoXtExaminerViewer(window);
  exViewer->setSize(SbVec2s(640, 480));
  exViewer->setSceneGraph(root);
  exViewer->setTitle("Crease Angle Example");
  exViewer->show();
  exViewer->viewAll();

  SoXt::show(window);
  SoXt::mainLoop();
}

