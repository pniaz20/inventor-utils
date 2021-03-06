// src\Inventor\Win\viewers\SoWinPlaneViewer.cpp.  Generated from SoGuiPlaneViewer.cpp.in by configure.

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

// This file contains the generic, "templatize-able" parts of the
// So*PlaneViewer sourcecode.

/*!
  \class SoWinPlaneViewer Inventor/Win/viewers/SoWinPlaneViewer.h
  \brief The SoWinPlaneViewer class is for examining 3D models by moving the camera in orthogonal planes.

  \ingroup components viewers

  The SoWinPlaneViewer is a viewer that is useful for "CAD-style"
  applications, where you want the end-user to examine your model with
  the viewpoint set from one of the three principal axes.

  <center>
  <img src="planeviewer.png">
  </center>


  Controls:
  <ul>

  <li>hold down left mousebutton and move mouse pointer to dolly (or
  hold both left and middle mousebuttons)</li>

  <li>hold middle mousebutton to pan (or a CTRL-key plus left
  mousebutton, or a SHIFT-key plus left mousebutton)</li>

  <li>hold down CTRL + middle mousebutton to rotate (or CTRL + SHIFT +
  the left mousebutton)</li>

  <li>click 's', then pick with the left mousebutton to seek</li>

  <li>right mousebutton open the popup menu</li>

  <li>click 'ESC' key to switch to and from 'view' mode and
  'scenegraph interaction' mode (see setViewing() documentation)</li>

  <!-- 
    FIXME: This functionality has been disabled. See FIXME comment
    20050202 larsa below.

  <li>hold down the 'ALT' key to temporary toggle from  
      camera-interaction mode to scenegraph-interaction mode</li>  

  //-->

  </ul>

  Hitting any of the X, Y or Z buttons in the panel on the right side
  of the render canvas will "flip" the current camera direction around
  it's focal point to point along the selected axis (towards negative
  infinity).

  The SoWinPlaneViewer also provides a user decoration's button for
  toggling between orthographic or perspective camera view volumes and
  projection methods. This is the bottom-most click button on the
  right decoration border.

  It also inherits the decoration buttons from the SoWinFullViewer:
  the arrow for switching to "scenegraph interaction" mode, the hand
  for setting back to "camera interaction" mode, the house for "reset
  camera to home position", the blueprint house for "set new camera
  home position", the eye for "zoom camera out to view full scene" and
  the flashlight for setting "click to seek" mode.

  Note that a common faulty assumption about all the viewer-classes is
  that user interaction (in the "examine"-mode, not the
  scenegraph-interaction mode) influences the model or 3D-scene in the
  view. This is not correct, as it is always the viewer's \e camera
  that is translated and rotated.

  The initial position of the camera is placed such that all of the
  scenegraph's geometry fits within it's view.
*/

// *************************************************************************

#include <Inventor/Win/viewers/SoWinPlaneViewer.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <assert.h>
#include <math.h>

#include <Inventor/Win/common/gl.h>
#include <Inventor/Win/SoWinCursor.h>

#include <Inventor/SbLinear.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <sowindefs.h>

#include <Inventor/Win/viewers/SoGuiFullViewerP.h> // for pan() and zoom()
#include <Inventor/Win/viewers/SoGuiViewerP.h> // for adjusting final camera orientation before seek
#include <Inventor/Win/viewers/SoWinPlaneViewerP.h>

// *************************************************************************

// To access SoGuiPlaneViewerP "private implementation" class.

#define PRIVATE(ptr) (ptr->pimpl)

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinPlaneViewer);

// ************************************************************************

