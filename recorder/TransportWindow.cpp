
#include <interface/GroupLayout.h>
#include <interface/GroupLayoutBuilder.h>

#include "TransportWindow.h"
#include "TransportView.h"

TransportWindow::TransportWindow()
	: BWindow(BRect(50, 50, 1, 1), "Transport", B_FLOATING_WINDOW,
		B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE | B_ASYNCHRONOUS_CONTROLS |
		B_AUTO_UPDATE_SIZE_LIMITS | B_CLOSE_ON_ESCAPE)
{
	TransportView* view = new TransportView("transport");

	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(BGroupLayoutBuilder(B_HORIZONTAL)
		.Add(view)
	);
}
