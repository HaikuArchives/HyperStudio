

#include "TimeLineView.h"
#include "Track.h"
#include "TrackView.h"

TrackView::TrackView(BRect frame, Track &track)
	: BView(frame, "TrackView",
	        B_FOLLOW_ALL,
	        B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE)
{
	SetViewColor(B_TRANSPARENT_COLOR);
}

void
TrackView::Draw(BRect updateRect)
{
	BRect r = Bounds();
	rgb_color bg_color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                                B_LIGHTEN_2_TINT);
	rgb_color color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                             B_DARKEN_1_TINT);

	// Fill background
	SetLowColor(bg_color);
	FillRect(r, B_SOLID_LOW);

	// Draw bottom border
	SetHighColor(color);
	StrokeLine(r.LeftBottom(), r.RightBottom());
}
