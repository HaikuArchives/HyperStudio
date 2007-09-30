

#include "libcore/Track.h"
#include "TimeLineView.h"
#include "TrackView.h"

TrackView::TrackView(BRect frame, Track &track)
	: BView(frame, "TrackView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	SetViewColor(B_TRANSPARENT_COLOR);
}

void
TrackView::Draw(BRect updateRect)
{
	rgb_color color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                             B_DARKEN_2_TINT);

	// Draw bottom border
	SetHighColor(color);
	StrokeLine(updateRect.LeftBottom(), updateRect.RightBottom());
}
