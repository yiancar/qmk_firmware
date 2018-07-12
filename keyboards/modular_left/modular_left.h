#ifndef MODULAR_LEFT_H
#define MODULAR_LEFT_H

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
	K00, K01, K02, K03, K04, K05, K45,        K07, K08, K09, K0A, K0B, K0C, K0D, K06,   K0E, K0F, K0G,   K0H, K0J, K0K, K0L, \
	K10, K11, K12, K13, K14, K15,        K16, K17, K18, K19, K1A, K1B, K1C, K1D,        K1E, K1F, K1G,   K1H, K1J, K1K, K1L, \
	K20, K21, K22, K23, K24, K25,        K26, K27, K28, K29, K2A, K2B, K2C, K2D,                         K2H, K2J, K2K, K2L, \
	K30, K44, K31, K32, K33, K34, K35,   K36, K37, K38, K39, K3A,      K3C, K3D,             K3F,        K3H, K3J, K3K,      \
	K40, K41, K42, K43,                  K46, K47, K48, K49, K4A, K4B,                  K4E, K4F, K4G,   K4H, K4J, K4K, K4L  \
) \
{ \
    { K00, K01, K02, K03, K04, K05,   K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0E, K0F, K0G,   K0H, K0J, K0K, K0L }, \
    { K10, K11, K12, K13, K14, K15,   K16, K17, K18, K19, K1A, K1B, K1C, K1D,   K1E, K1F, K1G,   K1H, K1J, K1K, K1L }, \
    { K20, K21, K22, K23, K24, K25,   K26, K27, K28, K29, K2A, K2B, K2C, K2D,   XXX, XXX, XXX,   K2H, K2J, K2K, K2L }, \
    { K30, K31, K32, K33, K34, K35,   K36, K37, K38, K39, K3A, XXX, K3C, K3D,   XXX, K3F, XXX,   K3H, K3J, K3K, XXX }, \
    { K40, K41, K42, K43, K44, K45,   K46, K47, K48, K49, K4A, K4B, XXX, XXX,   K4E, K4F, K4G,   K4H, K4J, K4K, K4L }  \
}

#endif
