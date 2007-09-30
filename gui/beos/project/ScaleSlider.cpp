
#include <Slider.h>

#include "ScaleSlider.h"

SliderView::SliderView(BRect frame)
	: BView(frame, "SliderView")
{
	fSlider = new BSlider(frame, "ScaleSlider", NULL,
		new BMessage(kScaleChanged), 10, 100, B_TRIANGLE_THUMB);
	fSlider->SetValue(DEFAULT_SCALE);
	fSlider->SetHashMarks(B_HASH_MARKS_TOP);
	fSlider->SetHashMarkCount(10);
	AddChild(fSlider);
}
