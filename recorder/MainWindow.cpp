/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#include <Alert.h>
#include <Application.h>
#include <Bitmap.h>
#include <File.h>
#include <FilePanel.h>
#include <Path.h>
#include <Message.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <StatusBar.h>
#include <String.h>

#include "libcore/HyperStudioDebug.h"
#include "libcore/Project.h"
#include "AddAudioTrackWindow.h"
#include "AppIconMenu.h"
#include "HyperionConsts.h"
#include "MainWindow.h"
#include "NewProjectWindow.h"
#include "TransportWindow.h"

#include "project/TimelineView.h"

MainWindow::MainWindow(BRect frame)
	: BWindow(frame, "HyperStudio Recorder", B_DOCUMENT_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
		B_ASYNCHRONOUS_CONTROLS),
	fOpenPanel(NULL),
	fSavePanel(NULL),
	fNewPrjWindow(NULL),
	fAddAudioTrackWindow(NULL),
	fTimelineView(NULL)
{
	// Create menus
	InitMenus();

	// Create views
	InitViews();

	// Create open and save panels
	fOpenPanel = new BFilePanel(B_OPEN_PANEL, new BMessenger(this));
	fOpenPanel->Window()->SetTitle("Select a project to open:");
	fSavePanel = new BFilePanel(B_SAVE_PANEL, new BMessenger(this));
	fSavePanel->Window()->SetTitle("Save the project to:");

	// Automatically show this window
	Show();

	// Create transport window
	fTransport = new TransportWindow();
	fTransport->Show();
}

MainWindow::~MainWindow()
{
	// Delete open and save panels
	delete fOpenPanel;
	delete fSavePanel;
}

bool
MainWindow::QuitRequested()
{
	// Close the project
	if (!CloseProject())
		return false;

	// Quit the application
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

void
MainWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
	// Open/save panel messages
	case B_REFS_RECEIVED:
		_RefsReceived(msg);
		break;
	case B_SAVE_REQUESTED:
		_SaveRequested(msg);
		break;

	// Menu messages
	case MENU_PROJECT_NEW:
		if (!fNewPrjWindow)
			fNewPrjWindow = new NewProjectWindow(this);
		fNewPrjWindow->Show();
		break;
	case MENU_PROJECT_OPEN:
		fOpenPanel->Show();
		break;
#if 0
	case MENU_PROJECT_SAVE:
		if (fPrjView->CurrentProject()->FileName())
			fPrjView->CurrentProject()->Save();
		else
			fSavePanel->Show();
		break;
#endif
	case MENU_PROJECT_SAVEAS:
		fSavePanel->Show();
		break;
	case MENU_PROJECT_CLOSE:
		Quit();
		break;
	case MENU_TRACKS_ADDAUDIO:
		if (!fAddAudioTrackWindow)
			fAddAudioTrackWindow = new AddAudioTrackWindow(this);
		fAddAudioTrackWindow->Show();
		break;
	case MENU_TRACKS_ADDMIDI:
		break;

#if 0
	// Dialog messages
	case kNewProjectSelected:
		fNewPrjWindow->Hide();
		fPrjView->CurrentProject()->New();
		SetTitle(fPrjView->CurrentProject()->Title());
		break;
#endif
	case kNewProjectCanceled:
		fNewPrjWindow = NULL;
		break;
#if 0
	case kAddAudioTrackSelected: {
			int32 channels = 0;
			if (msg->FindInt32("channels", &channels) == B_OK)
				fPrjView->AddAudioTrack((uint32)channels);
		}
		break;
#endif
	case kAddAudioTrackCanceled:
		fAddAudioTrackWindow = NULL;
		break;

#if 0
	// View messages
	case kScaleChanged:
		fPrjView->Rescale();
		break;
#endif

	// Default handler
	default:
		BWindow::MessageReceived(msg);
		break;
	}
}

void
MainWindow::_RefsReceived(BMessage* msg)
{
	entry_ref ref;

	// Find opened file name
	if (msg->FindRef("refs", &ref) != B_OK)
	{
		BAlert *alert = new BAlert(NULL, "Internal error while opening!", "OK", NULL, NULL,
		                           B_WIDTH_AS_USUAL, B_STOP_ALERT);
		alert->Go();
	}

	// Getn entry path and file name
	BPath path;
	BEntry entry(&ref, true);
	entry.GetPath(&path);

#if 0
	// Load project file
	// TODO: Handle error
	if (fPrjView->CurrentProject()->Load(path.Path()) != B_OK) {
		BAlert* alert = new BAlert(NULL, "Error!", "OK", NULL, NULL,
		                           B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT);
		alert->Go();
		return;
	}

	// Set a new title
	SetTitle(fPrjView->CurrentProject()->Title());
#endif
}

