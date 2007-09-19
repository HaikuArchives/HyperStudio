
#include <Alert.h>
#include <ScrollView.h>
#include <String.h>

#include "Project.h"
#include "ProjectView.h"
#include "TimeLineView.h"
#include "TracksView.h"
#include "Track.h"

ProjectView::ProjectView(BRect frame)
	: BView(frame, "ProjectView",
	        B_FOLLOW_ALL,
	        B_FULL_UPDATE_ON_RESIZE),
	  fScale(25),
	  fPointer(0)
{
	// Set background color
	rgb_color bg_color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                                B_DARKEN_2_TINT);
	SetViewColor(bg_color);

	BRect frame = Bounds();

	// Add timeline view
	frame.left = 128.0f;
	fTimeLineView = new TimeLineView(frame);
	fTimeLineView->ResizeToPreferred();
	AddChild(fTimeLineView);

	// Add tracks view
	frame.top = fTimeLineView->Bounds().Height();
	frame.bottom = Bounds().Height();
	frame.right -= B_V_SCROLL_BAR_WIDTH;
	frame.bottom -= B_H_SCROLL_BAR_HEIGHT;
	fTracksView = new TracksView(frame);
	AddChild(new BScrollView("TracksScrollView", fTracksView,
	                         B_FOLLOW_ALL_SIDES, B_WILL_DRAW,
	                         true, true, B_NO_BORDER));                       
	//fTracksView->ResizeToPreferred();
}

ProjectView::~ProjectView()
{
	delete fTimeLineView;
	delete fTracksView;
}
