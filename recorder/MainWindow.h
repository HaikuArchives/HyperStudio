/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Window.h>

class BBitmap;
class BMenuBar;
class BMenu;
class BMenuItem;
class BFilePanel;
class NewProjectWindow;
class AddAudioTrackWindow;
class TransportWindow;
class TimelineView;

class MainWindow : public BWindow {
	public:
		MainWindow(BRect frame);
		virtual ~MainWindow();

		virtual bool QuitRequested();
		virtual void MessageReceived(BMessage* msg);

	private:
		void _RefsReceived(BMessage* msg);
		void _SaveRequested(BMessage* msg);
		void InitMenus();
		void InitViews();
		bool CloseProject();

		BMenuBar* fMenuBar;
		BMenu* fRecentMenu;
		BFilePanel* fOpenPanel;
		BFilePanel* fSavePanel;
		TimelineView* fTimelineView;
		NewProjectWindow* fNewPrjWindow;
		AddAudioTrackWindow* fAddAudioTrackWindow;
		TransportWindow* fTransport;
};

#endif // MAIN_WINDOW_H
