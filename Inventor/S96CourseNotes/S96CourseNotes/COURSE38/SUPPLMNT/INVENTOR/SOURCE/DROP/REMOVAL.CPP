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
 |   Classes	: TsField::removeRows
 |                TsField::shiftRows
 |                TsField::endShift
 |
 |   Author	: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

//--------------------------- Include ----------------------------------
#include "stdafx.h"
#include "TsField.h"

#define FILL_HIGHLIGHT_DURATION    1.0
#define REMOVAL_ANIMATE            1
#define REMOVAL_DROP_RATE          4.0
#define LEVELS_REQUIRED            4

static int currentRemoval;

////////////////////////////////////////////////////////////////////////
//
// Description:
//	This callback routine for the removalSensor alarm sensor will be
//      called after a period of time.  The routine removes all completed
//      rows and shedules a timer sensor used to animate the remaining
//      rows downward.
//
// Use: public

void
TsField::removeRows( void *data, SoSensor * )

//
////////////////////////////////////////////////////////////////////////
{
    TsField     *field = (TsField *)data;
    int         i;

    // 
    // For each row being removed, replace the level node with a removal
    // translation node and restore the original level material.
    //
    SoSeparator *levelSep;
    for (i=0; i<field->numRemovals; i++)
    {
        field->otherBlocks->replaceChild(
                field->levelGroup[field->removalList[i]],
                field->removalTranslation[i]);

        levelSep = (SoSeparator *)field->levelGroup[field->removalList[i]];
        levelSep->replaceChild (field->removalMaterial,
                             field->levelMaterial[field->removalList[i]]);
    }


    // Initialize the removal translation nodes
    SoTranslation *rt;
    for (i=0; i<3; i++)
    {
        rt = (SoTranslation *)field->removalTranslation[i];
        rt->translation.setValue (0.0, 0.0, 0.0);
    }

    // Schedule a timer sensor to animate the remaining rows downward
    currentRemoval = 0;
    field->currentFraction = 0.0;
    field->wallClock.setToTimeOfDay();
    field->shiftSensor->schedule();    
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	This callback routine for the shiftSensor alarm sensor animates
//      the remaining rows downward.  When all shifting has been finished,
//      the timer is unscheduled and a new piece is put into play.
//
// Use: static, private

void
TsField::shiftRows( void *data, SoSensor * )

//
////////////////////////////////////////////////////////////////////////
{
    TsField       *field = (TsField *)data;
    SoTranslation *rt;
    SbTime        elapsedTime;
    float         tmpFraction, shiftDistance;
    time_t        clockSeconds;
    long          clockMSeconds;		// System long

    //
    // Calculate the distance the rows should fall.  This is calculated
    // given the change in time and the rate at which the piece is falling.
    // The distance is expressed as a value from 0.0 to -2.0.  This represents
    // the intermediate distance from one integer position to the next.
    //
    elapsedTime.setToTimeOfDay();
    elapsedTime -= field->wallClock;
    field->wallClock.setToTimeOfDay();
    elapsedTime.getValue (clockSeconds, clockMSeconds);
    shiftDistance = (clockSeconds + clockMSeconds * 1e-6) * REMOVAL_DROP_RATE;
    tmpFraction = field->currentFraction - shiftDistance;

    if (tmpFraction > -2.0)
    {
        //
        // Just translate down.
        //
        field->currentFraction = tmpFraction;
    }
    else
    {
        while (tmpFraction < -2.0)
        {
            //
            // The rows have crossed an integer boundary.
            // assign -2 to the current removal translation and increment the
            // current removal translation.  If there are no more rows to be
            // translated stop the animation and update the database.
            //
            rt = (SoTranslation *)field->removalTranslation[currentRemoval];
            rt->translation.setValue (0.0, -2.0, 0.0);
            if (++currentRemoval == field->numRemovals)
            {
                field->shiftSensor->unschedule();
                field->endShift();
                return;
            }

            // Assign any extra animation difference to the next removal
            // translation.        
            rt = (SoTranslation *)field->removalTranslation[currentRemoval];
            rt->translation.setValue (0.0, tmpFraction + 2.0, 0.0);

            tmpFraction += 2.0;
            field->currentFraction = tmpFraction;
        }
        return;
    }

    // Update the correct removalTranslation node to move the rows downward.
    rt = (SoTranslation *)field->removalTranslation[currentRemoval];
    const SbVec3f &tpos =  rt->translation.getValue ();
    SbVec3f spos;
    spos[0] = tpos[0];
    spos[1] = tpos[1] - shiftDistance;
    spos[2] = tpos[2];
    rt->translation.setValue (spos);
}




////////////////////////////////////////////////////////////////////////
//
// Description:
//	This routine updates the database and fieldTable after completed
//      rows have been removed.
//
// Use: private

void
TsField::endShift()

//
////////////////////////////////////////////////////////////////////////
{
    SoSeparator *lg;
    int i, j, n;

    //
    // replace the completed rows back into the scene graph and remove
    // all of their block children.
    //
    for (i=0; i<numRemovals; i++)
    {
        lg = (SoSeparator *)levelGroup[removalList[i]];
        otherBlocks->replaceChild (removalTranslation[i], lg);

        for (j=0; j<(resolution*resolution); j++)
            lg->removeChild(2);
    }

    //
    // For each empty row, loop through the rows above and shift their
    // children down one row.  Shift the fieldTable values down one row
    // as well.
    //
    SoSeparator *next;
    SoNode      *blk;
    int         level, fieldPos;
    int         rr = resolution * resolution;

    for (i=numRemovals; --i>=0;)
    {
        lg = (SoSeparator *)levelGroup[removalList[i]];
        fieldPos = removalList[i] * rr;
        for (level=removalList[i]+1; level<=currentHeight; level++, lg = next)
        {
            // Shift the block children down one row
            next = (SoSeparator *)levelGroup[level];
            n = next->getNumChildren();
            for (j=0; j<(n-2); j++)
            {
                blk = next->getChild(2);
                next->removeChild(blk);
                lg->addChild(blk);
            }

            // Shift the fieldTable values down one row
            for (j=0; j<rr; j++, fieldPos++)
                fieldTable[fieldPos] = fieldTable[fieldPos+rr];
        }

        // Clear the top level of the field and reduce the currentHeight
        for (j=0; j<rr; j++, fieldPos++)
            fieldTable[fieldPos] = 0;
        --currentHeight;
    }
    numRemovals = 0;

    // Reattach the falling piece to the scene graph
    fieldRoot->insertChild (fallingRoot, 2);

    // Add a new piece to the playing field.
    addPoints( pointsEarned );
    pointsEarned = 0;
    addPiece ();
}





