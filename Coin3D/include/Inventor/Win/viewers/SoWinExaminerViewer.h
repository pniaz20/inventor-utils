#ifndef SOWIN_EXAMINERVIEWER_H
#define SOWIN_EXAMINERVIEWER_H

// 

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

#include <Inventor/SbLinear.h>
#include <Inventor/Win/viewers/SoWinFullViewer.h>

class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class SoWinThumbWheel;

// *************************************************************************

class SOWIN_DLL_API SoWinExaminerViewer : public SoWinFullViewer {
  SOWIN_OBJECT_HEADER(SoWinExaminerViewer, SoWinFullViewer);

public:
  SoWinExaminerViewer(HWND parent = NULL,
                        const char * name = NULL,
                        SbBool embed = TRUE,
                        SoWinFullViewer::BuildFlag flag = BUILD_ALL,
                        SoWinViewer::Type type = BROWSER);
  ~SoWinExaminerViewer();

  void setAnimationEnabled(const SbBool enable);
  SbBool isAnimationEnabled(void) const;

  void stopAnimating(void);
  SbBool isAnimating(void) const;

  void setFeedbackVisibility(const SbBool enable);
  SbBool isFeedbackVisible(void) const;

  void setFeedbackSize(const int size);
  int getFeedbackSize(void) const;

  virtual void setViewing(SbBool enable);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);

protected:
  SoWinExaminerViewer(HWND parent,
                        const char * name,
                        SbBool embed,
                        SoWinFullViewer::BuildFlag flag,
                        SoWinViewer::Type type,
                        SbBool build);

  virtual void leftWheelMotion(float val);
  virtual void bottomWheelMotion(float val);
  virtual void rightWheelMotion(float val);

  virtual void createViewerButtons(HWND parent, SbPList * buttonlist);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual SbBool processSoEvent(const SoEvent * const event);
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void afterRealizeHook(void);

private:
  class SoWinExaminerViewerP * pimpl;

  friend class SoGuiExaminerViewerP;
  friend class SoWinExaminerViewerP;
};

#endif // ! SOWIN_EXAMINERVIEWER_H
