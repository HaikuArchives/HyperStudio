
#ifndef TRACKS_VIEW_H
#define TRACKS_VIEW_H

#include <View.h>

class BList;
class Track;

class TracksView : public BView
{
public:
	TracksView(BRect frame);
	virtual ~TracksView();

	virtual void AttachedToWindow();
	virtual void FrameResized(float width, float height);
	virtual void MessageReceived(BMessage *msg);

	void AddTrack(Track &track);

private:
	void FixupScrollBars();

	BList *fTrackViews;
	BRect fLastSlot;
};

#endif // TRACKS_VIEW_H
