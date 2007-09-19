
#ifndef TIME_LINE_VIEW_H
#define TIME_LINE_VIEW_H

#include <View.h>

class TimeLine;

class TimeLineView : public BView
{
public:
	TimeLineView(BRect frame);

	virtual void GetPreferredSize(float *width, float *height);

	void Draw(BRect updateRect);

private:
	TimeLine *fTimeLine;
};

#endif // TIME_LINE_VIEW_H
