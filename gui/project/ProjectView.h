
#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <View.h>

class BScrollView;
class BSlider;
class Project;
class TimeLineView;
class TracksView;

const uint32 kScaleChanged = 'slch';

class ProjectView : public BView
{
public:
	ProjectView(BRect frame);
	virtual ~ProjectView();

	Project* CurrentProject() const { return fProject; }

	uint32 Scale() const;
	bigtime_t Pointer() const { return fPointer; }

	void Rescale();

private:
	Project* fProject;
	bigtime_t fPointer;
	TimeLineView* fTimeLineView;
	TracksView* fTracksView;
	BScrollView* fTracksScrollView;
	BSlider* fSlider;
};

#endif // PROJECT_VIEW_H
