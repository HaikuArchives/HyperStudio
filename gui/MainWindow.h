
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Window.h>

class BBitmap;
class BMenuBar;
class BMenu;
class BMenuItem;
class BFilePanel;
class ProjectView;
class NewProjectWindow;

class MainWindow : public BWindow
{
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
	ProjectView* fPrjView;
	NewProjectWindow* fNewPrjWindow;
};

#endif // MAIN_WINDOW_H
