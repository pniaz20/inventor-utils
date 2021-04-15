/*
 * Copyright 1991-1995, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
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
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
/*
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.2 $
 |
 |   Methods	: TsField::handleKeyboard
 |
 |   Author	: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

//--------------------------- Include ----------------------------------
#include "stdafx.h"
 
#include "TsField.h"
#include "dropDoc.h"
#include "MainFrm.h"

////////////////////////////////////////////////////////////////////////
//
// Description:
//	This routine handles all keyboard events that move the pieces as
//      they fall.
//
// Use: private, static

void
TsField::handleKeyboard( void *data, SoEventCallback *node )

//
////////////////////////////////////////////////////////////////////////
{
    TsField       *field = (TsField *)data;

#if 1 
	// jlr - not working!
    if (SO_KEY_PRESS_EVENT(node->getEvent(), RETURN)) {
#else
	if (1) {
#endif
        field->gameStarted = TRUE;
        field->handleReturnKey();
        node->setHandled();
        return;
    }

    // If the game has been paused, don't accept any input.  Just return.
    // (Also, don't accept input if the game has not started.)
    if (field->gamePaused || !field->gameStarted) {
        node->setHandled();
        return;
    }
    
    if (SO_KEY_PRESS_EVENT(node->getEvent(), LEFT_ARROW))
        field->translation (TS_X_AXIS, -1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), RIGHT_ARROW))
        field->translation (TS_X_AXIS,  1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), UP_ARROW))
        field->translation (TS_Z_AXIS,  1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), DOWN_ARROW))
        field->translation (TS_Z_AXIS, -1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), F))
        field->rotation (TS_Z_AXIS,   1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), S))
        field->rotation (TS_Z_AXIS,  -1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), D))
        field->rotation (TS_Y_AXIS,  1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), C))
        field->rotation (TS_X_AXIS,  -1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), E))
        field->rotation (TS_X_AXIS,   1);
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), SPACE))
        field->dropPiece();
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), H)) 
        field->handleHelpKey();
    else if (SO_KEY_PRESS_EVENT(node->getEvent(), P)) 
        field->handleHelpKey();


    node->setHandled();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//	This routine handles the return key press.
//
// Use: public

void
TsField::handleReturnKey()

//
////////////////////////////////////////////////////////////////////////
{
    // If help had been displayed, either start the first game
    // or resume a game in progress.
    if (helpDisplayed) {
        helpDisplayed = FALSE;
        helpRoot->removeChild(helpGroup); //old:overRoot->removeChild(helpRoot)

		
        if (isGameOver) 
            startNewGame();
        else
            resumeGame();
    }
    else {
        // Start a new game
        startNewGame();
    }
}

void
TsField::setStatusText(const char *text)
{

	POSITION pos = dropDoc->GetFirstViewPosition();
	CView* pView = dropDoc->GetNextView( pos );
 	CMainFrame *pFrame = (CMainFrame *)(pView->GetParentFrame());

	ASSERT(pFrame);

	CStatusBar *pStatus = &pFrame->m_wndStatusBar;

	ASSERT(pStatus);
	// pStatus->SetPaneText(1, text, TRUE);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//	This routine handles the H key press.
//
// Use: public

void
TsField::handleHelpKey()

//
////////////////////////////////////////////////////////////////////////
{
    // If the help message is not displayed, add the help message geometry
    // to the scene graph and pause the game.
    if (!helpDisplayed) {
        helpRoot->addChild(helpGroup); //old: overRoot->addChild(helpRoot);
        helpDisplayed = TRUE;
        pauseGame();
    }
}
