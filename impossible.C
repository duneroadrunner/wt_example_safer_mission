/*
 * Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "CountDownWidget.h"
#include "wt_ext.h"

Wt::WWidgetPtr<WApplication> createApplication(const WEnvironment& env)
{
  Wt::WWidgetPtr<WApplication> appl = Wt::WWidgetNew<WApplication>(env);

  new WText("<h1>Your mission</h1>", appl->root());
  Wt::WWidgetPtr<WText> secret
	  = Wt::WWidgetNew<WText>("Your mission, Jim, should you accept, is to create solid "
		"web applications.",
		appl->root());

  new WBreak(appl->root()); new WBreak(appl->root());

  new WText("This program will quit in ", appl->root());
  Wt::WWidgetPtr<CountDownWidget> countdown = Wt::WWidgetNew<CountDownWidget>(10, 0, 1000, appl->root());
  new WText(" seconds.", appl->root());

  new WBreak(appl->root()); new WBreak(appl->root());

  Wt::WWidgetPtr<WPushButton> cancelButton = Wt::WWidgetNew<WPushButton>("Cancel!", appl->root());
  Wt::WWidgetPtr<WPushButton> quitButton = Wt::WWidgetNew<WPushButton>("Quit", appl->root());
  quitButton->clicked().connect((WApplication*)appl, &WApplication::quit);

  countdown->done().connect((WApplication*)appl, &WApplication::quit);
  cancelButton->clicked().connect((CountDownWidget*)countdown, &CountDownWidget::cancel);
  cancelButton->clicked().connect((WPushButton*)cancelButton, &WFormWidget::disable);
  cancelButton->clicked().connect((WText*)secret, &WWidget::hide);

  return appl;
}

int main(int argc, char **argv)
{
   return WRun(argc, argv, &createApplication);
}
