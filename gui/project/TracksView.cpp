
#include <List.h>
#include <Message.h>
#include <ScrollBar.h>

#include "ProjectView.h"
#include "Track.h"
#include "TracksView.h"
#include "TrackView.h"

TracksView::TracksView(BRect frame)
	: BView(frame, "TracksView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS)
{
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
TracksView::Draw(BRect updateRect)
{
	rgb_color bg_color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                                B_LIGHTEN_1_TINT);
	rgb_color white = (rgb_color){ 255, 255, 255 };

	// Update background
	SetLowColor(bg_color);
	FillRect(updateRect, B_SOLID_LOW);

	// Get scale from project settings
	ProjectView *parent = dynamic_cast<ProjectView*>(Parent()->Parent());
	uint32 scale = parent->Scale();

	int32 start = (int32(updateRect.left / scale) ) * scale;
	int32 end = (int32(updateRect.right / scale) + 1) * scale;
	int32 nb = (end - start) / scale * 2 + 3;
	int32 height = Bounds().IntegerHeight(); // FIXME: max height

	// Draw if the rectangle is large enough
	if (nb <= 0)
		return;

	// Draw lines
	BeginLineArray(nb);
	for (int32 i = start; i <= end; i += scale)
	{
		AddLine(BPoint(i, 0),
		        BPoint(i, height), white);
		AddLine(BPoint(i + scale / 2, 0),
		        BPoint(i + scale / 2, height), white);
	}
	EndLineArray();
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
	BScrollBar* sb;

	// Get size
	float width = Bounds().Width();
	float height = Bounds().Height();

	// Get max size
	float maxWidth = width * 2.0f;
	float maxHeight = height * 2.0f;

	// Proportional size
	float propWidth = width / maxWidth;
	float propHeight = height / maxHeight;

	// Range size
	float rangeWidth = maxWidth - width;
	float rangeHeight = maxHeight - height;

	// Fix horizontal scrollbar
	if ((sb = ScrollBar(B_HORIZONTAL)) != NULL) {
		sb->SetProportion(propWidth);
		sb->SetRange(0, rangeWidth);
		sb->SetSteps(width / 8.0f, width / 2.0f);
	}

	// Fix vertical scrollbar
	if ((sb = ScrollBar(B_VERTICAL)) != NULL) {
		sb->SetProportion(propHeight);
		sb->SetRange(0, rangeHeight);
		sb->SetSteps(height / 8.0f, height / 2.0f);
	}
}