/*!
  \fn SoWinPlaneViewer::SoWinPlaneViewer(HWND parent, const char * const name, SbBool embed, SoWinFullViewer::BuildFlag flag, SoWinViewer::Type type)

  The public constructor, to be used by application programmers who
  want to instantiate the plain, standard SoWinPlaneViewer.
*/
SoWinPlaneViewer::SoWinPlaneViewer(HWND parent,
                                       const char * const name,
                                       SbBool embed,
                                       SoWinFullViewer::BuildFlag flag,
                                       SoWinViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinPlaneViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

/*!
  \fn SoWinPlaneViewer::SoWinPlaneViewer(HWND parent, const char * const name, SbBool embed, SoWinFullViewer::BuildFlag flag, SoWinViewer::Type type, SbBool build)

  A protected constructor, to be used by application programmers who
  want to extend the SoWinPlaneViewer.
*/
SoWinPlaneViewer::SoWinPlaneViewer(HWND parent,
                                       const char * const name,
                                       SbBool embed,
                                       SoWinFullViewer::BuildFlag flag,
                                       SoWinViewer::Type type,
                                       SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoWinPlaneViewerP(this);
  PRIVATE(this)->constructor(build);
}

/*!
  \fn SoWinPlaneViewer::~SoWinPlaneViewer()

  The destructor. Cleans up all internal resources used by the
  SoWinPlaneViewer instance.
*/
SoWinPlaneViewer::~SoWinPlaneViewer()
{
  delete PRIVATE(this);
}

// ************************************************************************

// Documented in superclass.
SbBool
SoWinPlaneViewer::processSoEvent(const SoEvent * const ev)
{
#if SOWIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoWinPlaneViewer::processSoEvent",
                          "[invoked], event '%s' "
                         "(isViewing()==%d, isSeekMode()==%d, mode==%d)",
                         ev->getTypeId().getName().getString(),
                         this->isViewing(), this->isSeekMode(),
                         PRIVATE(this)->mode);
#endif // debug

  // We're in "interact" mode (ie *not* the camera modification mode),
  // so don't handle the event here. It should either be forwarded to
  // the scenegraph, or caught by SoWinViewer::processSoEvent() if
  // it's an ESC and ALT press (to switch modes).
  if (!this->isViewing()) { return inherited::processSoEvent(ev); }
    
  // Events when in "ready-to-seek" mode are ignored, except those
  // which influence the seek mode itself -- these are handled further
  // up the inheritance hierarchy.
  if (this->isSeekMode()) { return inherited::processSoEvent(ev); }


  SbBool processed = FALSE;
  const SoGuiPlaneViewerP::PlaneViewerMode currentmode = PRIVATE(this)->mode;
  SoGuiPlaneViewerP::PlaneViewerMode newmode = currentmode;

  const SoType type(ev->getTypeId());

  const SbVec2s size(this->getGLSize());
  const SbVec2s pos(ev->getPosition());
  const SbVec2f posn((float)pos[0] / (float) SoWinMax(size[0], (short int)1),
                     (float)pos[1] / (float) SoWinMax(size[1], (short int)1));

  PRIVATE(this)->ctrldown = ev->wasCtrlDown();
  PRIVATE(this)->shiftdown = ev->wasShiftDown();

  if (type.isDerivedFrom(SoMouseButtonEvent::getClassTypeId())) {
    processed = TRUE;
    const SoMouseButtonEvent * event = (const SoMouseButtonEvent *) ev;
    const SbBool press = (event->getState() == SoButtonEvent::DOWN) ? TRUE : FALSE;

    if (press) {
      // Called twice to initialize both "now" (current) and "then"
      // (previous) pointer location.
      PRIVATE(this)->setPointerLocation(pos);
      PRIVATE(this)->setPointerLocation(pos);
    }

    switch (event->getButton()) {
      case SoMouseButtonEvent::BUTTON1:
        PRIVATE(this)->button1down = press;

        if (press && (currentmode == SoGuiPlaneViewerP::SEEK_WAIT_MODE)) {
          newmode = SoGuiPlaneViewerP::SEEK_MODE;
          this->seekToPoint(pos); // implicitly calls interactiveCountInc()
        }
        break;

      case SoMouseButtonEvent::BUTTON2:
        processed = FALSE; // pass on to superclass, so popup menu is shown
        break;

      case SoMouseButtonEvent::BUTTON3:
        PRIVATE(this)->button3down = press;
        break;

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTON5
      case SoMouseButtonEvent::BUTTON4:
        if (press) SoGuiFullViewerP::zoom(this->getCamera(), 0.1f);
        break;

      case SoMouseButtonEvent::BUTTON5:
        if (press) SoGuiFullViewerP::zoom(this->getCamera(), -0.1f);
        break;
#endif // HAVE_SOMOUSEBUTTONEVENT_BUTTON5

      default:
        break;
    } // switch (event->getButton())
  } // SoMouseButtonEvent::getClassTypeId()

  if (type.isDerivedFrom(SoKeyboardEvent::getClassTypeId())) {
    const SoKeyboardEvent * event = (const SoKeyboardEvent *) ev;
    const SbBool press = (event->getState() == SoButtonEvent::DOWN) ? TRUE : FALSE;

#if SOWIN_DEBUG && 0 // debug
    SoDebugError::postInfo("SoWinPlaneViewer::processSoEvent",
                           "keyboard %s: \"%c\"",
                           press ? "press" : "release",
                           event->getPrintableCharacter());
#endif // debug

    switch (event->getKey()) {
    case SoKeyboardEvent::LEFT_CONTROL:
    case SoKeyboardEvent::RIGHT_CONTROL:
      processed = TRUE;
      PRIVATE(this)->ctrldown = press;
      break;
    case SoKeyboardEvent::LEFT_SHIFT:
    case SoKeyboardEvent::RIGHT_SHIFT:
      processed = TRUE;
      PRIVATE(this)->shiftdown = press;
      break;

    default:
      break;
    }

  } // SoKeyboardEvent::getClassTypeId()


  if (type.isDerivedFrom(SoLocation2Event::getClassTypeId())) {
    processed = TRUE;
    const SoLocation2Event * event = (const SoLocation2Event *) ev;
    PRIVATE(this)->setPointerLocation(pos);
    const SbVec2f prevn((float) PRIVATE(this)->pointer.then[0] / (float) SoWinMax(size[0], (short int)1),
                        (float) PRIVATE(this)->pointer.then[1] / (float) SoWinMax(size[1], (short int)1));

    do {
      if (currentmode == SoGuiPlaneViewerP::ROTZ_MODE) {
        PRIVATE(this)->rotateZ(PRIVATE(this)->getPointerOrigoMotionAngle());
        break;
      }

      if (currentmode == SoGuiPlaneViewerP::TRANSLATE_MODE) {
        if (posn != prevn) {
          SoGuiFullViewerP::pan(this->getCamera(), this->getGLAspectRatio(),
                                PRIVATE(this)->panningplane, posn, prevn);
        }
        break;
      }

      if (currentmode == SoGuiPlaneViewerP::DOLLY_MODE) {
        if (posn[1] != prevn[1]) {
          float value = this->getRightWheelValue() + (prevn[1] - posn[1]) * 10.0f;
          this->rightWheelMotion(value);
          this->setRightWheelValue(value);
        }
        break;
      }

    } while (FALSE);
  } // SoLocation2Event::getClassTypeId()

  enum {
    BUTTON1DOWN = 1 << 0,
    BUTTON3DOWN = 1 << 1,
    CTRLDOWN =    1 << 2,
    SHIFTDOWN =   1 << 3
  };
  unsigned int combo =
    (PRIVATE(this)->button1down ? BUTTON1DOWN : 0) |
    (PRIVATE(this)->button3down ? BUTTON3DOWN : 0) |
    (PRIVATE(this)->ctrldown ? CTRLDOWN : 0) |
    (PRIVATE(this)->shiftdown ? SHIFTDOWN : 0);

#if SOWIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoWinPlaneViewer::processSoEvent",
                         "button1==%d, button3==%d, "
                         "ctrl==%d, shift==%d",
                         PRIVATE(this)->button1down, PRIVATE(this)->button3down,
                         PRIVATE(this)->ctrldown,
                         PRIVATE(this)->shiftdown);
