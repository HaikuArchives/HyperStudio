
#ifndef ADD_AUDIO_TRACK_WINDOW_H
#define ADD_AUDIO_TRACK_WINDOW_H

#include <Window.h>

class BMenu;

const uint32 kAddAudioTrack = 'aatw';

class AddAudioTrackWindow : public BWindow
{
public:
	AddAudioTrackWindow();

private:
	void _PopulateMenu(BMenu* menu);
};

#endif // ADD_AUDIO_TRACK_WINDOW_H
