/*
 * Copyright 1996, Portable Graphics, Inc., Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * IRIS GL and OpenGL are registered trademarks, and Inventor and
 * Open Inventor are trademarks of Silicon Graphics, Inc.
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Portable Graphics, Inc.,
 * 3006 Longhorn Blvd. Suite #105,  Austin, TX 78758-7631.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF PORTABLE GRAPHICS, INC. AND SILICON GRAPHICS, INC. ANY
 * DUPLICATION, MODIFICATION, DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN
 * WHOLE, OR IN PART, IS STRICTLY PROHIBITED WITHOUT THE PRIOR EXPRESS
 * WRITTEN  PERMISSION OF PORTABLE GRAPHICS, INC.
 */


// mazedoc.cpp : implementation of the CMazeDoc class
//
// mazedoc.cpp : implementation of the CMazeDoc class
//

#include "stdafx.h"
#include "maze.h"
#include "mazedoc.h"
void maze_init(SoSeparator * main_root, int argc, char *argv[]);
void resetMazeType(int maze_type);
void resetGame();
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc

IMPLEMENT_DYNCREATE(CMazeDoc, SoMfcDoc)

BEGIN_MESSAGE_MAP(CMazeDoc, SoMfcDoc)
	//{{AFX_MSG_MAP(CMazeDoc)
	ON_COMMAND(ID_GAME_MAZE1, OnGameMaze1)
	ON_COMMAND(ID_GAME_MAZE2, OnGameMaze2)
	ON_COMMAND(ID_GAME_MAZE3, OnGameMaze3)
	ON_COMMAND(ID_GAME_RESTART, OnGameRestart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc construction/destruction

CMazeDoc::CMazeDoc()
{
	// TODO: add one-time construction code here
}

CMazeDoc::~CMazeDoc()
{
}

BOOL CMazeDoc::OnNewDocument()
{
	if (!SoMfcDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle("Maze");
	SoSeparator *root = GetScene();	
	maze_init(root, 0, NULL);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc serialization

void CMazeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc diagnostics

#ifdef _DEBUG
void CMazeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMazeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMazeDoc commands

void CMazeDoc::OnGameMaze1() 
{
	// TODO: Add your command handler code here
	resetMazeType(1);
	SoMfcDoc::SetTitle("#1");
}

void CMazeDoc::OnGameMaze2() 
{
	// TODO: Add your command handler code here
	resetMazeType(2);
	SoMfcDoc::SetTitle("#2");

}

void CMazeDoc::OnGameMaze3() 
{
	// TODO: Add your command handler code here
	resetMazeType(3);
	SoMfcDoc::SetTitle("#3");

}

void CMazeDoc::OnGameRestart() 
{
	// TODO: Add your command handler code here
	resetGame();
}

void CMazeDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	SoMfcDoc::SetTitle("#1");
}
 