#endif // debug
  

  switch (combo) {
  case BUTTON1DOWN:
  case BUTTON1DOWN|BUTTON3DOWN:
    newmode = SoGuiPlaneViewerP::DOLLY_MODE;
    break;
  case BUTTON3DOWN:
  case CTRLDOWN|BUTTON1DOWN:
  case SHIFTDOWN|BUTTON1DOWN:
    newmode = SoGuiPlaneViewerP::TRANSLATE_MODE;
    break;
  case CTRLDOWN|BUTTON3DOWN:
  case CTRLDOWN|SHIFTDOWN|BUTTON1DOWN:
    newmode = SoGuiPlaneViewerP::ROTZ_MODE;
    break;
  case CTRLDOWN:
  case CTRLDOWN|SHIFTDOWN:
    newmode = SoGuiPlaneViewerP::ROTZ_WAIT_MODE;
    break;
  default:
    if ((currentmode != SoGuiPlaneViewerP::SEEK_WAIT_MODE) &&
        (currentmode != SoGuiPlaneViewerP::SEEK_MODE)) {
      newmode = SoGuiPlaneViewerP::IDLE_MODE;
    }
    break;
  }

  if (newmode != currentmode) {
    if (newmode == SoGuiPlaneViewerP::ROTZ_MODE) {
      PRIVATE(this)->setCanvasSize(size);
      PRIVATE(this)->setPointerLocation(pos);
      PRIVATE(this)->setPointerLocation(pos);
    }

    PRIVATE(this)->changeMode(newmode);
  }

  // If not handled in this class, pass on upwards in the inheritance
  // hierarchy.
  return processed || inherited::processSoEvent(ev);
}

