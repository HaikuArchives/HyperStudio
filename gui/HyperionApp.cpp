
#include <Autolock.h>
#include <Entry.h>
#include <Path.h>
#include <Screen.h>

#include <unistd.h>

#include "AboutWindow.h"
#include "HyperionApp.h"
#include "MainWindow.h"

HyperionApp::HyperionApp()
	: BApplication(HYPERION_SIGNATURE),
	  fFirstWindow(NewWindow())
{
}

HyperionApp::~HyperionApp()
{
}

BWindow*
HyperionApp::NewWindow()
{
	BAutolock _(this);
	// TODO: load last size and position from preferences
	BScreen screen;
	BRect frame = screen.Frame();
	frame.left = frame.top = 50.0f;
	frame.right /= 1.5f;
	frame.bottom /= 1.5f;
	return new MainWindow(frame);
}

void
HyperionApp::RefsReceived(BMessage* msg)
{
	entry_ref ref;

	// The user:
	// - dropped a file (or files) or
	// - clicked on Project|Open menu item or
	// - double clicked a file handled by this application

	// For each file we create a new window and send it
	// a B_REFS_RECEIVED message.
	for (int32 i = 0; msg->FindRef("refs", i, &ref) == B_OK; i++) {
		BWindow* win = (i == 0 && IsLaunching()) ? fFirstWindow : NewWindow();
		BMessage m(B_REFS_RECEIVED);
		m.AddRef("refs", &ref);
		win->PostMessage(&m);
	}
}

void 
HyperionApp::ArgvReceived(int32 argc, char** argv)
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

void
HyperionApp::AboutRequested()
{
	const char* authors[] = { "Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>", NULL };
	AboutWindow* w = new AboutWindow("Hyperion", 2007, authors, "Audio and MIDI sequencer.");
	w->Show();
}
