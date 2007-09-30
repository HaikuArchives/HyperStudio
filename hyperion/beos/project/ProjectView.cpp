
#include <Alert.h>
#include <ScrollView.h>
#include <Slider.h>
#include <String.h>

#include "libcore/Project.h"
#include "libcore/Track.h"
#include "ProjectView.h"
#include "TimeLineView.h"
#include "TracksView.h"

#define DEFAULT_SCALE 25

ProjectView::ProjectView(BRect frame)
	: BView(frame, "ProjectView",
	        B_FOLLOW_ALL,
	        B_FULL_UPDATE_ON_RESIZE),
	  fPointer(0)
{
	// Create a new empty project
	fProject = new Project;

	// Set background color
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	BRect frame = Bounds();

	// Add timeline view
	frame.left = 128.0f;
	fTimeLineView = new TimeLineView(frame);
	fTimeLineView->ResizeToPreferred();
	AddChild(fTimeLineView);

	// Add tracks view
	frame.top = fTimeLineView->Bounds().Height();
	frame.right -= B_V_SCROLL_BAR_WIDTH;
	frame.bottom -= B_H_SCROLL_BAR_HEIGHT;
	fTracksView = new TracksView(frame);
	fTracksScrollView = new BScrollView("TracksScrollView", fTracksView,
		B_FOLLOW_ALL_SIDES, 0, true, true, B_NO_BORDER); 
	AddChild(fTracksScrollView);

	// Add scale slider
	frame.left = 0.0f;
	frame.top = Bounds().Height() - B_H_SCROLL_BAR_HEIGHT;
	frame.right = 127.0f;
	frame.bottom = Bounds().Height();
	fSlider = new BSlider(frame, "ScaleSlider", NULL,
		new BMessage(kScaleChanged), 10, 100, B_TRIANGLE_THUMB);
	fSlider->SetValue(DEFAULT_SCALE);
	fSlider->SetHashMarks(B_HASH_MARKS_TOP);
	fSlider->SetHashMarkCount(10);
	AddChild(fSlider);
}

ProjectView::~ProjectView()
{
	delete fTimeLineView;
	delete fTracksView;
	delete fProject;
}

uint32
ProjectView::Scale() const
{
	return fSlider->Value();
}

void
ProjectView::Rescale()
{
	fTimeLineView->Invalidate();
	fTracksView->Invalidate();
}

void
ProjectView::AddAudioTrack(uint32 channels)
{
	Track track;
	fTracksView->AddTrack(track);
}
