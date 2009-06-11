/*
 * Copyright 2007-2009 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the GPL v3 License.
 */
#ifndef HYPERSTUDIO_DEBUG_H
#define HYPERSTUDIO_DEBUG_H

#define DEBUG 1
#include <Debug.h>

#ifdef DEBUG
#	define DBGMSG(ARGS) _debugPrintf("%s - %s\n\t", __FILE__, __FUNCTION__); _debugPrintf ARGS
#else
#	define DEBUGMSG(ARGS) (void)0
#endif

#endif // HYPERSTUDIO_DEBUG_H
