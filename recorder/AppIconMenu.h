/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef APP_ICON_MENU_H
#define APP_ICON_MENU_H

#include <MenuItem.h>

class BBitmap;

class AppIconMenu : public BMenuItem {
	public:
		AppIconMenu(BBitmap* icon, BMenu* menu);
		AppIconMenu(BMenu* menu);
		virtual ~AppIconMenu();

	protected:
		virtual void GetContentSize(float* width, float* height);
		virtual void DrawContent();

	private:
		// Disabled copy constructor
		AppIconMenu(const AppIconMenu& iconMenu);

		BRect fBounds;
		BBitmap* fLabel;
};

#endif // APP_ICON_MENU_H
