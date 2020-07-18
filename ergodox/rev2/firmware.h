#include QMK_KEYBOARD_H

#include "config.h"
#include "dynamic.h"

#define DELAY 10

#define FIRMWARE "keymap: " QMK_KEYBOARD "/" QMK_KEYMAP " > firmware: " FIRMWARE_VERSION " @ release: "  RELEASE_URL "/releases/tag/" CURRENT_VERSION

// #include "firmware.h"
// SEND_STRING(FIRMWARE SS_DELAY(50) SS_TAP(X_ENTER));