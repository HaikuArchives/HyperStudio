
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

#include "AboutWindow.h"
#include "Hyperion.h"
#include "HyperionDebug.h"
#include "HyperionApp.h"
#include "MainWindow.h"

HyperionApp::HyperionApp()
	: BApplication(HYPERION_SIGNATURE),
	  fWins(new BList),
	  fFirstWindow(NewWindow())
{
	// Installing MIME type
	BMimeType projectType("application/x-hyperion");
	if (projectType.InitCheck() == B_OK) {
		if (!projectType.IsInstalled()) {
			app_info info;
			GetAppInfo(&info);
			BFile appFile(&(info.ref), B_READ_ONLY);
			BResources res(&appFile, false);

			size_t len = 0;
			BBitmap* icon = NULL;
			void* iconBits = NULL;

			iconBits = res.FindResource('ICON', "BEOS:L:application/x-hyperion", &len);
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
			projectType.SetShortDescription("Hyperion Project File");
			projectType.SetLongDescription("Hyperion Project File.");

			// Set Preferred Application
			projectType.SetPreferredApp(HYPERION_SIGNATURE, B_OPEN);
			projectType.Install();
		}
	}
}

HyperionApp::~HyperionApp()
{
	// Delete windows invidually and the list
	BWindow* item;
	for (int32 i = 0; (item = (BWindow*)fWins->ItemAt(i)); i++)
		delete item;
	delete fWins;
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
	BWindow* win = new MainWindow(frame);
	fWins->AddItem(win);
	return win;
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
		BWindow* win = i == 0 ? fFirstWindow : NewWindow();
		BMessage m(B_REFS_RECEIVED);
		m.AddRef("refs", &ref);
		DBGMSG(("i=%d, B_REFS_RECEIVED for %s\n", i, ref.name));
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

bool
HyperionApp::QuitRequested()
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
HyperionApp::AboutRequested()
{
	const char* authors[] = { "Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>", NULL };
	AboutWindow* w = new AboutWindow("Hyperion", 2007, authors, "Audio and MIDI sequencer.");
	w->Show();
}
