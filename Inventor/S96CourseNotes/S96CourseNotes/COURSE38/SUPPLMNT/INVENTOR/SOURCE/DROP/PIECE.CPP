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
 |   $Revision: 1.1 $
 |
 |   Classes	: TsPiece
 |
 |   Author	: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

//--------------------------- Include ----------------------------------
#include "stdafx.h"
#include "TsPiece.h"

////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsPiece.
//
// Use: public

TsPiece::TsPiece()

//
////////////////////////////////////////////////////////////////////////
{
    orientation        = 0;
    numBlocks          = 0;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsPiece.
//
// Use: public

TsPiece::~TsPiece()

//
////////////////////////////////////////////////////////////////////////
{
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	This routine returns the list of positions of the blocks for the
//      piece in its current orientation.  The positions are specified as
//      indices into the standard 27-cube.  This method assumes that space
//      to store the returned indices is passed in.
//
// Use: public

int
TsPiece::getPosition(
        int pos[] )               // (out) the list of positions

// Values Returned:
//      number of blocks in the piece
//
////////////////////////////////////////////////////////////////////////
{
    int i;

    for (i=0; i<numBlocks; i++)
        pos[i] = piecePositionTable[orientation][i];

    return numBlocks;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	This routine returns the list of positions of the blocks for the
//      piece in the given orientation.  The positions are specified as
//      indices into the standard 27-cube.  This method assumes that space
//      to store the returned indices is passed in.
//
// Use: public

int
TsPiece::getPosition(
        int newOrientation,
        int pos[])               // (out) the list of positions

// Values Returned:
//      number of blocks in the piece
//
////////////////////////////////////////////////////////////////////////
{
    int i;

    for (i=0; i<numBlocks; i++)
        pos[i] = piecePositionTable[newOrientation][i];

    return numBlocks;
}




