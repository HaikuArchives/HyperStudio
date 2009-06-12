
#include <interface/GroupLayout.h>
#include <interface/GroupLayoutBuilder.h>

#include "TransportView.h"
#include "TransportControlGroup.h"

TransportView::TransportView(const char* name)
	: BView(name, B_WILL_DRAW)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	// Create transport buttons
	fControls = new TransportControlGroup(BRect(0, 0, 100, 100), true, true, true);

	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(BGroupLayoutBuilder(B_HORIZONTAL)
		.Add(fControls)
	);
}
