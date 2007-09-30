/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef ABOUT_WINDOW_H
#define ABOUT_WINDOW_H

class AboutWindow {
	public:
		AboutWindow(char* appName, int32 firstCopyrightYear,
		            const char** authors, char* extraInfo = NULL);
		virtual ~AboutWindow();

		void Show();

	private:
		BString* fAppName;
		BString* fText;
};

#endif // ABOUT_WINDOW_H
