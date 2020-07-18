#include QMK_KEYBOARD_H

#include "config.h"
#include "dynamic.h"

#define DELAY 10

#define FIRMWARE QMK_KEYBOARD "/" QMK_KEYMAP " > firmware:" FIRMWARE_VERSION "@ build:"  RELEASE_URL "/tag/" CURRENT_VERSION

// #include "firmware.h"
// SEND_STRING(FIRMWARE SS_DELAY(50) SS_TAP(X_ENTER));