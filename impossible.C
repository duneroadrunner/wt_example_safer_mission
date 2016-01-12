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
#include "mseregisteredforlegacy.h"

mse::TRegisteredPointerForLegacy<WApplication> createApplication(const WEnvironment& env)
{
  mse::TRegisteredPointerForLegacy<WApplication> appl = mse::registered_new_for_legacy<WApplication>(env);

  new WText("<h1>Your mission</h1>", appl->root());
  mse::TRegisteredPointerForLegacy<WText> secret
	  = mse::registered_new_for_legacy<WText>("Your mission, Jim, should you accept, is to create solid "
		"web applications.",
		appl->root());

  new WBreak(appl->root()); new WBreak(appl->root());

  new WText("This program will quit in ", appl->root());
  mse::TRegisteredPointerForLegacy<CountDownWidget> countdown = mse::registered_new_for_legacy<CountDownWidget>(10, 0, 1000, appl->root());
  new WText(" seconds.", appl->root());

  new WBreak(appl->root()); new WBreak(appl->root());

  mse::TRegisteredPointerForLegacy<WPushButton> cancelButton = mse::registered_new_for_legacy<WPushButton>("Cancel!", appl->root());
  mse::TRegisteredPointerForLegacy<WPushButton> quitButton = mse::registered_new_for_legacy<WPushButton>("Quit", appl->root());
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
