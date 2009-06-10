
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

	BRect rect = Bounds();

	// Add timeline view
	rect.left = 128.0f;
	fTimeLineView = new TimeLineView(rect);
	fTimeLineView->ResizeToPreferred();
	AddChild(fTimeLineView);

	// Add tracks view
	rect.top = fTimeLineView->Bounds().Height();
	rect.right -= B_V_SCROLL_BAR_WIDTH;
	rect.bottom -= B_H_SCROLL_BAR_HEIGHT;
	fTracksView = new TracksView(rect);
	fTracksScrollView = new BScrollView("TracksScrollView", fTracksView,
		B_FOLLOW_ALL_SIDES, 0, true, true, B_NO_BORDER); 
	AddChild(fTracksScrollView);

	// Add scale slider
	rect.left = 0.0f;
	rect.top = Bounds().Height() - B_H_SCROLL_BAR_HEIGHT;
	rect.right = 127.0f;
	rect.bottom = Bounds().Height();
	fSlider = new BSlider(rect, "ScaleSlider", NULL,
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
