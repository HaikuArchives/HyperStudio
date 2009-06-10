/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#include <Alert.h>
#include <String.h>

#include "HyperionApp.h"

int
main(int argc, char* argv[])
{
	HyperionApp* app = new HyperionApp;
	if (app->InitCheck() != B_OK) {
		BString errMsg;
		errMsg << "The following error occurred loading Hyperion:\n";
		errMsg << strerror(app->InitCheck());
		BAlert* alert = new BAlert("Hyperion Error", errMsg.String(),
			"OK", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT);
		alert->Go();
	}
	else
		app->Run();
	delete app;

	return 0;
}
