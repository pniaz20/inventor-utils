/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

// $Id$

#ifndef SOXT_SLIDERSET_H
#define SOXT_SLIDERSET_H

#include <Inventor/Xt/SoXtSliderSetBase.h>

class SoXtSlider;
struct SoXtSliderSetClosure;

// *************************************************************************

class SOXT_DLL_API SoXtSliderSet : public SoXtSliderSetBase {
  SOXT_OBJECT_ABSTRACT_HEADER(SoXtSliderSet, SoXtSliderSetBase);

public:
  SoXtSliderSet(
    const Widget parent,
    const char * const name,
    const SbBool embed,
    SoNode * const node);

  virtual void setNode(SoNode * node);
  void updateLayout(void);

protected:
  SoXtSliderSet(
    const Widget parent,
    const char * const name,
    const SbBool embed,
    SoNode * const node,
    const SbBool build);
  ~SoXtSliderSet(void);

  Widget buildWidget(Widget parent);

private:
  void constructor(const SbBool build);

  void buildSliderModule(const Widget rowcolumn);
  void buildSliderSet(const Widget rowcolumn);

  void folding(SoXtSliderSetClosure * closure, Widget button);
  static void folding_cb(Widget, XtPointer, XtPointer);
  void style(SoXtSliderSetClosure * closure);
  static void style_cb(Widget, XtPointer, XtPointer);
  void slider(SoXtSliderSetClosure * closure, char * title, float value);
  static void slider_cb(void * closure, char * title, float value);

private:
  int numSliders;
  SoXtSlider ** sliders;

  SbPList * closures;

}; // class SoXtSliderSet

// *************************************************************************

#endif // ! SOXT_SLIDERSET_H
