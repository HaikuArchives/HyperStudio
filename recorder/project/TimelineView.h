
#ifndef TIMELINE_VIEW_H
#define TIMELINE_VIEW_H

#include <View.h>

class TimeLine;

class TimelineView : public BView
{
public:
				TimelineView(const char* name);

	// BView interface
	virtual void		AttachedToWindow();
	virtual void		DetachedFromWindow();

	virtual void		MessageReceived(BMessage* message);

	virtual void		MouseDown(BPoint where);
	virtual void		MouseUp(BPoint where);

private:
	TimeLine *fTimeLine;
};

#endif // TIMELINE_VIEW_H
