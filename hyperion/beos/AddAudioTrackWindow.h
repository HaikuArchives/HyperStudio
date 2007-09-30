
#ifndef ADD_AUDIO_TRACK_WINDOW_H
#define ADD_AUDIO_TRACK_WINDOW_H

#include <Window.h>

class BPopUpMenu;

const uint32 kAddAudioTrackSelected = '_aat';
const uint32 kAddAudioTrackCanceled = '_aac';

class AddAudioTrackWindow : public BWindow
{
public:
	AddAudioTrackWindow(BLooper* looper);

	void MessageReceived(BMessage* msg);
	bool QuitRequested();

private:
	void PopulateMenu(BPopUpMenu* menu);

	BLooper* fLooper;
	int32 fLastChannels;
};

#endif // ADD_AUDIO_TRACK_WINDOW_H
