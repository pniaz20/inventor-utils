#ifndef COIN_SOWINMATERIALEDITOR_H
#define COIN_SOWINMATERIALEDITOR_H

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

#include <Inventor/Win/nodes/SoGuiMaterialEditor.h>
#include <Inventor/Win/SoWinRenderArea.h>

class SoMaterial;
class SoVRMLMaterial;

// *************************************************************************

typedef void SoWinMaterialEditorCB(void * userdata, const SoMaterial * material);

class SOWIN_DLL_API SoWinMaterialEditor : public SoWinRenderArea {
  SOWIN_OBJECT_HEADER(SoWinMaterialEditor, SoWinRenderArea);

public:
  SoWinMaterialEditor(HWND parent = NULL, const char * name = NULL, SbBool embed = TRUE);
  ~SoWinMaterialEditor(void);

  enum UpdateFrequency {
    CONTINUOUS = SoGuiMaterialEditor::CONTINUOUS,
    AFTER_ACCEPT = SoGuiMaterialEditor::AFTER_ACCEPT
  };

  void attach(SoMaterial * material, int index = 0);
  void attach(SoVRMLMaterial * material);
  void detach(void);
  SbBool isAttached(void);

  void addMaterialChangedCallback(
    SoWinMaterialEditorCB * callback, void * closure = NULL);
  void removeMaterialChangedCallback(
    SoWinMaterialEditorCB * callback, void * closure = NULL);

  void setUpdateFrequency(SoWinMaterialEditor::UpdateFrequency frequency);
  SoWinMaterialEditor::UpdateFrequency getUpdateFrequency(void) const;

  void setMaterial(const SoMaterial & material);
  void setMaterial(const SoVRMLMaterial & material);
  const SoMaterial & getMaterial(void) const;
  SbBool isAttachedVRML(void);

  SoGuiMaterialEditor * getEditor(void) const;

protected:
  SoWinMaterialEditor(HWND parent, const char * const name, SbBool embed, SbBool build);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

private:
  void * internals;

}; // class SoWinMaterialEditor

// *************************************************************************

#endif // !COIN_SOWINMATERIALEDITOR_H
