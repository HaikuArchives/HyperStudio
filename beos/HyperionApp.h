/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef HYPERION_APP_H
#define HYPERION_APP_H

#include <Application.h>

class BList;
class BWindow;

class HyperionApp : public BApplication {
	public:
		HyperionApp();
		virtual ~HyperionApp();

		BWindow* NewWindow();

		virtual void RefsReceived(BMessage* msg);
		virtual void ArgvReceived(int32 argc, char** argv);
		virtual bool QuitRequested();
		virtual void AboutRequested();

	private:
		BList* fWins;
		BWindow* fFirstWindow;
};

#endif // HYPERION_APP_H
