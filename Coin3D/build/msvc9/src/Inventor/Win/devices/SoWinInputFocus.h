#ifndef SOWIN_INPUTFOCUS_H
#define SOWIN_INPUTFOCUS_H

// src\Inventor\Win\devices\SoWinInputFocus.h.  Generated from SoGuiInputFocus.h.in by configure.

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

#include <Inventor/Win/devices/SoWinDevice.h>

// *************************************************************************

class SOWIN_DLL_API SoWinInputFocus : public SoWinDevice {
  SOWIN_OBJECT_HEADER(SoWinInputFocus, SoWinDevice);

public:
  enum Events {
    ENTER_WINDOW = 1 << 0,
    LEAVE_WINDOW = 1 << 1,
    ALL_EVENTS   = ENTER_WINDOW | LEAVE_WINDOW
  };

  SoWinInputFocus(int mask = ALL_EVENTS);
  virtual ~SoWinInputFocus();

  virtual void enable(HWND widget, SoWinEventHandler * handler, void * closure);
  virtual void disable(HWND widget, SoWinEventHandler * handler, void * closure);

  virtual const SoEvent * translateEvent(MSG * event);

private:
  class SoWinInputFocusP * pimpl;
  friend class SoGuiInputFocusP;
  friend class SoWinInputFocusP;
};

#define SO_WIN_ALL_FOCUS_EVENTS SoWinInputFocus::ALL_EVENTS;

// *************************************************************************

#endif // ! SOWIN_INPUTFOCUS_H
