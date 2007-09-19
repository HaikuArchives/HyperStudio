
#include <List.h>
#include <Message.h>

#include "Track.h"
#include "TracksView.h"
#include "TrackView.h"

TracksView::TracksView(BRect frame)
	: BView(frame, "TracksView",
	        B_FOLLOW_ALL,
	        B_FULL_UPDATE_ON_RESIZE)
{
	// Background color
	rgb_color bg_color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                                B_LIGHTEN_1_TINT);
	SetViewColor(bg_color);

	// Initialize memebers
	fTrackViews = new BList;
	fLastSlot = BRect(0.0f, 0.0f, Bounds().Width()*4, 128.0f);
}

TracksView::~TracksView()
{
	// TODO: delete all views
	delete fTrackViews;
}

void
TracksView::AttachedToWindow()
{
	FixupScrollBars();
}

void
TracksView::FrameResized(float width, float height)
{
	FixupScrollBars();
}

void
TracksView::MessageReceived(BMessage *msg)
{
	BView::MessageReceived(msg);
}

void
TracksView::AddTrack(Track &track)
{
	// Add track view
	TrackView *view = new TrackView(fLastSlot, track);
	fTrackViews->AddItem(view);
	AddChild(view);

	// Update last slot position
	fLastSlot.top = fLastSlot.bottom + fTrackViews->CountItems();
	fLastSlot.bottom += 128.0f + fTrackViews->CountItems();
}

void
TracksView::FixupScrollBars()
{
}
