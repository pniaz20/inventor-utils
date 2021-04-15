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
 |   Classes	: TsEll, TsTee, TsZee, TsLTri, TsMTri, TsRTri
 |
 |   Author	: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */
#include "stdafx.h"
#if defined(__sgi)    // PGI_IV ---- yjz
  #include <bstring.h>
#else
#  if defined(__hpux)
#    include <string.h>
#  elif defined(_WIN32)
#    include <string.h>
#  else  // PGI_IV, For _AIX, __osf__ and __sun
#    include <strings.h>
#  endif
#  if defined (__sun) || defined(__hpux)
#    define bcopy(a,b,c) memcpy((b),(a),(c))
#    define bzero(a,c) memset((a),0,(c))
#  endif
#endif
#include "TsPieces.h"

static int ellTable[24][4] = {
	{  4, 13, 22, 23},
	{ 12, 13, 14,  5},
	{ 22, 13,  4,  3},
	{ 14, 13, 12, 21},
	{ 10, 13, 16, 17},
	{ 12, 13, 14, 11},
	{ 16, 13, 10,  9},
	{ 14, 13, 12, 15},
	{ 22, 13,  4,  5},
	{ 14, 13, 12,  3},
	{  4, 13, 22, 21},
	{ 12, 13, 14, 23},
	{ 16, 13, 10, 11},
	{ 14, 13, 12,  9},
	{ 10, 13, 16, 15},
	{ 12, 13, 14, 17},
	{  4, 13, 22, 19},
	{ 16, 13, 10,  1},
	{ 22, 13,  4,  7},
	{ 10, 13, 16, 25},
	{  4, 13, 22, 25},
	{ 10, 13, 16,  7},
	{ 22, 13,  4,  1},
	{ 16, 13, 10, 19}};

static int teeTable[24][4] = {
	{  4, 13, 22, 14},
	{ 12, 13, 14,  4},
	{ 22, 13,  4, 12},
	{ 14, 13, 12, 22},
	{ 10, 13, 16, 14},
	{ 12, 13, 14, 10},
	{ 16, 13, 10, 12},
	{ 14, 13, 12, 16},
	{ 22, 13,  4, 14},
	{ 14, 13, 12,  4},
	{  4, 13, 22, 12},
	{ 12, 13, 14, 22},
	{ 16, 13, 10, 14},
	{ 14, 13, 12, 10},
	{ 10, 13, 16, 12},
	{ 12, 13, 14, 16},
	{  4, 13, 22, 10},
	{ 16, 13, 10,  4},
	{ 22, 13,  4, 16},
	{ 10, 13, 16, 22},
	{  4, 13, 22, 16},
	{ 10, 13, 16,  4},
	{ 22, 13,  4, 10},
	{ 16, 13, 10, 22}};

static int zeeTable[24][4] = {
	{  4, 13, 14, 23},
	{ 12, 13,  4,  5},
	{ 23, 14, 13,  4},
	{  5,  4, 13, 12},
	{ 10, 13, 14, 17},
	{ 12, 13, 10, 11},
	{ 17, 14, 13, 10},
	{ 11, 10, 13, 12},
	{ 22, 13, 14,  5},
	{ 14, 13,  4,  3},
	{  5, 14, 13, 22},
	{  3,  4, 13, 14},
	{ 16, 13, 14, 11},
	{ 14, 13, 10,  9},
	{ 11, 14, 13, 16},
	{  9, 10, 13, 14},
	{  4, 13, 10, 19},
	{ 16, 13,  4,  1},
	{ 19, 10, 13,  4},
	{  1,  4, 13, 16},
	{  4, 13, 16, 25},
	{ 10, 13,  4,  7},
	{ 25, 16, 13,  4},
	{  7,  4, 13, 10}};


static int ltriTable[24][4] = {
	{  0,  9, 12,  1},
	{  9, 10, 13,  0},
	{ 10,  1,  4,  9},
	{  1,  0,  3, 10},
	{  9, 12,  3, 10},
	{ 12, 13,  4,  9},
	{ 13, 10,  1, 12},
	{ 10,  9,  0, 13},
	{ 12,  3,  0, 13},
	{ 13, 12,  9,  4},
	{  4, 13, 10,  3},
	{  3,  4,  1, 12},
	{  3,  0,  9,  4},
	{  4,  3, 12,  1},
	{  1,  4, 13,  0},
	{  0,  1, 10,  3},
	{  3, 12, 13,  0},
	{ 12,  9, 10,  3},
	{  9,  0,  1, 12},
	{  0,  3,  4,  9},
	{  1, 10,  9,  4},
	{ 10, 13, 12,  1},
	{ 13,  4,  3, 10},
	{  4,  0,  1, 13}};


