//  -*- C++ -*-

/*
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.2 $
 |
 |   Description:
 |	This class describes the field of play.  
 |
 |   Classes:
 |      TsField
 |
 |   Author: Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _TS_FIELD_
#define _TS_FIELD_

#include "stdafx.h"

class SoMfcViewer;
class SoEventCallback;
class SoTranslation;
class SoSeparator;
class SoMaterial;
class SoGroup;
class SoSensor;
class SoText2;
class SoAlarmSensor;
class SoTimerSensor;
class TsPiece;
class TsScoreboard;
class CDropDoc;

enum TxAxes {
    TS_X_AXIS,    
    TS_Y_AXIS,    
    TS_Z_AXIS
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: TsField
//
//  The class for the field of play.  Methods move pieces in the
//  field, check for collisions, and keep score.
//
//////////////////////////////////////////////////////////////////////////////

class TsField {	  
public:
    TsField(SoMfcViewer *, CDropDoc *);
   ~TsField();

    int getScore() { return totalScore; }

    // Initialize the whole game.
    void            initGame();

    // Start a new game.
    void            startNewGame();
	void			StartGame();  // jlr: a hack!
    // Add a piece and start it falling.
    void            addPiece();

    // Returns the viewer for the field
    SoMfcViewer    *getViewer() const;

    // These routines move the piece in various ways.
    void            rotation( int axis, int amount );
    void            translation( int axis, int amount );
    void            dropPiece();

    // Add points to the score.
    void            addPoints( int points );

    // Used by event callbacks
    void	    handleReturnKey();
    void	    handleHelpKey();

	BOOL        isStarted() { return gameStarted; }
	BOOL        isPaused() { return gamePaused; }
    void			pauseGame();
    void			resumeGame();


private:
    SoSeparator     *block, *floor, *grid, *helpRoot, *overRoot;
    SoSeparator     *fieldRoot, *fallingRoot, *piecesRoot;
    SoSeparator     *fallingPiece;
    SoTranslation   *pieceXZTranslation, *pieceYTranslation;
    SoTranslation   *gridTranslation;
    SoGroup         *otherBlocks, *helpGroup;
    SoText2         *overScore;
    SbBool          gameStarted;
    SbBool          isGameOver, isDropping, helpDisplayed;
    SbBool			gamePaused, trickleOn, shiftOn, removalOn;
    SbPList         pieceList;
    SoNodeList      standardCube, levelMaterial, levelGroup;
    SoNodeList      pieceChild, staticBlock, removalTranslation;
    TsPiece         *currentPiece;
    SoMfcViewer     *viewer;
    SoMaterial      *saveMaterials[4], *removalMaterial;
    SoTimerSensor   *trickleSensor, *shiftSensor;
    SoAlarmSensor   *removalSensor;
    SbTime          wallClock, fallingClock;
    float           currentFraction, currentRate, skillRates[7], saveRate;
    int             numPieceBlocks, pointsEarned, totalScore, pointsNeeded;
    int             piecePositions[4], numPieceTypes;
    int             standardPosition[3];
    int             *fieldTable;
    int             currentHeight, currentOrientation;
    int             resolution, totalHeight;
    int             numRemovals, removalList[3], skillLevel;
	CDropDoc        *dropDoc;

    SbBool 	    isNextPieceEnabled, isBlockBuilt;

    // Geometry creation routines
    void        createFloorAndGrid();
    void 	    buildBlock();
    void	    buildHelpMessage(SoSeparator *root);
	void		setStatusText(const char *text);

    // Gets the basic block shape
    SoSeparator     *getBlock() {return block;}

    void            stopPiece();
    void            endShift();
   
    void            getFieldPositions( int numBlocks, int *localPos,
                                       int *fieldPos, int *standard );
    SbBool          validPosition( int numBlocks, int *newPositions,
                                   int *standard );
    SbBool          collision( int numBlocks, int *newPositions );
    void            rotatePiece( int newOrientation );

    // Sensor callback routines for animating the currently falling piece,
    // removing completed rows, and shifting the remaining rows down
    static void     tricklePiece( void *data, SoSensor *sensor );
    static void     removeRows( void *data, SoSensor *sensor );
    static void     shiftRows( void *data, SoSensor *sensor );

    // Event callback routine for handling keyboard events
    static void     handleKeyboard(void *data, SoEventCallback *node);

    // Builds the widget.
    // virtual Widget  buildWidget(Widget parent, const char *name);
};

#endif /* _TS_FIELD_ */







