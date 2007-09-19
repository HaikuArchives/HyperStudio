
#include <Menu.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <Message.h>
#include <View.h>

#include "AddAudioTrackWindow.h"

AddAudioTrackWindow::AddAudioTrackWindow()
	: BWindow(BRect(50,50,300,200),
	          "Add audio track",
	          B_MODAL_WINDOW_LOOK,
	          B_MODAL_APP_WINDOW_FEEL,
	          B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS)
{
	BView* child = new BView(Bounds(), "AddAudioTrackView",
	                         B_FOLLOW_ALL, B_FULL_UPDATE_ON_RESIZE);

	BMenu* menu = new BMenu("             ");
	_PopulateMenu(menu);
	BMenuField* field = new BMenuField(BRect(0,0,150,20),
	                                   "AddAudioTrackChannels", "&Channels:", menu);
	child->ResizeToPreferred();
	child->AddChild(field);

	AddChild(child);
}

void
AddAudioTrackWindow::_PopulateMenu(BMenu* menu)
{
	// TODO: Get the maximum number of channels supported by the output device
	BMessage* msg;

	msg = new BMessage(kAddAudioTrack);
	msg->AddInt32("channels", 1);
	menu->AddItem(new BMenuItem("Mono", msg));
	delete msg;

	msg = new BMessage(kAddAudioTrack);
	msg->AddInt32("channels", 2);
	menu->AddItem(new BMenuItem("Stereo", msg));
	delete msg;
}
