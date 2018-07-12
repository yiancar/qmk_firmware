#ifndef TEST_R_H
#define TEST_R_H

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
	K00, K01, K02, \
	K10, K11, K12, \
	               \
	     K31,      \
	K40, K41, K42  \
) \
{ \
    { K00, K01, K02 }, \
    { K10, K11, K12 }, \
    { XXX, XXX, XXX }, \
    { XXX, K31, XXX }, \
    { K40, K41, K42 }  \
}

#endif
