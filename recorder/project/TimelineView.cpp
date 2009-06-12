
#include <String.h>

#include <stdio.h>

#include "TimelineView.h"

TimelineView::TimelineView(const char* name)
	: BView(name, B_WILL_DRAW)
{
	SetLowColor(180, 180, 180, 255);
}


void TimelineView::AttachedToWindow()
{
}


void TimelineView::DetachedFromWindow()
{
}


void TimelineView::MessageReceived(BMessage* message)
{
}


void TimelineView::MouseDown(BPoint where)
{
}


void TimelineView::MouseUp(BPoint where)
{
}
