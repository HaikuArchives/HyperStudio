
#include <Button.h>
#include <Entry.h>
#include <ListView.h>
#include <Screen.h>
#include <ScrollView.h>
#include <String.h>
#include <StringView.h>
#include <View.h>

#include <stdlib.h>
#include <string.h>

#include "NewProjectWindow.h"

const uint32 kTemplateInvoked = 'tmpl';

class TemplateListItem : public BStringItem
{
public:
	TemplateListItem(const char* name, const char* filename)
		: BStringItem(name),
		  fFileName(filename) {}

	const char* FileName() const { return fFileName.String(); }

private:
	BString fFileName;
};

NewProjectWindow::NewProjectWindow(BLooper* Looper)
	: BWindow(CenteredRect(), "New...", B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL,
	          B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_ASYNCHRONOUS_CONTROLS),
	  fLooper(Looper)
{
	BRect rect;

	BView* view = new BView(Bounds(), "NewProjectView", B_FOLLOW_ALL, B_WILL_DRAW);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(view);

	rect = BRect(4.0f, 4.0f, 0.0f, 0.0f);
	BStringView* label1 = new BStringView(rect, "CollectionLabel", "Collection");
	label1->ResizeToPreferred();
	view->AddChild(label1);

	rect = label1->Frame();
	rect = BRect(rect.left, rect.bottom + 1.0f, rect.left + 100.0f, rect.bottom + 201.0f);
	BListView* collectionListView = new BListView(rect, "Collection");
	BScrollView* scrollCollection = new BScrollView("ScrollCollection", collectionListView,
		B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true);
	view->AddChild(scrollCollection);

	rect = scrollCollection->Frame();
	rect = BRect(rect.Width() + 8.0f, 4.0f, 0.0f, 0.0f);
	BStringView* label2 = new BStringView(rect, "TemplateLabel", "Template");
	label2->ResizeToPreferred();
	view->AddChild(label2);

	rect = label2->Frame();
	rect = BRect(rect.left, rect.bottom + 1.0f, rect.left + 200.0f, rect.bottom + 201.0f);
	fTemplateListView = new BListView(rect, "Template");
	fTemplateListView->SetInvocationMessage(new BMessage(kTemplateInvoked));
	BScrollView* scrollTemplate = new BScrollView("ScrollTemplate", fTemplateListView,
		B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true);
	view->AddChild(scrollTemplate);

	// TODO: load from disk
	collectionListView->AddItem(new BStringItem("Produce"));
	fTemplateListView->AddItem(new TemplateListItem("Empty Project", NULL));
}

void
NewProjectWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
	case kTemplateInvoked: {
			int index = fTemplateListView->CurrentSelection();
			if (index < 0)
				break;

			TemplateListItem* item =
				(TemplateListItem*)fTemplateListView->ItemAt(index);
			
			// Post message with the selected template to the main window
			BMessage* m = new BMessage(kNewProjectSelected);
			if (item->FileName())
			{
				entry_ref ref;
				get_ref_for_path(item->FileName(), &ref);
				m->AddRef("ref", &ref);
			}
			fLooper->PostMessage(m);
		}
		break;
	default:
		BWindow::MessageReceived(msg);
		break;
	}
}

bool
NewProjectWindow::QuitRequested()
{
	fLooper->PostMessage(kNewProjectCanceled);
	return true;
}

BRect
NewProjectWindow::CenteredRect()
{
	BScreen screen;
	BRect screenFrame = screen.Frame();
	BRect frame = BRect(0.0f, 0.0f, 345.0f, 226.0f);

	frame.OffsetTo(screenFrame.left + (screenFrame.Width() - frame.Width()) / 2,
	               screenFrame.top + (screenFrame.Height() - frame.Height()) /2); 
	return frame;
}
