// src\Inventor\Win\devices\SoWinMouseCommon.cpp.  Generated from SoGuiMouse.cpp.in by configure.

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Win/devices/SoWinMouse.h>
#include <Inventor/Win/devices/SoGuiMouseP.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

/*!
  \class SoWinMouse SoWinMouse.h Inventor/Win/devices/SoWinMouse.h
  \brief The SoWinMouse class is the mouse input device abstraction.

  \ingroup devices

  The SoWinMouse class is the glue between native mouse handling and
  mouse interaction in the Inventor scenegraph.

  All components derived from the SoWinRenderArea have got an
  SoWinMouse device attached by default.

  One important note for application programmers: our mappings to
  SoMouseButtonEvent::BUTTON2 and SoMouseButtonEvent::BUTTON3 do not
  match the mappings in SGI's InventorXt library or TGS's SoWin
  library for 3-button mice. They map mouse buttons like this:

  <ul>
  <li>left button: SoMouseButtonEvent::BUTTON1</li>
  <li>middle button: SoMouseButtonEvent::BUTTON2</li>
  <li>right button: SoMouseButtonEvent::BUTTON3</li>
  </ul>

  While in this SIM SoWin library the mappings are:

  <ul>
  <li>left button: SoMouseButtonEvent::BUTTON1</li>
  <li>middle button: SoMouseButtonEvent::BUTTON3</li>
  <li>right button: SoMouseButtonEvent::BUTTON2</li>
  </ul>

  This is a conscious design decision we've made.  The reason is that
  BUTTON2 should be the right mouse button whether you have a 2-button
  mouse or a 3-button mouse.
*/

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinMouse);

// *************************************************************************

/*!
  \enum SoWinMouse::Events
  Enumeration over supported mouse events.
*/
/*!
  \var SoWinMouse::Events SoWinMouse::BUTTON_PRESS
  Maskbit for mousebutton press events.
*/
/*!
  \var SoWinMouse::Events SoWinMouse::BUTTON_RELEASE
  Maskbit for mousebutton release events.
*/
/*!
  \var SoWinMouse::Events SoWinMouse::POINTER_MOTION
  Maskbit for mousepointer motion events.
*/
/*!
  \var SoWinMouse::Events SoWinMouse::BUTTON_MOTION
  Maskbit for mousepointer motion events with one or more mousebuttons
  pressed.
*/
/*!
  \var SoWinMouse::Events SoWinMouse::ALL_EVENTS

  Mask which includes all the maskbits in the enum (ie use this to
  signal interest in all kinds of events for the mouse device).
*/

// *************************************************************************

/*!
  \fn SoWinMouse::SoWinMouse(int mask)

  Constructor. The \a mask argument should contain the set of
  SoWinMouse::Events one is interested in tracking.
*/

/*!
  \fn SoWinMouse::~SoWinMouse()
  Destructor.
*/

/*!
  \fn const SoEvent * SoWinMouse::translateEvent(MSG * event)

  Translates a native event from the underlying toolkit into a generic
  event.

  This is then returned in the form of an instance of a subclass of
  the Inventor API's SoEvent class, either an SoMouseButtonEvent or an
  SoLocation2Event, depending on whether the native event is a
  mousebutton press / release, or a mousecursor movement event.

  The mapping of the mousebuttons upon generation of
  SoMouseButtonEvent events will be done as follows:

  <ul>
  <li>left mousebutton: SoMouseButtonEvent::BUTTON1</li>
  <li>right mousebutton: SoMouseButtonEvent::BUTTON2</li>
  <li>middle mousebutton, if available: SoMouseButtonEvent::BUTTON3</li>
  <li>forward motion on a wheel mouse: SoMouseButtonEvent::BUTTON4</li>
  <li>backward motion on a wheel mouse: SoMouseButtonEvent::BUTTON5</li>
  </ul>

  Note that the rightmost mousebutton will always map to
  SoMouseButtonEvent::BUTTON2, even on a 3-button mouse.
*/

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

SoGuiMouseP::SoGuiMouseP(SoWinMouse * p)
{
  this->pub = p;

  // Allocate system-neutral event objects once and reuse.
  this->buttonevent = new SoMouseButtonEvent;
  this->locationevent = new SoLocation2Event;
}

SoGuiMouseP::~SoGuiMouseP()
{
  delete this->buttonevent;
  delete this->locationevent;
}

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************
