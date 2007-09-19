
#ifndef HYPERION_APP_H
#define HYPERION_APP_H

#include <Application.h>

#define HYPERION_SIGNATURE "application/x-vnd.Hyperion"

class BWindow;

class HyperionApp : public BApplication
{
public:
	HyperionApp();
	virtual ~HyperionApp();

	BWindow* NewWindow();

	virtual void RefsReceived(BMessage* msg);
	virtual void ArgvReceived(int32 argc, char** argv);
	virtual void AboutRequested();

private:
	BWindow* fFirstWindow;
};

#endif // HYPERION_APP_H
