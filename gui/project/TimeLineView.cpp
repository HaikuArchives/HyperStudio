
#include <String.h>

#include <stdio.h>

#include "ProjectView.h"
#include "TimeLineView.h"

TimeLineView::TimeLineView(BRect frame)
	: BView(frame, "TimeLineView",
	        B_FOLLOW_TOP | B_FOLLOW_LEFT_RIGHT,
	        B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE)
{
	// This avoids flickering while resizing its parent view
	SetViewColor(B_TRANSPARENT_COLOR);

	// Get stuff
	//fTimeLine = project->GetTimeLine();
}

void
TimeLineView::GetPreferredSize(float *width, float *height)
{
	if (width)
		*width = Bounds().Width()*4;
	if (height)
		*height = 20.0f;
}

void
TimeLineView::Draw(BRect updateRect)
{
	BRect r = Bounds();
	rgb_color bg_color = (rgb_color){ 35, 70, 100 };
	//rgb_color light_color = tint_color(bg_color, B_LIGHTEN_1_TINT);

	// Fill with background color
	SetLowColor(bg_color);
	FillRect(r, B_SOLID_LOW);

	rgb_color white = (rgb_color){ 255, 255, 255 };
	rgb_color small_color = tint_color(white, B_DARKEN_1_TINT);

	// Get scale from project settings
	ProjectView *parent = dynamic_cast<ProjectView*>(Parent());
	uint32 scale = parent->Scale();

	int32 start = (int32(updateRect.left / scale) ) * scale;
	int32 end = (int32(updateRect.right / scale) + 1) * scale;
	int32 nb = (end - start) / scale * 2 + 3;

	// Draw if the rectangle is large enough
	if (nb <= 0)
		return;

	// Draw lines
	BeginLineArray(nb);
	for (int32 i = start; i <= end; i += scale)
	{
		AddLine(BPoint(i, 0), BPoint(i, 10), white);
		AddLine(BPoint(i + scale / 2, 0), BPoint(i + scale / 2, 5), small_color);
	}
	EndLineArray();

	// Draw labels
	SetHighColor(white);
	for (int32 i = start; i <= end; i += scale)
	{
		BString str;
		int32 sec = i / scale;
		if (!(sec % 5))
		{
			str << uint32(sec / 60);
			str << ":";
			str << uint32(sec % 60);
			MovePenTo(i - StringWidth(str.String())/2, 20);
			DrawString(str.String());
		}
	}

// FIXME: don't know what is this, i took it from VBL
rgb_color black = (rgb_color){255,0,0};
	BeginLineArray(4);
	AddLine(BPoint(updateRect.left, 30), BPoint(updateRect.right, 30), black);
	AddLine(BPoint(updateRect.left, 60), BPoint(updateRect.right, 60), black);
	AddLine(BPoint(updateRect.left, 80), BPoint(updateRect.right, 80), black);
	AddLine(BPoint(updateRect.left, 110), BPoint(updateRect.right, 110), black);
	EndLineArray();
}
