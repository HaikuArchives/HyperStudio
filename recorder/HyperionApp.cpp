/*
 * Copyright 2007-2009 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the GPL v3 License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#include <AppFileInfo.h>
#include <Autolock.h>
#include <Bitmap.h>
#include <Entry.h>
#include <Mime.h>
#include <List.h>
#include <Path.h>
#include <Resources.h>
#include <Roster.h>
#include <Screen.h>

#include <unistd.h>

#include "libcore/HyperStudio.h"
#include "libcore/HyperStudioDebug.h"
#include "AboutWindow.h"
#include "HyperionApp.h"
#include "MainWindow.h"

RecorderApp::RecorderApp()
	: BApplication(HYPERSTUDIO_RECORDER_SIGNATURE),
	fWins(new BList),
	fFirstWindow(NewWindow())
{
	// Installing MIME type
	BMimeType projectType("application/x-hyperstudio-project");
	if (projectType.InitCheck() == B_OK) {
		if (!projectType.IsInstalled()) {
			app_info info;
			GetAppInfo(&info);
			BFile appFile(&(info.ref), B_READ_ONLY);
			BResources res(&appFile, false);

			size_t len = 0;
			BBitmap* icon = NULL;
			void* iconBits = NULL;

			iconBits = res.FindResource('ICON', "BEOS:L:application/x-hyperstudio-project", &len);
			if (iconBits) {
				icon = new BBitmap(BRect(0, 0, 31, 31), B_CMAP8);
				icon->SetBits(iconBits, len, 0, B_CMAP8);
				projectType.SetIcon(icon, B_LARGE_ICON);
				delete icon;
				icon = NULL;
				len = 0;
			}

			iconBits = res.FindResource('ICON', "BEOS:M:application/x-hyperion", &len);
			if (iconBits) {
				icon = new BBitmap(BRect(0, 0, 15, 15), B_CMAP8);
				icon->SetBits(iconBits, len, 0, B_CMAP8);
				projectType.SetIcon(icon, B_MINI_ICON);
				delete icon;
				icon = NULL;
				len = 0;
			}

			// Extensions
			BMessage extensions;
			extensions.AddString("extensions", "hprj");
			projectType.SetFileExtensions(&extensions);
			projectType.SetShortDescription("Recorder Project File");
			projectType.SetLongDescription("Recorder Project File.");

			// Set Preferred Application
			projectType.SetPreferredApp(HYPERSTUDIO_RECORDER_SIGNATURE, B_OPEN);
			projectType.Install();
		}
	}
}

RecorderApp::~RecorderApp()
{
}

BWindow*
RecorderApp::NewWindow()
{
	BAutolock _(this);
	// TODO: load last size and position from preferences
	BScreen screen;
	BRect frame = screen.Frame();
	frame.left = frame.top = 50.0f;
	frame.right /= 1.5f;
	frame.bottom /= 1.5f;
	BWindow* win = new MainWindow(frame);
	fWins->AddItem(win);
	return win;
}

void
RecorderApp::RefsReceived(BMessage* msg)
{
	entry_ref ref;

	// The user:
	// - dropped a file (or files) or
	// - clicked on Project|Open menu item or
	// - double clicked a file handled by this application

	// For each file we create a new window and send it
	// a B_REFS_RECEIVED message.
	for (int32 i = 0; msg->FindRef("refs", i, &ref) == B_OK; i++) {
		BWindow* win = i == 0 ? fFirstWindow : NewWindow();
		BMessage m(B_REFS_RECEIVED);
		m.AddRef("refs", &ref);
		DBGMSG(("i=%ld, B_REFS_RECEIVED for %s\n", i, ref.name));
		win->PostMessage(&m);
	}
}

void 
RecorderApp::ArgvReceived(int32 argc, char** argv)
{
	char cwd[B_PATH_NAME_LENGTH];
	getcwd(cwd, sizeof(cwd));

	BMessage m(B_REFS_RECEIVED);

	for (int32 i = 1; i < argc; i++) {
		BPath path;
		if (argv[i][0] != '/')
			path.SetTo(cwd, argv[i]);
		else
			path.SetTo(argv[i]);
		BEntry entry(path.Path(), true);
		if (!entry.Exists() || !entry.IsFile())
			continue;

		entry_ref ref;
		if (B_OK == entry.GetRef(&ref))
			m.AddRef("refs", &ref);
	}

	if (m.HasRef("refs"))
		RefsReceived(&m);
}

bool
RecorderApp::QuitRequested()
{
	// Close all windows but even if only one couldn't be
	// closed we cannot quit the application!
	bool retval = true;
	BWindow* win;
	for (int32 i = 0; (win = (BWindow*)fWins->ItemAt(i)); i++) {
		win->Lock();
		if (!win->QuitRequested()) {
			win->Unlock();
			retval = false;
			break;
		}
		win->Quit();
	}

	return retval;
}

void
RecorderApp::AboutRequested()
{
	const char* authors[] = { "Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>", NULL };
	AboutWindow* w = new AboutWindow("HyperStudio Recorder", 2007, authors, "Multi-track audio and MIDI recorder.");
	w->Show();
}