// ************************************************************************

// Documented in superclass.
void
SoWinPlaneViewer::actualRedraw(void)
{
  if (PRIVATE(this)->mode == SoGuiPlaneViewerP::ROTZ_MODE) {
    PRIVATE(this)->updateAnchorScenegraph();
  }

  inherited::actualRedraw();
}

// ************************************************************************

// documented in superclass
void
SoWinPlaneViewer::setSeekMode(SbBool on)
{
#if SOWIN_DEBUG
  if (!!on == !!this->isSeekMode()) {
    SoDebugError::postWarning("SoWinPlaneViewer::setSeekMode",
                              "seek mode already %sset", on ? "" : "un");
    return;
  }
#endif // SOWIN_DEBUG

  inherited::setSeekMode(on);

  PRIVATE(this)->changeMode(on ?
                            SoGuiPlaneViewerP::SEEK_WAIT_MODE :
                            (this->isViewing() ?
                             SoGuiPlaneViewerP::IDLE_MODE :
                             SoGuiPlaneViewerP::SCENEGRAPH_INTERACT_MODE));
}

// ************************************************************************

// Documented in superclass.
void
SoWinPlaneViewer::setCursorEnabled(SbBool enable)
{
  inherited::setCursorEnabled(enable);
  PRIVATE(this)->setCursorRepresentation(PRIVATE(this)->mode);
}

// ************************************************************************

// Documented in superclass.
void
SoWinPlaneViewer::setViewing(SbBool enable)
{
  if (!!enable == !!this->isViewing()) {
#if SOWIN_DEBUG
    SoDebugError::postWarning("SoQtPlaneViewer::setViewing",
                              "unnecessary invocation");
#endif // SOWIN_DEBUG
    return;
  }

  inherited::setViewing(enable);

  PRIVATE(this)->changeMode(this->isViewing() ? 
                            SoGuiPlaneViewerP::IDLE_MODE :
                            SoGuiPlaneViewerP::SCENEGRAPH_INTERACT_MODE);
}

// ************************************************************************

// Documented in superclass.
const char *
SoWinPlaneViewer::getDefaultWidgetName(void) const
{
  return "SoWinPlaneViewer";
}

// Documented in superclass.
const char *
SoWinPlaneViewer::getDefaultTitle(void) const
{
  return "Plane Viewer";
}