static int mtriTable[24][4] = {
	{  0,  9, 12, 10},
	{  9, 10, 13,  1},
	{ 10,  1,  4,  0},
	{  1,  0,  3,  9},
	{  9, 12,  3, 13},
	{ 12, 13,  4, 10},
	{ 13, 10,  1,  9},
	{ 10,  9,  0, 12},
	{ 12,  3,  0,  4},
	{ 13, 12,  9,  3},
	{  4, 13, 10, 12},
	{  3,  4,  1, 13},
	{  3,  0,  9,  1},
	{  4,  3, 12,  0},
	{  1,  4, 13,  3},
	{  0,  1, 10,  4},
	{  3, 12, 13,  9},
	{ 12,  9, 10,  0},
	{  9,  0,  1,  3},
	{  0,  3,  4, 12},
	{  1, 10,  9, 13},
	{ 10, 13, 12,  4},
	{ 13,  4,  3,  1},
	{  4,  0,  1, 10}};


static int rtriTable[24][4] = {
	{  0,  9, 12, 13},
	{  9, 10, 13,  4},
	{ 10,  1,  4,  3},
	{  1,  0,  3, 12},
	{  9, 12,  3,  4},
	{ 12, 13,  4,  1},
	{ 13, 10,  1,  0},
	{ 10,  9,  0,  3},
	{ 12,  3,  0,  1},
	{ 13, 12,  9,  0},
	{  4, 13, 10,  9},
	{  3,  4,  1, 10},
	{  3,  0,  9, 10},
	{  4,  3, 12,  9},
	{  1,  4, 13, 12},
	{  0,  1, 10, 13},
	{  3, 12, 13, 10},
	{ 12,  9, 10,  1},
	{  9,  0,  1,  4},
	{  0,  3,  4, 13},
	{  1, 10,  9, 12},
	{ 10, 13, 12,  3},
	{ 13,  4,  3,  0},
	{  4,  0,  1,  9}};



////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsEll.
//
// Use: public

TsEll::TsEll()

//
////////////////////////////////////////////////////////////////////////
{
    numBlocks          = 4;

#if defined(__osf__)  // PGI_IV -- yjz
    bcopy ((const char *)ellTable,
           (char *)piecePositionTable,
           24*4*sizeof(int));
#else
    bcopy ((const void *)ellTable,
           (void *)piecePositionTable,
           24*4*sizeof(int));
#endif
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsEll.
//
// Use: public

TsEll::~TsEll()

//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsTee.
//
// Use: public

TsTee::TsTee()

//
////////////////////////////////////////////////////////////////////////
{
    numBlocks          = 4;

#if defined(__osf__)  // PGI_IV -- yjz
    bcopy ((const char *)teeTable,
           (char *)piecePositionTable,
           24*4*sizeof(int));
#else
    bcopy ((const void *)teeTable,
           (void *)piecePositionTable,
           24*4*sizeof(int));
#endif
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsTee.
//
// Use: public

TsTee::~TsTee()

//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsZee.
//
// Use: public

TsZee::TsZee()

//
////////////////////////////////////////////////////////////////////////
{
    numBlocks          = 4;

#if defined(__osf__)  // PGI_IV -- yjz
    bcopy ((const char *)zeeTable,
           (char *)piecePositionTable,
           24*4*sizeof(int));
#else
    bcopy ((const void *)zeeTable,
           (void *)piecePositionTable,
           24*4*sizeof(int));
#endif
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsZee.
//
// Use: public

TsZee::~TsZee()

//
////////////////////////////////////////////////////////////////////////
{
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsLTri.
//
// Use: public

TsLTri::TsLTri()

//
////////////////////////////////////////////////////////////////////////
{
    numBlocks          = 4;

#if defined(__osf__)  // PGI_IV -- yjz
    bcopy ((const char *)ltriTable,
           (char *)piecePositionTable,
           24*4*sizeof(int));
#else
    bcopy ((const void *)ltriTable,
           (void *)piecePositionTable,
           24*4*sizeof(int));
#endif
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsLTri.
//
// Use: public

TsLTri::~TsLTri()

//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsMTri.
//
// Use: public

TsMTri::TsMTri()

//
////////////////////////////////////////////////////////////////////////
{
    numBlocks          = 4;

#if defined(__osf__)  // PGI_IV -- yjz
    bcopy ((const char *)mtriTable,
           (char *)piecePositionTable,
           24*4*sizeof(int));
#else
    bcopy ((const void *)mtriTable,
           (void *)piecePositionTable,
           24*4*sizeof(int));
#endif
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsMTri.
//
// Use: public

TsMTri::~TsMTri()

//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//	Constructor for the TsRTri.
//
// Use: public

TsRTri::TsRTri()

//
////////////////////////////////////////////////////////////////////////
{
    numBlocks          = 4;
#if defined(__osf__)  // PGI_IV -- yjz
    bcopy ((const char *)rtriTable,
           (char *)piecePositionTable,
           24*4*sizeof(int));
#else
    bcopy ((const void *)rtriTable,
           (void *)piecePositionTable,
           24*4*sizeof(int));
#endif
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Destructor for TsRTri.
//
// Use: public

TsRTri::~TsRTri()

//
////////////////////////////////////////////////////////////////////////
{
}






