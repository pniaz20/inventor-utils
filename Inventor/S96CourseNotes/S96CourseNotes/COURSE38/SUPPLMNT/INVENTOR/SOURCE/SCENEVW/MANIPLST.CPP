/**************************************************************************
 * 		 Copyright (C) 1991-94, Silicon Graphics, Inc.		  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 **************************************************************************/

/*
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 * 
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.4 $
 |
 |   Classes:	SvManipList
 |
 |   Author(s):	David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include /**/ <Inventor/SbPList.h>
#include /**/ <Inventor/SoPath.h>
#include /**/ <Inventor/nodes/SoGroup.h>
#include /**/ <Inventor/manips/SoTransformManip.h>
#include "manipLst.h"


typedef struct SvPathManipStuff {
    SoPath	     *selectionPath;
    SoTransformManip *manip;
    SoPath           *xfPath;
} SvPathManipStuff;

////////////////////////////////////////////////////////////////////////
//
// Constructor
//
// Use: public
SvManipList::SvManipList()
//
////////////////////////////////////////////////////////////////////////
{
    list = new SbPList;
}

////////////////////////////////////////////////////////////////////////
//
// Destructor
//
// Use: public
SvManipList::~SvManipList()
//
////////////////////////////////////////////////////////////////////////
{
	for (int i = 0; (i < list->getLength()); i++)
	{
		remove( i );    
	}

    delete list;
}

////////////////////////////////////////////////////////////////////////
//
// Use: public
int
SvManipList::getLength() const
//
////////////////////////////////////////////////////////////////////////
{
    return list->getLength();
}

////////////////////////////////////////////////////////////////////////
//
// Append adds the selectionPath/manip/xfPath stuff to the list.
// This ref()'s both the paths and the manip.
//
// Use: public
void
SvManipList::append(SoPath *selectionP, SoTransformManip *m, 
		    SoPath *xfP )
//
////////////////////////////////////////////////////////////////////////
{
    SvPathManipStuff *stuff = new SvPathManipStuff;
    
    stuff->selectionPath = selectionP;
    stuff->manip = m;
    stuff->xfPath = xfP;
    selectionP->ref();
    m->ref();
    xfP->ref();
    
    list->append(stuff);
}

////////////////////////////////////////////////////////////////////////
//
// Find locates the first selectionPath/manip/xfPath stuff whose 
// selectionPath is p, and returns the index in the list of that stuff.
//
// Use: public
int
SvManipList::find(const SoPath *p) const
//
////////////////////////////////////////////////////////////////////////
{
    int which = -1;
    
    for (int i = 0; (i < list->getLength()) && (which == -1); i++) {
	SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[i];
	if (*stuff->selectionPath == *p)
	    which = i;
    }
    
    return which;
}

////////////////////////////////////////////////////////////////////////
//
// Find locates the first selectionPath/manip/xfPath stuff whose manip is m,
// and returns the index in the list of that stuff.
//
// Use: public
int
SvManipList::find(const SoTransformManip *m) const
//
////////////////////////////////////////////////////////////////////////
{
    int which = -1;
    
    for (int i = 0; (i < list->getLength()) && (which == -1); i++) {
	SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[i];
	if (stuff->manip == m)
	    which = i;
    }
    
    return which;
}

////////////////////////////////////////////////////////////////////////
//
// findByXfPath locates the first selectionPath/manip/xfPath stuff whose 
// xfPath is p, and returns the index in the list of that stuff.
//
// Use: public
int
SvManipList::findByXfPath(const SoPath *p) const
//
////////////////////////////////////////////////////////////////////////
{
    int which = -1;
    
    for (int i = 0; (i < list->getLength()) && (which == -1); i++) {
	SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[i];
	if (*stuff->xfPath == *p)
	    which = i;
    }
    
    return which;
}

////////////////////////////////////////////////////////////////////////
//
// Remove removes the selectionPath/manip/xfPath stuff specified by 
// which index from the list. This unref()'s both paths and the manip.
//
// Use: public
void
SvManipList::remove(int which)
//
////////////////////////////////////////////////////////////////////////
{
    SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[which];
    
    stuff->selectionPath->unref();
    stuff->manip->unref();
    stuff->xfPath->unref();
    
    list->remove(which);
	delete stuff;
}

////////////////////////////////////////////////////////////////////////
//
// This returns the selectionPath in the selectionPath/manip/xfPath stuff 
// specified by which index.
//
// Use: public
SoPath *
SvManipList::getSelectionPath(int which) const
//
////////////////////////////////////////////////////////////////////////
{
    SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[which];
    return (stuff->selectionPath);
}

////////////////////////////////////////////////////////////////////////
//
// This returns the manip in the selectionPath/manip/xfPath stuff 
// specified by which index.
//
// Use: public
SoTransformManip *
SvManipList::getManip(int which) const
//
////////////////////////////////////////////////////////////////////////
{
    SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[which];
    return (stuff->manip);
}

////////////////////////////////////////////////////////////////////////
//
// This returns the xfPath of the manip in the 
// selectionPath/manip/xfPath stuff specified by which index.
//
// Use: public
SoPath *
SvManipList::getXfPath(int which) const
//
////////////////////////////////////////////////////////////////////////
{
    SvPathManipStuff *stuff = (SvPathManipStuff *) (*list)[which];
    return (stuff->xfPath);
}
