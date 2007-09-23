
#ifndef HYPERION_H
#define HYPERION_H

#define HYPERION_SIGNATURE "application/x-vnd.Hyperion"

#define DEBUG 1
#include <Debug.h>

#ifdef DEBUG
#define DBGMSG(ARGS) _debugPrintf("%s - %s\n\t", __FILE__, __FUNCTION__); _debugPrintf ARGS
#else
#define DEBUGMSG(ARGS) (void)0
#endif

#endif // HYPERION_H
