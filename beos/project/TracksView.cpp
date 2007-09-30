
#include <List.h>
#include <Message.h>
#include <ScrollBar.h>

#include "libcore/Track.h"
#include "ProjectView.h"
#include "TracksView.h"
#include "TrackView.h"

TracksView::TracksView(BRect frame)
	: BView(frame, "TracksView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS)
{
	// Initialize memebers
	fViews = new BList;
	fLastSlot = BRect(0.0f, 0.0f, Bounds().Width()*4, 128.0f);
}

TracksView::~TracksView()
{
	TrackView* item;
	for (int32 i = 0; (item = (TrackView*)fViews->ItemAt(i)); i++)
		delete item;
	delete fViews;
}

void
TracksView::Draw(BRect updateRect)
{
	rgb_color bg_color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                                B_DARKEN_2_TINT);
	rgb_color line_color = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
	                                  B_DARKEN_3_TINT);

	// Update background
	SetLowColor(bg_color);
	FillRect(Bounds(), B_SOLID_LOW);

	// Get scale from project settings
	ProjectView *parent = dynamic_cast<ProjectView*>(Parent()->Parent());
	uint32 scale = parent->Scale();

	// Get maximum size
	float maxWidth, maxHeight;
	GetMaxSize(&maxWidth, &maxHeight);

	// Calculate start and end
	int32 start = (int32(Frame().left / scale) ) * scale;
	int32 end = (int32(maxWidth / scale) + 1) * scale;
	int32 nb = (end - start) / scale * 2 + 3;

	// Draw if the rectangle is large enough
	if (nb <= 0)
		return;

	// Draw lines
	BeginLineArray(nb);
	for (int32 i = start; i <= end; i += scale)
	{
		AddLine(BPoint(i, 0),
		        BPoint(i, maxHeight), line_color);
		AddLine(BPoint(i + scale / 2, 0),
		        BPoint(i + scale / 2, maxHeight), line_color);
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
TracksView::AddTrack(Track &track)
{
	// Add track view
	TrackView *view = new TrackView(fLastSlot, track);
	fViews->AddItem(view);
	AddChild(view);

	// Update last slot position
	fLastSlot.top = fLastSlot.bottom + fViews->CountItems();
	fLastSlot.bottom += 128.0f + fViews->CountItems();
}

void
TracksView::GetMaxSize(float* width, float* height)
{
	if (width)
		*width = Bounds().Width() * 2.0f;
	if (height)
		*height = Bounds().Height() * 2.0f;
}

void
TracksView::FixupScrollBars()
{
	BScrollBar* sb;

	// Get size
	float width = Bounds().Width();
	float height = Bounds().Height();

	// Get max size
	float maxWidth, maxHeight;
	GetMaxSize(&maxWidth, &maxHeight);

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
