#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "dynamic.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define MAC 3  // jetbrains idea keys
// MAC Setup
#define LEFT_THIRD LCTL(LALT(KC_D)) /* Extract Method. CTRL+OPTION+COMMAND+D */
#define CENTER_THIRD LCTL(LALT(KC_F)) /* Extract Method. CTRL+OPTION+COMMAND+F */
#define RIGHT_THIRD LCTL(LALT(KC_G)) /* Extract Method. CTRL+OPTION+COMMAND+G */
// TO Consider
#define RUN LSFT(KC_F10)                    /* Run class or test. Shift+F10 */
#define EXPRESSION LALT(KC_F8)              /* Evaluete expression. Shift+F8 */
#define CONSTANT LCTL(LALT(KC_C))           /* Crete constant. CTRL+ALT+C */
#define OPT_IMPORTS LCTL(LALT(KC_O))        /* Optimize imports. CTRL+ALT+O */
#define REFORMAT LCTL(LALT(KC_L))           /* Reformat Code. CTRL+ALT+L */
#define COM_LINE LCTL(KC_SLSH)              /* Line Comment. CTRL+/ */
#define RENAME LSFT(KC_F6)                  /* Rename. CTRL+/ */

enum custom_keycodes
{
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  CAPSLOCK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,---------------------------------------------------------.
 * |CAPSLOCK|   1  |   2  |   3  |   4  |   5  | ESC  |           |  = +        |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |-------------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  Tab        |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |             |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |-------------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | OSL(MAC)    |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |             |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | LAlt |KC_LGUI| [   |  ]   |                                       | Left |  Up  | Down | Right| ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,---------------.
 *                                        | Del  | PrScr |       | Ins  |  BkSp  |
 *                                 ,------|------|-------|       |------+--------+------.
 *                                 |      |      | `~    |       | '"   |        |      |
 *                                 | Space| Enter|-------|       |------| Enter  |Space |
 *                                 |      |      | Home  |       | End  |        |      |
 *                                 `---------------------'       `----------------------'
 */
    // If it accepts an argument (i.e, is a function), it doesn't need KC_.
    // Otherwise, it needs KC_*
    [BASE] = LAYOUT_ergodox( // layer 0 : default
        // left hand
        KC_CAPS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_ESC,
        KC_DELT, KC_Q, KC_W, KC_E, KC_R, KC_T, TG(SYMB),
        KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, ALL_T(KC_NO),
        KC_LCTL, KC_LALT, KC_LGUI, KC_LBRC, KC_RBRC,
        KC_DELT, KC_PSCR,
        LT(SYMB, KC_GRV),
        KC_SPC, KC_ENT, KC_HOME,
        // right hand
        KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
        KC_TAB, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
        KC_H, KC_J, KC_K, KC_L, LT(MDIA, KC_SCLN), GUI_T(KC_QUOT),
        OSL(MAC), KC_N, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLSH), KC_RSFT,
        KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_FN1,
        KC_INS, KC_BSPC,
        KC_QUOT,
        KC_END, KC_ENT, KC_SPC),
    /* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |  ||  |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------|  &&  |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    // SYMBOLS
    [SYMB] = LAYOUT_ergodox(
        // left hand
        VRSN, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS,
        KC_TRNS, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
        KC_TRNS, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_GRV,
        KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        // right hand
        KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_TRNS, M(2), KC_7, KC_8, KC_9, KC_ASTR, KC_F12,
        M(1), KC_4, KC_5, KC_6, KC_PLUS, KC_TRNS,
        KC_TRNS, KC_AMPR, KC_1, KC_2, KC_3, KC_BSLS, KC_TRNS,
        KC_TRNS, KC_DOT, KC_0, KC_EQL, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS),
    /* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | MsUp |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |MsLeft|MsDown|MsRght|      |      | ---- |           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |VolUp | VolDn| Mute |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Lclk | Rclk |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    // MEDIA AND MOUSE
    [MDIA] = LAYOUT_ergodox(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        // right hand
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_BTN1, KC_BTN2),
    /* Keymap 3: JetBrains IDEA
 *
 * ,--------------------------------------------------.           ,-----------------------------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      | RENAME     |                 |  EXPRESSION    |      |  RUN |        |
 * |--------+------+------+------+------+-------------|           |------+------+-----------------+----------------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |                 |      |   OPT_IMPORTS   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+-----------------+------+------+------+--------|
 * |        |      | LEFT_THIRD     |CENTER_SCREEN| RIGHT_THIRD | ---- |           |------|      |                 |      |  REFORMAT    |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+-----------------+------+-------------+------+--------|
 * |        |      |      | CONSTANT     |      |      |      |           |      |  EXT_METHOD    |      |      |      | COM_LINE     |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |VolUp | VolDn| Mute |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Lclk | Rclk |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    // MAC
    [MAC] = LAYOUT_ergodox( // layer 3 : custom
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, LEFT_THIRD, CENTER_THIRD, RIGHT_THIRD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        // right hand
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC__VOLUP, KC__VOLDOWN, KC__MUTE, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_BTN1, KC_BTN2),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB) // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch (id)
  {
  case 0:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " RELEASE_URL " : " CURRENT_VERSION);
    }
    break;
  case 1:
    // ||
    if (record->event.pressed)
    {
      return MACRO(D(LSFT), T(7), T(7), U(LSFT), END);
    }
    break;
  case 2:
    // &&
    if (record->event.pressed)
    {
      return MACRO(D(LSFT), T(BSLS), T(BSLS), U(LSFT), END);
    }
    break;
  case 3:
    if (record->event.pressed)
    { // For resetting EEPROM
      eeconfig_init();
    }
    break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  // dynamically generate these.
  case EPRM:
    if (record->event.pressed)
    {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " RELEASE_URL " : " CURRENT_VERSION);
    }
    return false;
    break;
  case RGB_SLD:
    if (record->event.pressed)
    {
#ifdef RGBLIGHT_ENABLE
      rgblight_mode(1);
#endif
    }
    return false;
    break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void)
{
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void){

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state)
{
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer)
  {
  case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#else
#ifdef RGBLIGHT_ENABLE
    rgblight_init();
#endif
#endif
    break;
  case 1:
    ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
    break;
  case 2:
    ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
    break;
  case 3:
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
    break;
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
    break;
  case 5:
    ergodox_right_led_1_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
    break;
  case 6:
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
    break;
  case 7:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
    break;
  default:
    break;
  }

  return state;
};
