/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef ADD_AUDIO_TRACK_WINDOW_H
#define ADD_AUDIO_TRACK_WINDOW_H

#include <Window.h>

class BPopUpMenu;

const uint32 kAddAudioTrackSelected = '_aat';
const uint32 kAddAudioTrackCanceled = '_aac';

class AddAudioTrackWindow : public BWindow {
	public:
		AddAudioTrackWindow(BLooper* looper);

		virtual void MessageReceived(BMessage* msg);
		virtual bool QuitRequested();

	private:
		void PopulateMenu(BPopUpMenu* menu);

		BLooper* fLooper;
		int32 fLastChannels;
};

#endif // ADD_AUDIO_TRACK_WINDOW_H
