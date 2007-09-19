
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Window.h>

class BMenuBar;
class BMenuItem;
class BFilePanel;
class ProjectView;

class MainWindow : public BWindow
{
public:
	MainWindow(BRect frame);
	virtual ~MainWindow();

	virtual bool QuitRequested();
	virtual void MessageReceived(BMessage* msg);

private:
	void _InitMenus();
	void _InitViews();
	void _OpenProjectView();
	void _CloseProjectView();
	void _RefsReceived(BMessage* msg);
	void _SaveRequested(BMessage* msg);
	void _NewProject();
	void _SaveProjectAs();
	bool _CloseProject();

	BMenuBar* fMenuBar;
	BMenuItem* fFileSave;
	BMenuItem* fFileSaveAs;
	BMenuItem* fFileClose;
	BMenuItem* fTracksAddAudio;
	BMenuItem* fTracksAddMidi;
	BFilePanel* fOpenPanel;
	BFilePanel* fSavePanel;
	BView* fMainView;
	ProjectView* fPrjView;
};

#endif // MAIN_WINDOW_H
