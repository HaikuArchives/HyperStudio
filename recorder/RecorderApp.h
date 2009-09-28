/*
 * Copyright 2007-2009 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the GPL v3 License.
 */
#ifndef RECORDER_APP_H
#define RECORDER_APP_H

#include <Application.h>

class BList;
class BWindow;

class RecorderApp : public BApplication
{
public:
				RecorderApp();
	virtual			~RecorderApp();

		BWindow*	NewWindow();

	virtual	void		RefsReceived(BMessage* msg);
	virtual void		ArgvReceived(int32 argc, char** argv);
	virtual bool		QuitRequested();
	virtual void		AboutRequested();

private:
		BList*		fWins;
		BWindow*	fFirstWindow;
};

#endif // RECORDER_APP_H
