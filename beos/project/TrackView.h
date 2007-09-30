
#ifndef TRACK_VIEW_H
#define TRACK_VIEW_H

#include <View.h>

class Track;

class TrackView : public BView
{
public:
	TrackView(BRect frame, Track &track);

	void Draw(BRect updateRect);
};

#endif // TRACK_VIEW_H
