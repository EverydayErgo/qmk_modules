#include QMK_KEYBOARD_H

#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

typedef enum {
    NOT_FORCED,
    FORCED_MACOS,
    FORCED_WINDOWS
}osa_forced_os_t;

void force_macos(void);
void force_windows(void);
void osa_tap_code(uint16_t keycode);
void osa_activate_vertical_scroll(void);
void osa_deactivate_vertical_scroll(void);
void osa_activate_horizontal_scroll(void);
void osa_deactivate_horizontal_scroll(void);
void osa_scroll_update_user(void);