// Documented in superclass.
const char *
SoWinPlaneViewer::getDefaultIconTitle(void) const
{
  return "Plane Viewer";
}

// ************************************************************************

// Documented in superclass.
void
SoWinPlaneViewer::bottomWheelStart(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::TRANSLATE_MODE);
}

// Documented in superclass.
void
SoWinPlaneViewer::bottomWheelMotion(float value)
{
  // This method set up the bottom wheel to control camera translation
  // in the horizontal direction.

  if (value != this->getBottomWheelValue()) {
    SoGuiFullViewerP::pan(this->getCamera(), this->getGLAspectRatio(),
                          PRIVATE(this)->panningplane,
                          SbVec2f(value, 0),
                          SbVec2f(this->getBottomWheelValue(), 0));
  }
  inherited::bottomWheelMotion(value);
}

// Documented in superclass.
void
SoWinPlaneViewer::bottomWheelFinish(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::IDLE_MODE);
}


// Documented in superclass.
void
SoWinPlaneViewer::leftWheelStart(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::TRANSLATE_MODE);
}

// Documented in superclass.
void
SoWinPlaneViewer::leftWheelMotion(float value)
{
  // This method set up the left wheel to control camera translation
  // in the vertical direction.

  if (value != this->getLeftWheelValue()) {
    SoGuiFullViewerP::pan(this->getCamera(), this->getGLAspectRatio(),
                          PRIVATE(this)->panningplane,
                          SbVec2f(0, this->getLeftWheelValue()),
                          SbVec2f(0, value));
  }

  inherited::leftWheelMotion(value);
}

// Documented in superclass.
void
SoWinPlaneViewer::leftWheelFinish(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::IDLE_MODE);
}

// Documented in superclass.
void
SoWinPlaneViewer::rightWheelStart(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::DOLLY_MODE);
}

// Documented in superclass.
void
SoWinPlaneViewer::rightWheelMotion(float value)
{
  // This method set up the right wheel to control camera movement in
  // the inwards direction.

  SoGuiFullViewerP::zoom(this->getCamera(), this->getRightWheelValue() - value);
  inherited::rightWheelMotion(value);
}

// Documented in superclass.
void
SoWinPlaneViewer::rightWheelFinish(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::IDLE_MODE);
}

// ************************************************************************

// Documented in superclass.
void
SoWinPlaneViewer::afterRealizeHook(void)
{
  PRIVATE(this)->setCursorRepresentation(PRIVATE(this)->mode);
  inherited::afterRealizeHook();
}

// ************************************************************************

#ifndef DOXYGEN_SKIP_THIS

// This method locates a named node in the superimposed scene.
static SoNode *
get_scenegraph_node(SoSearchAction * search, SoNode * root, const char * name)
{
  search->reset();
  search->setName(SbName(name));
  search->setInterest(SoSearchAction::FIRST);
  search->setSearchingAll(TRUE);
  search->apply(root);
  assert(search->getPath());
  return search->getPath()->getTail();
}

// *************************************************************************

// Remaining code is for the SoGuiPlaneViewerP "private
// implementation" class.

#define PUBLIC(ptr) (ptr->pub)

SoGuiPlaneViewerP::SoGuiPlaneViewerP(SoWinPlaneViewer * publ)
{
  PUBLIC(this) = publ;
}

SoGuiPlaneViewerP::~SoGuiPlaneViewerP()
{
  if (this->superimposition != NULL) {
    PUBLIC(this)->removeSuperimposition(this->superimposition);
    this->superimposition->unref();
  }
}

