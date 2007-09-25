
#include <Alert.h>
#include <String.h>

#include "HyperionApp.h"

int
main(int argc, char* argv[])
{
	HyperionApp* app = new HyperionApp;
	if (app->InitCheck() == B_OK) {
		app->Run();
	} else {
		BString errMsg;
		errMsg << "The following error occurred loading Hyperion:\n";
		errMsg << strerror(app->InitCheck());
		BAlert* alert = new BAlert("Hyperion Error", errMsg.String(),
			"OK", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT);
		alert->Go();
	}
	delete app;

	return 0;
}
