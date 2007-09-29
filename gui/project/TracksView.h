
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

	virtual void Draw(BRect updateRect);
	virtual void AttachedToWindow();
	virtual void FrameResized(float width, float height);

	void AddTrack(Track &track);

private:
	void GetMaxSize(float* width, float* height);
	void FixupScrollBars();

	BList *fViews;
	BRect fLastSlot;
};

#endif // TRACKS_VIEW_H