void
SoGuiPlaneViewerP::commonConstructor(void)
{
  this->mode = SoGuiPlaneViewerP::IDLE_MODE;

  this->canvas = SbVec2s(0, 0);
  this->pointer.now = SbVec2s(0, 0);
  this->pointer.then = SbVec2s(0, 0);
  this->ctrldown = FALSE;
  this->shiftdown = FALSE;
  this->button1down = FALSE;
  this->button3down = FALSE;


  static const char * superimposed = {
    "#Inventor V2.1 ascii\n\n"
    ""
    "Separator {"
    "  DEF sowin->orthocam OrthographicCamera {"
    "    height 1"
    "    nearDistance 0"
    "    farDistance 1"
    "  }"
    "  LightModel {"
    "    model BASE_COLOR"
    "  }"
    ""
    "  Separator {"
    "    DEF sowin->geometry Coordinate3 {"
    "      point ["  // coordinates set from code
    "       0 0 0,"
    "       0 0 0," 
    "       0 0 0,"
    "       0 0 0"
    "      ]"
    "    }"
    "    BaseColor { rgb 1 1 1 }"
    "    DEF sowin->style0 DrawStyle { }" // lineWidth set in code
    "    DEF sowin->mainline IndexedLineSet {" // fat line (exterior)
    "      coordIndex ["
    "        0, 1, -1, 1, 2, -1, 1, 3, -1"
    "      ]"
    "    }"
    "    BaseColor { rgb 0.5 0.5 0.5 }"
    "    DEF sowin->style1 DrawStyle { }" // lineWidth set in code
    "    USE sowin->mainline" // thin line (interior)
    "  }"
    "}"
  };

  SoInput * input = new SoInput;
  input->setBuffer((void *)superimposed, strlen(superimposed));
  SbBool ok = SoDB::read(input, this->superimposition);
  assert(ok && "error in superimposed scenegraph");
  delete input;
  this->superimposition->ref();

  SoSearchAction s;
  this->super.coords = (SoCoordinate3 *)
    get_scenegraph_node(&s, this->superimposition, "sowin->geometry");
  this->super.camera = (SoOrthographicCamera *)
    get_scenegraph_node(&s, this->superimposition, "sowin->orthocam");

  // drawstyle settings for the superimposed lines will be updated on
  // demand, according to the capabilities of the GL driver & context.
  this->lineds[0] = (SoDrawStyle *)
    get_scenegraph_node(&s, this->superimposition, "sowin->style0");
  this->lineds[1] = (SoDrawStyle *)
    get_scenegraph_node(&s, this->superimposition, "sowin->style1");

  PUBLIC(this)->addSuperimposition(this->superimposition);
  PUBLIC(this)->setSuperimpositionEnabled(this->superimposition, FALSE);
}

void
SoGuiPlaneViewerP::rotateZ(const float angle) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  camera->orientation =
    camera->orientation.getValue() * SbRotation(dir, angle);
}

void
SoGuiPlaneViewerP::viewPlaneX(void) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * dir;
  camera->position = focalpoint +
    camera->focalDistance.getValue() * SbVec3f(1, 0, 0);
  camera->orientation = SbRotation(SbVec3f(0, 1, 0), float(M_PI) / 2.0f);
}

void
SoGuiPlaneViewerP::viewPlaneY(void) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * dir;
  camera->position = focalpoint +
    camera->focalDistance.getValue() * SbVec3f(0, 1, 0);
  camera->orientation = SbRotation(SbVec3f(1, 0, 0), -float(M_PI) / 2.0f);
}

void
SoGuiPlaneViewerP::viewPlaneZ(void) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * dir;
  camera->position = focalpoint +
    camera->focalDistance.getValue() * SbVec3f(0, 0, 1);
  camera->orientation = SbRotation(SbVec3f(0, 1, 0), 0);
}

void
SoGuiPlaneViewerP::setCanvasSize(const SbVec2s size)
{
  this->canvas = size;
}

void
SoGuiPlaneViewerP::setPointerLocation(const SbVec2s position)
{
  this->pointer.then = this->pointer.now;
  this->pointer.now = position;
}

int
SoGuiPlaneViewerP::getPointerXMotion(void) const
{
  return this->pointer.now[0] - this->pointer.then[0];
}

int
SoGuiPlaneViewerP::getPointerYMotion(void) const
{
  return this->pointer.now[1] - this->pointer.then[1];
}

