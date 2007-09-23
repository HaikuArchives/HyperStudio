
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Window.h>

class BBitmap;
class BMenuBar;
class BMenu;
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
	void InitMenus();
	void InitViews();
	void _RefsReceived(BMessage* msg);
	void _SaveRequested(BMessage* msg);
	void NewProject();
	void _SaveProjectAs();
	bool _CloseProject();

	BMenuBar* fMenuBar;
	BMenu* fRecentMenu;
	BFilePanel* fOpenPanel;
	BFilePanel* fSavePanel;
	ProjectView* fPrjView;
};

#endif // MAIN_WINDOW_H
