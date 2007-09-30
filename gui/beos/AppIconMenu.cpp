
#include <AppFileInfo.h>
#include <Application.h>
#include <Bitmap.h>
#include <Roster.h>

#include "AppIconMenu.h"

AppIconMenu::AppIconMenu(BBitmap* icon, BMenu* menu)
	: BMenuItem(menu),
	  fBounds(),
	  fLabel(NULL)
{
	if (icon) {
		fBounds = icon->Bounds();
		fLabel = new BBitmap(fBounds, B_COLOR_8_BIT);
		fLabel->SetBits(icon->Bits(), icon->BitsLength(), 0, B_COLOR_8_BIT);
	}
}

AppIconMenu::AppIconMenu(BMenu* menu)
	: BMenuItem(menu),
	  fBounds(0.0f, 0.0f, 15.0f, 15.0f),
	  fLabel(NULL)
{
	app_info info;
	if (be_app->GetAppInfo(&info) == B_NO_ERROR) {
		BFile appFile(&(info.ref), O_RDONLY);
		BAppFileInfo appFileInfo(&appFile);

		fLabel = new BBitmap(fBounds, B_COLOR_8_BIT);

		if (appFileInfo.GetIcon(fLabel, B_MINI_ICON) != B_NO_ERROR) {
			delete fLabel;
			fLabel = NULL;
		}
	}
}

AppIconMenu::~AppIconMenu()
{
	delete fLabel;
	fLabel = NULL;
}

void AppIconMenu::GetContentSize(float* width, float* height)
{
	if (fLabel) {
		*width = fBounds.Width();
		*height = fBounds.Height();
	}
	else
		BMenuItem::GetContentSize(width, height);
}

void AppIconMenu::DrawContent()
{
	if (fLabel) {
		Menu()->SetDrawingMode(B_OP_OVER);

		float width, height;

		Menu()->GetPreferredSize(&width, &height);

		BRect destBounds = fBounds;
		destBounds.OffsetBy(8.0, ((height - fBounds.Height()) * 0.5) - 1);

		// Scaling the icon is left as an exercise for the reader :)
		Menu()->DrawBitmap(fLabel, fBounds, destBounds);
	}
	else
		BMenuItem::DrawContent();
}