float
SoGuiPlaneViewerP::getPointerOrigoAngle(void) const
{
  SbVec2s now = this->pointer.now;
  now[0] -= this->canvas[0] / 2;
  now[1] -= this->canvas[1] / 2;

  double nowradval = (now[0] != 0) ? atan(fabs((double) (now[1] / now[0]))) : 0.0;

  if (now[0] < 0) nowradval = M_PI - nowradval;
  if (now[1] < 0) nowradval = 2 * M_PI - nowradval;

  return (float)nowradval;
}

float
SoGuiPlaneViewerP::getPointerOrigoMotionAngle(void) const
{
  if (this->pointer.then == this->pointer.now)
    return 0.0f;

  SbVec2s now = this->pointer.now;
  now[0] -= this->canvas[0] / 2;
  now[1] -= this->canvas[1] / 2;

  SbVec2s then = this->pointer.then;
  then[0] -= this->canvas[0] / 2;
  then[1] -= this->canvas[1] / 2;

  double nowradval = (now[0] != 0) ? atan(fabs((double) (now[1] / now[0]))) : 0.0;
  if (now[0] < 0) nowradval = M_PI - nowradval;
  if (now[1] < 0) nowradval = 2 * M_PI - nowradval;

  double thenradval = (then[0] != 0) ? atan(fabs((double) (then[1] / then[0]))) : 0.0;
  if (then[0] < 0) thenradval = M_PI - thenradval;
  if (then[1] < 0) thenradval = 2 * M_PI - thenradval;

  return (float)(nowradval - thenradval);
}

// This method updates the contents of the scenegraph which renders
// the rotate-"anchor".
void
SoGuiPlaneViewerP::updateAnchorScenegraph(void) const
{
  // must re-check this, since the GL context may be different between
  // invocations:
  SbVec2f range;
  float granularity;
  PUBLIC(this)->getLineWidthLimits(range, granularity);
  // Draw a thinner line on top of a fat line, to make an outline.
  const float lw0 = SoWinClamp(5.0f, range[0], range[1]);
  const float lw1 = SoWinClamp(3.0f, range[0], range[1]);
  if (this->lineds[0]->lineWidth.getValue() != lw0) { this->lineds[0]->lineWidth = lw0; }
  if (this->lineds[1]->lineWidth.getValue() != lw1) { this->lineds[1]->lineWidth = lw1; }


  float x = float(this->pointer.now[0]) / float(this->canvas[0]);
  float y = float(this->pointer.now[1]) / float(this->canvas[1]);

  float aspectratio = PUBLIC(this)->getViewportRegion().getViewportAspectRatio();
  SbViewVolume vv = this->super.camera->getViewVolume(aspectratio);
  // know we have ADJUST_CAMERA mapping
  if (aspectratio < 1.0f) vv.scale(1.0f / aspectratio);

  SbVec3f p = vv.getPlanePoint(1.0, SbVec2f(x, y));

  this->super.coords->point.set1Value(0, SbVec3f(0, 0, 0));
  this->super.coords->point.set1Value(1, SbVec3f(p[0], p[1], 0));

  float angle = this->getPointerOrigoAngle();
  SbRotation r(SbVec3f(0, 0, 1), angle);

  SbVec3f xarrow(-0.02f, -0.1f, 0.0f);
  r.multVec(xarrow, xarrow);
  SbVec3f pa = SbVec3f(p[0] + xarrow[0], p[1] + xarrow[1], 0);
  this->super.coords->point.set1Value(2, SbVec3f(pa[0], pa[1], 0));

  SbVec3f yarrow(-0.02f, 0.1f, 0.0f);
  r.multVec(yarrow, yarrow);
  pa = SbVec3f(p[0] + yarrow[0], p[1] + yarrow[1], 0);
  this->super.coords->point.set1Value(3, SbVec3f(pa[0], pa[1], 0));
}