void
MainWindow::_SaveRequested(BMessage* msg)
{
	entry_ref dir_ref, file_ref;
	const char* filename;

	// Find directory and file name
	if (!((msg->FindRef("directory", &dir_ref) == B_OK) &&
	      (msg->FindString("name", &filename) == B_OK)))
	{
		BAlert *alert = new BAlert(NULL, "Internal error while saving!", "OK", NULL, NULL,
		                           B_WIDTH_AS_USUAL, B_STOP_ALERT);
		alert->Go();
	}

	// Get directory full path
	BDirectory dir;
	dir.SetTo(&dir_ref);
	if (dir.InitCheck() != B_OK)
		return;
	BPath path(&dir_ref);
	path.Append(filename);

#if 0
	// Save project file
	// TODO: Handle error
	if (fPrjView->CurrentProject()->SaveAs(path.Path()) != B_OK) {
		BAlert *alert = new BAlert(NULL, "Error!", "OK");
		alert->Go();
	}
#endif
}

void
MainWindow::InitMenus()
{
	fMenuBar = new BMenuBar(BRect(0.0f, 0.0f, 0.0f, 0.0f), "MenuBar");

	BMenu* main = new BMenu("HyperStudio Recorder");
	BMenuItem *about = new BMenuItem("About"B_UTF8_ELLIPSIS, new BMessage(B_ABOUT_REQUESTED));
	about->SetTarget(be_app);
	main->AddItem(about);
	main->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));
	fMenuBar->AddItem(new AppIconMenu(main));

	BMenu* project = new BMenu("Project");
	project->AddItem(new BMenuItem("New"B_UTF8_ELLIPSIS, new BMessage(MENU_PROJECT_NEW), 'N'));
	project->AddItem(new BMenuItem("Open"B_UTF8_ELLIPSIS, new BMessage(MENU_PROJECT_OPEN), 'O'));
	fRecentMenu = new BMenu("Open Recent");
	fRecentMenu->AddSeparatorItem();
	BMenuItem* clearRecent = new BMenuItem("Clear Menu", new BMessage(MENU_PROJECT_CLEAR_RECENT));
	fRecentMenu->AddItem(clearRecent);
	project->AddItem(fRecentMenu);
	project->AddSeparatorItem();
	project->AddItem(new BMenuItem("Close", new BMessage(MENU_PROJECT_CLOSE), 'W'));
	project->AddItem(new BMenuItem("Save", new BMessage(MENU_PROJECT_SAVE), 'S'));
	project->AddItem(new BMenuItem("Save As"B_UTF8_ELLIPSIS, new BMessage(MENU_PROJECT_SAVEAS)));
	project->AddItem(new BMenuItem("Save a Copy As"B_UTF8_ELLIPSIS, new BMessage(MENU_PROJECT_SAVE_COPYAS)));
	project->AddSeparatorItem();
	project->AddItem(new BMenuItem("Import"B_UTF8_ELLIPSIS, new BMessage(MENU_PROJECT_IMPORT)));
	project->AddItem(new BMenuItem("Export mixdown"B_UTF8_ELLIPSIS, new BMessage(MENU_PROJECT_EXPORT)));
	fMenuBar->AddItem(project);

	BMenu* tracks = new BMenu("Tracks");
	tracks->AddItem(new BMenuItem("Add audio track"B_UTF8_ELLIPSIS, new BMessage(MENU_TRACKS_ADDAUDIO)));
	tracks->AddItem(new BMenuItem("Add MIDI track"B_UTF8_ELLIPSIS, new BMessage(MENU_TRACKS_ADDMIDI)));
	fMenuBar->AddItem(tracks);

	// Add menu bar
	fMenuBar->ResizeToPreferred();
	AddChild(fMenuBar);
}

void
MainWindow::InitViews()
{
	fTimelineView = new TimelineView("timeline");

#if 0 // TODO: not sure about this
	// Create and add project view
	BRect r = Bounds();
	r.top = fMenuBar->Frame().Height();
	fPrjView = new ProjectView(r);
	AddChild(fPrjView);

	// Set window title
	SetTitle(fPrjView->CurrentProject()->Title());

	BStatusBar *sbar = new BStatusBar(BRect(0.0f, Bounds().Height() - 10.0f, Bounds().Width(), Bounds().Height()), "StatusBar");
	AddChild(sbar);
#endif
}

bool
MainWindow::CloseProject()
{
#if 0
	// Just exit successfully if already saved
	if (!fPrjView->CurrentProject()->IsModified())
		return true;

	bool saveAs = (fPrjView->CurrentProject()->FileName() != NULL);

	// Prompt for saving if needed
	if (fPrjView->CurrentProject()->IsModified())
	{
		BString warnMsg;
		warnMsg << "Save changes to the project ";
		warnMsg << "\"" << fPrjView->CurrentProject()->Title() << "\"?";
		BAlert *alert = new BAlert("Save changes", warnMsg.String(),
		                           "Cancel", "Don't save", "Save",
		                           B_WIDTH_AS_USUAL, B_OFFSET_SPACING,
		                           B_WARNING_ALERT);
		alert->SetShortcut(0, B_ESCAPE);
		int32 button_index = alert->Go();

		switch (button_index)
		{
		case 0:
			return false;
		case 1:
			break;
		case 2:
			if (!saveAs)
				fPrjView->CurrentProject()->Save();
			break;
		}
	}

	// Save as...
	if (saveAs)
	{
		fSavePanel->Show();
		return false;
	}
#endif

	return true;
}
