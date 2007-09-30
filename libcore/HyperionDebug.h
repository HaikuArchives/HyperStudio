/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef HYPERION_DEBUG_H
#define HYPERION_DEBUG_H

#define DEBUG 1
#include <Debug.h>

#ifdef DEBUG
#define DBGMSG(ARGS) _debugPrintf("%s - %s\n\t", __FILE__, __FUNCTION__); _debugPrintf ARGS
#else
#define DEBUGMSG(ARGS) (void)0
#endif

#endif // HYPERION_DEBUG_H