// Set cursor graphics according to mode.
void
SoGuiPlaneViewerP::setCursorRepresentation(PlaneViewerMode modearg)
{
#if SOWIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoWinPlaneViewer::setCursorRepresentation",
                         "mode==%d", mode);
#endif // debug

  assert(PUBLIC(this)->getGLWidget());

  if (!PUBLIC(this)->isCursorEnabled()) {
    PUBLIC(this)->setComponentCursor(SoWinCursor::getBlankCursor());
    return;
  }

  switch (modearg) {
  case SoGuiPlaneViewerP::SCENEGRAPH_INTERACT_MODE:
    PUBLIC(this)->setComponentCursor(SoWinCursor(SoWinCursor::DEFAULT));
    break;

  case SoGuiPlaneViewerP::IDLE_MODE:
  case SoGuiPlaneViewerP::DOLLY_MODE:
    PUBLIC(this)->setComponentCursor(SoWinCursor(SoWinCursor::UPARROW));
    break;
  case SoGuiPlaneViewerP::ROTZ_WAIT_MODE:
  case SoGuiPlaneViewerP::ROTZ_MODE:
    PUBLIC(this)->setComponentCursor(SoWinCursor::getRotateCursor());
    break;
  case SoGuiPlaneViewerP::SEEK_WAIT_MODE:
  case SoGuiPlaneViewerP::SEEK_MODE:
    PUBLIC(this)->setComponentCursor(SoWinCursor(SoWinCursor::CROSSHAIR));
    break;
  case SoGuiPlaneViewerP::TRANSLATE_MODE:
    PUBLIC(this)->setComponentCursor(SoWinCursor::getPanCursor());
    break;
  default:
    assert(0 && "unknown PlaneViewer mode");
    break;
  }
}


/*!  
  Overridden to make sure camera orientation is not affected by a
  seek
 */
void
SoWinPlaneViewer::computeSeekFinalOrientation(void)
{
  SoWinViewerP * thisp = ((SoWinViewer *)this)->pimpl;
  thisp->cameraendorient = thisp->camera->orientation.getValue();
}


void
SoGuiPlaneViewerP::changeMode(PlaneViewerMode newmode)
{
  if (newmode == this->mode) { return; }

  switch (newmode) {
  case SoGuiPlaneViewerP::TRANSLATE_MODE:
  case SoGuiPlaneViewerP::DOLLY_MODE:
    PUBLIC(this)->interactiveCountInc();
    break;

  case SoGuiPlaneViewerP::ROTZ_MODE:
    PUBLIC(this)->interactiveCountInc();
    PUBLIC(this)->setSuperimpositionEnabled(this->superimposition, TRUE);
    PUBLIC(this)->scheduleRedraw();
    break;

  default:
    break;
  }

  switch (this->mode) {
  case SoGuiPlaneViewerP::ROTZ_MODE:
    PUBLIC(this)->setSuperimpositionEnabled(this->superimposition, FALSE);
    PUBLIC(this)->scheduleRedraw();
    // fall through

  case SoGuiPlaneViewerP::TRANSLATE_MODE:
  case SoGuiPlaneViewerP::DOLLY_MODE:
    PUBLIC(this)->interactiveCountDec();
    break;
  default:
    break;
  }

  if (newmode == SoGuiPlaneViewerP::TRANSLATE_MODE) {
    // The plane we're projecting the mouse coordinates to get 3D
    // coordinates should stay the same during the whole pan
    // operation, so we should calculate this value here.
    SoCamera * cam = PUBLIC(this)->getCamera();
    if (cam == NULL) { // can happen for empty scenegraph
      this->panningplane = SbPlane(SbVec3f(0, 0, 1), 0);
    }
    else {
      SbViewVolume vv = cam->getViewVolume(PUBLIC(this)->getGLAspectRatio());
      this->panningplane = vv.getPlane(cam->focalDistance.getValue());
    }
  }

  this->setCursorRepresentation(newmode);
  this->mode = newmode;
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

#undef PRIVATE
#undef PUBLIC

