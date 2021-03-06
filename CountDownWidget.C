/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <boost/lexical_cast.hpp>

#include <Wt/WTimer>
#include "CountDownWidget.h"

CountDownWidget::CountDownWidget(mse::CInt start, mse::CInt stop, mse::CSize_t msec,
	mse::TSaferPtrForLegacy<WContainerWidget> parent)
  : WText(parent),
    done_(this),
    start_(start),
    stop_(stop)
{
  stop_ = std::min(start_ - 1, stop_);  // stop must be smaller than start
  current_ = start_;

  timer_ = Wt::WWidgetNew<WTimer>(this);
  timer_->setInterval(mse::CInt(msec));
  timer_->timeout().connect(this, &CountDownWidget::timerTick);
  timer_->start();

  setText(boost::lexical_cast<std::string>(current_));
}

void CountDownWidget::cancel()
{
  timer_->stop();
}

void CountDownWidget::timerTick()
{
  setText(boost::lexical_cast<std::string>(--current_));

  if (current_ <= stop_) {
    timer_->stop();
    done_.emit();
  }
}
