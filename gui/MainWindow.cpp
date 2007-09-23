
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

#include "AddAudioTrackWindow.h"
#include "AppIconMenu.h"
#include "Exception.h"
#include "Hyperion.h"
#include "HyperionConsts.h"
#include "MainWindow.h"
#include "NewProjectWindow.h"
#include "Project.h"
#include "ProjectView.h"

MainWindow::MainWindow(BRect frame)
	: BWindow(frame, "HyperionWindow",
	          B_DOCUMENT_WINDOW_LOOK,
	          B_NORMAL_WINDOW_FEEL,
	          B_ASYNCHRONOUS_CONTROLS),
	  fOpenPanel(NULL),
	  fSavePanel(NULL)
{
	// Create menus
	InitMenus();

	// Create views
	InitViews();

	// Automatically show this window
	Show();
}

MainWindow::~MainWindow()
{
	// Delete open and save panels
	if (fOpenPanel)
		delete fOpenPanel;
	if (fSavePanel)
		delete fSavePanel;
}

bool
MainWindow::QuitRequested()
{
	// Close the project
	if (!_CloseProject())
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
	case B_REFS_RECEIVED:
		_RefsReceived(msg);
		break;
	case B_SAVE_REQUESTED:
		_SaveRequested(msg);
		break;

	// Menu messages
	case MENU_PROJECT_NEW:
		NewProject();
		break;
	case MENU_PROJECT_OPEN:
		if (!fOpenPanel)
		{
			fOpenPanel = new BFilePanel(B_OPEN_PANEL, &be_app_messenger);
			fOpenPanel->Window()->SetTitle("Select a project to open:");
		}
		fOpenPanel->Show();
		break;
#if 0
	case MENU_PROJECT_SAVE:
		if (project->FileName())
			project->Save();
		else
			_SaveProjectAs();
		break;
#endif
	case MENU_PROJECT_SAVEAS:
		_SaveProjectAs();
		break;
	case MENU_PROJECT_CLOSE:
		_CloseProject();
		break;
	case MENU_TRACKS_ADDAUDIO: {
			AddAudioTrackWindow* win = new AddAudioTrackWindow();
			win->Show();
		}
		break;
	case MENU_TRACKS_ADDMIDI:
		break;

	// Default handler
	default:
		BWindow::MessageReceived(msg);
		break;
	}
}

void
MainWindow::InitMenus()
{
	fMenuBar = new BMenuBar(BRect(0.0f, 0.0f, 0.0f, 0.0f), "MenuBar");

	BMenu* main = new BMenu("Hyperion");
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
	// Create and add project view
	BRect r = Bounds();
	r.top = fMenuBar->Frame().Height();
	fPrjView = new ProjectView(r);
	AddChild(fPrjView);

	// Set window title
	SetTitle(fPrjView->CurrentProject()->Title());

#if 0 // TODO: not sure about this
	BStatusBar *sbar = new BStatusBar(BRect(0.0f, Bounds().Height() - 10.0f, Bounds().Width(), Bounds().Height()), "StatusBar");
	AddChild(sbar);
#endif
}

void
MainWindow::_RefsReceived(BMessage* msg)
{
#if 0
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

	// Load project file
	try {
		project->Load(path.Path());
	} catch (Hyperion::Exception e) {
		BAlert* alert = new BAlert(NULL, e.what(), "OK", NULL, NULL,
		                           B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_STOP_ALERT);
		alert->Go();
		return;
	}

	// Set a new title
	BString newTitle;
	newTitle << "Hyperion - " << project->Title();
	SetTitle(newTitle.String());

	// Create the project view
	_OpenProjectView();
#endif
}

void
MainWindow::_SaveRequested(BMessage* msg)
{
#if 0
	// If we didn't open/create a project, just exit
	if (!project)
		return;

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

	// Save project file
	try {
		project->SaveAs(path.Path(), filename);
	} catch (Hyperion::Exception e) {
		BAlert *alert = new BAlert(NULL, e.what(), "OK");
		alert->Go();
	}
#endif
}

void
MainWindow::NewProject()
{
	NewProjectWindow* w = new NewProjectWindow;
	w->Show();
}

void
MainWindow::_SaveProjectAs()
{
	if (!fSavePanel)
	{
		fSavePanel = new BFilePanel(B_SAVE_PANEL, new BMessenger(this));
		fSavePanel->Window()->SetTitle("Save the project to:");
	}
	fSavePanel->Show();	
}

bool
MainWindow::_CloseProject()
{
#if 0
	bool saveAs = !project->FileName();

	// Prompt for saving if needed
	if (project->IsModified())
	{
		BString warnMsg;
		warnMsg << "Save changes to the project ";
		warnMsg << "\"" << project->Title() << "\"?";
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
				project->Save();
			break;
		}
	}

	// Save as...
	if (saveAs)
		_SaveProjectAs();

	// Close the project view
	_CloseProjectView();
#endif

	return true;
}
