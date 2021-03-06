// src\Inventor\Win\devices\SoWinInputFocusCommon.cpp.  Generated from SoGuiInputFocus.cpp.in by configure.

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

/*!
  \class SoWinInputFocus SoWinInputFocus.h Inventor/Win/devices/SoWinInputFocus.h
  \brief The SoWinInputFocus class is an abstraction for widget focus events as an input device.

  \ingroup devices

  This device class is a "virtual device" which can be used to get
  events when the mouse pointer enters or leaves a specific widget.
*/

// *************************************************************************

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Win/devices/SoWinInputFocus.h>
#include <Inventor/Win/devices/SoGuiInputFocusP.h>

// *************************************************************************

SOWIN_OBJECT_SOURCE(SoWinInputFocus);

// *************************************************************************

/*!
  \enum SoWinInputFocus::Events

  Bit-wise enumeration over events handled by the SoWinInputFocus
  device class.  Used in the SoWinInputFocus constructor.
*/

/*!
  \var SoWinInputFocus::Events SoWinInputFocus::ENTER_WINDOW

  Maskbit for receiving events when focus comes to a widget.
*/

/*!
  \var SoWinInputFocus::Events SoWinInputFocus::LEAVE_WINDOW

  Maskbit for receiving events when focus leaves a widget.
*/

/*!
  \var SoWinInputFocus::Events SoWinInputFocus::ALL_EVENTS

  Combined bitmask for all possible events.
*/

/*!
  \fn SoWinInputFocus::SoWinInputFocus(int mask)

  Constructor. The \a mask specifies which focus-related events to
  handle. Others will just be ignored.
*/

// *************************************************************************

SoGuiInputFocusP::SoGuiInputFocusP(SoWinInputFocus * p)
{
  this->pub = p;
}

SoGuiInputFocusP::~SoGuiInputFocusP()
{
}

// *************************************************************************
