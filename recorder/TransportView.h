
#ifndef TRANSPORT_VIEW_H
#define TRANSPORT_VIEW_H

#include <interface/View.h>

class TransportControlGroup;

class TransportView : public BView
{
	public:
					TransportView(const char* name);

	private:
		TransportControlGroup*	fControls;
};

#endif // TRANSPORT_VIEW_H
