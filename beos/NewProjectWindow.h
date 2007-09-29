
#ifndef NEW_PROJECT_WINDOW_H
#define NEW_PROJECT_WINDOW_H

#include <Window.h>

const uint32 kNewProjectSelected = '_nps';
const uint32 kNewProjectCanceled = '_npc';

class BListView;

class NewProjectWindow : public BWindow
{
public:
	NewProjectWindow(BLooper* Looper);

	virtual void MessageReceived(BMessage* msg);
	virtual bool QuitRequested();

private:
	BRect CenteredRect();

	BLooper* fLooper;
	BListView* fTemplateListView;
};

#endif // NEW_PROJECT_WINDOW_H
