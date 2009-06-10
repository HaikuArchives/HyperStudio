
#include <Slider.h>

#include "ScaleSlider.h"

SliderView::SliderView()
	: BView("SliderView", B_WILL_DRAW)
{
	fSlider = new BSlider("ScaleSlider", NULL,
		new BMessage(kScaleChanged), 10, 100, B_TRIANGLE_THUMB);
	fSlider->SetValue(DEFAULT_SCALE);
	fSlider->SetHashMarks(B_HASH_MARKS_TOP);
	fSlider->SetHashMarkCount(10);
	AddChild(fSlider);
}
