
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

	// Fill with background color
	rgb_color bg_color = (rgb_color){ 35, 70, 100 };
	SetLowColor(bg_color);
	FillRect(r, B_SOLID_LOW);

	// Get scale from project settings
	ProjectView *parent = dynamic_cast<ProjectView*>(Parent());
	uint32 scale = parent->Scale();

	int32 start = (int32(updateRect.left / scale) ) * scale;
	int32 end = (int32(updateRect.right / scale) + 1) * scale;
	int32 nb = (end - start) / scale * 2 + 3;
	int32 height = Bounds().IntegerHeight();

	// Draw if the rectangle is large enough
	if (nb <= 0)
		return;

	// Change font size and get font height
	SetFontSize(8.0f);
	font_height fh;
	GetFontHeight(&fh);

	// Colors
	rgb_color white = (rgb_color){ 255, 255, 255 };
	rgb_color long_color = tint_color(white, B_DARKEN_2_TINT);
	rgb_color small_color = tint_color(white, B_DARKEN_3_TINT);

	// Set labels color
	SetHighColor(white);

	// Draw lines and labels
	BeginLineArray(nb);
	for (int32 i = start; i <= end; i += scale)
	{
		// Draw lines
		AddLine(BPoint(i, 0), BPoint(i, height), long_color);
		AddLine(BPoint(i + scale / 2, height), BPoint(i + scale / 2, height - 5), small_color);

		// Draw labels
		BString str;
		int32 val = i / scale;
		uint32 min = uint32(val / 60);
		uint32 sec = uint32(val % 60);
		if (!(val % 5))
		{
			str << min << ":";
			if (min > 0 && sec < 10)
				str << "0" << sec;
			else
				str << sec;
			MovePenTo(i - StringWidth(str.String()) / 2.0f, fh.ascent);
			DrawString(str.String());
		}
	}
	EndLineArray();
}
