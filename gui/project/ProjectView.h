
#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <View.h>

class TimeLineView;
class TracksView;

class ProjectView : public BView
{
public:
	ProjectView(BRect frame);
	virtual ~ProjectView();

	uint32 Scale() const { return fScale; }
	bigtime_t Pointer() const { return fPointer; }

private:
	void InitChilds();

	uint32 fScale;
	bigtime_t fPointer;
	TimeLineView *fTimeLineView;
	TracksView *fTracksView;
};

#endif // PROJECT_VIEW_H
