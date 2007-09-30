/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#include <Button.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <Message.h>
#include <PopUpMenu.h>
#include <Screen.h>
#include <View.h>

#include "AddAudioTrackWindow.h"

// Local message
const uint32 kAddAudioTrackConfirm = '_aok';

// User interface constants
const uint32 kBorderSpace = 5;
const uint32 kItemSpace = 7;

AddAudioTrackWindow::AddAudioTrackWindow(BLooper* looper)
	: BWindow(BRect(0.0f, 0.0f, 1.0f, 1.0f), "Add audio track", B_TITLED_WINDOW_LOOK,
		B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS),
	fLooper(looper),
	fLastChannels(0)
{
	// Add the main view
	BView* view = new BView(Bounds(), "AddAudioTrackView", B_FOLLOW_ALL, B_WILL_DRAW);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(view);

	// Add the channels selection menu
	BPopUpMenu* menu = new BPopUpMenu("");
	PopulateMenu(menu);
	menu->SetLabelFromMarked(true);
	BMenuField* field = new BMenuField(BRect(0.0f, 0.0f, 120.0f, 20.0f),
		"AddAudioTrackChannels", "Channels:", menu, true);
	field->SetDivider(view->StringWidth("Channels:   "));
	view->AddChild(field);

	// Add the "OK" button
	BRect rect(100.0f, field->Frame().bottom + kBorderSpace, 1.0f, 1.0f);
	BButton* okButton = new BButton(rect, "ok", "OK",
		new BMessage(kAddAudioTrackConfirm));
	okButton->ResizeToPreferred();
	view->AddChild(okButton);

	// Add the "Cancel" button
	rect = okButton->Frame();
	rect.right = rect.left - kItemSpace;
	rect.left = rect.right - okButton->Frame().Width() + kItemSpace;
	BButton* cancelButton = new BButton(rect, "cancel", "Cancel",
		new BMessage(kAddAudioTrackCanceled));
	cancelButton->ResizeToPreferred();
	view->AddChild(cancelButton);

	// Resize this window to fit its contents
	rect = okButton->Frame();
	ResizeTo(rect.right + 2.0f, rect.bottom + 2.0f);

	// Center this window on the screen
	BScreen screen;
	BRect screenFrame = screen.Frame();
	rect = Frame();
	MoveTo(screenFrame.left + (screenFrame.Width() - rect.Width()) / 2,
	       screenFrame.top + (screenFrame.Height() - rect.Height()) /2);
}

void
AddAudioTrackWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
		case kAddAudioTrackConfirm: {
				BMessage* m = new BMessage(kAddAudioTrackSelected);
				if (m->AddInt32("channels", fLastChannels) == B_OK) {
					fLooper->PostMessage(m);
					PostMessage(B_QUIT_REQUESTED);
				}
			}
			break;
		case kAddAudioTrackCanceled:
			PostMessage(B_QUIT_REQUESTED);
			break;
		case kAddAudioTrackSelected:
			msg->FindInt32("channels", &fLastChannels);
			break;
		default:
			BWindow::MessageReceived(msg);
			break;
	}
}

bool
AddAudioTrackWindow::QuitRequested()
{
	fLooper->PostMessage(kAddAudioTrackCanceled);
	return true;
}

void
AddAudioTrackWindow::PopulateMenu(BPopUpMenu* menu)
{
	// TODO: Get the maximum number of channels supported by the output device

	const char* labels[] = { "Mono", "Stereo" };
	int32 channels[] = { 1, 2 };

	for (int i = 0; i < 2; i++) {
		BMessage* msg = new BMessage(kAddAudioTrackSelected);
		msg->AddInt32("channels", channels[i]);
		BMenuItem* item = new BMenuItem(labels[i], msg);
		item->SetMarked((i == 0));
		menu->AddItem(item);
	}
}
