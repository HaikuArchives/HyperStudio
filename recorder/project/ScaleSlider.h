
#ifndef SLIDER_VIEW_H
#define SLIDER_VIEW_H

#include <View.h>

class BSlider;

class SliderView : public BView
{
public:
	SliderView();

private:
	BSlider*	fSlider;
};

#endif // SLIDER_VIEW_H
