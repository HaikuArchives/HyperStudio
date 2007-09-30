/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef NEW_PROJECT_WINDOW_H
#define NEW_PROJECT_WINDOW_H

#include <Window.h>

const uint32 kNewProjectSelected = '_nps';
const uint32 kNewProjectCanceled = '_npc';

class BListView;

class NewProjectWindow : public BWindow {
	public:
		NewProjectWindow(BLooper* Looper);

		virtual void MessageReceived(BMessage* msg);
		virtual bool QuitRequested();

	private:
		BRect CenteredRect();

		BLooper* fLooper;
		BListView* fTemplateListView;
};

#endif // NEW_PROJECT_WINDOW_H
