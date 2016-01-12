/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
// This may look like C code, but it's really -*- C++ -*-
#ifndef WCOUNTDOWNWIDGET_H_
#define WCOUNTDOWNWIDGET_H_

#include <Wt/WText>
#include "wt_ext.h"

namespace Wt {
  class WTimer;
}

using namespace Wt;

/**
 * \defgroup missionexample Timer example
 */
/*@{*/

/*!\brief A widget which displays a decrementing number.
 */
class CountDownWidget : public WText
{
public:
  /*! \brief Create a new CountDownWidget.
   *
   * The widget will count down from start to stop, decrementing
   * the number every msec milliseconds.
   */
  CountDownWidget(mse::CInt start, mse::CInt stop, mse::CSize_t msec,
		  mse::TSaferPtrForLegacy<WContainerWidget> parent = 0);
  virtual ~CountDownWidget() {}

  /*! \brief Signal emitted when the countdown reached stop.
   */
  Wt::Signal<void>& done() { return done_; }

  /*! \brief Cancel the count down.
   */
  void cancel();

private:
  Wt::Signal<void> done_;
  mse::CInt start_;
  mse::CInt stop_;

  mse::CInt current_;

  Wt::WWidgetPtr<WTimer> timer_;

  /*! \brief Process one timer tick.
   */
  void timerTick();
};

/*@}*/

#endif // WCOUNTDOWNWIDGET_H_
