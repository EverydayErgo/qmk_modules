#include QMK_KEYBOARD_H
#include "pointing_device.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,0,0);

static osa_forced_os_t osa_os = NOT_FORCED;

static bool osa_pds_vertical_scroll = false;
static bool osa_pds_horizontal_scroll = false;

__attribute__((weak)) void osa_scroll_update_user(void);

os_variant_t osa_detected_host_os(void) {
    switch(osa_os) {
        case NOT_FORCED:
            return detected_host_os();

        case FORCED_MACOS:
            return OS_MACOS;

        case FORCED_WINDOWS:
            return OS_WINDOWS;

        default:
            return OS_UNSURE;
    }
}

void force_macos(void) {
    osa_os = FORCED_MACOS;
}

void force_windows(void) {
    osa_os = FORCED_WINDOWS;
}

bool osa_matrix_is_on(uint8_t row, uint8_t col) {
    return matrix_get_row(row) & (1 << col);
}
bool osa_process_keycode(uint16_t keycode, bool pressed) {

    report_mouse_t mouse_report = pointing_device_get_report();
    switch(keycode) {
        case OA_VDL:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_LEFT));
                }else {
                    tap_code16(LGUI(LCTL(KC_LEFT)));
                }
            }  
            return false;

        case OA_VDR:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_RIGHT));
                }else {
                    tap_code16(LGUI(LCTL(KC_RIGHT)));
                }
            }
            return false;

        case OA_APQT:
            if(osa_detected_host_os()==OS_MACOS) {
                if(pressed) {
                    register_code(KC_LGUI);
                    register_code(KC_Q);
                }else {
                    unregister_code(KC_Q);
                    unregister_code(KC_LGUI);
                }
            }else {
                tap_code16(LALT(KC_F4));
            }
            return false;
        
        case OA_APPV:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_UP));
                }else {
                    tap_code16(LGUI(KC_TAB));
                }
            }
            return false;

        case OA_APPW:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_DOWN));
                }
            }
            return false;
        
        case OA_WBAK:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_LBRC));
                }else {
                    tap_code(KC_WBAK);
                }
            }
            return false;
        
        case OA_WFWD:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_RBRC));
                }else {
                    tap_code(KC_WFWD);
                }
            }
            return false;

        case OA_WREF:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_R));
                }else {
                    tap_code(KC_F5);
                }
            }
            return false;
        
        case OA_ZOIN:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_PPLS));
                }else {
                    tap_code16(LCTL(KC_PPLS));
                }
            }
            return false;

        case OA_ZOUT:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_PMNS));
                }else {
                    tap_code16(LCTL(KC_PMNS));
                }
            }
            return false;

        case OA_ZORT:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_0));
                }else {
                    tap_code16(LCTL(KC_0));
                }
            }
            return false;
        
        case MS_WHLU:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.v = -1;
                }else {
                    mouse_report.v = 1;
                }
            }
            pointing_device_set_report(mouse_report);
            return false;

        case MS_WHLD:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.v = 1;
                }else {
                    mouse_report.v = -1;
                }
            }
            pointing_device_set_report(mouse_report);
            return false;

        case MS_WHLL:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.h = 1;
                }else {
                    mouse_report.h = -1;
                }
            }
            pointing_device_set_report(mouse_report);
            return false;

        case MS_WHLR:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.h = -1;
                }else {
                    mouse_report.h = 1;
                } 
            }
            pointing_device_set_report(mouse_report);
            return false;
        
        case OA_PDSV:
            if(pressed) {
                osa_pds_vertical_scroll = true;
            }else {
                osa_pds_vertical_scroll = false;
            }
            return false;

        case OA_PDSH:
            if(pressed) {
                osa_pds_horizontal_scroll = true;
            }else {
                osa_pds_horizontal_scroll = false;
            }
            return false;

        case OA_LCTL:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    register_code(KC_LGUI);
                }else {
                    register_code(KC_LCTL);
                }
            }else {       
                if(osa_detected_host_os()==OS_MACOS) {
                    unregister_code(KC_LGUI);
                }else {
                    unregister_code(KC_LCTL);
                }
            }
            return false;

        case OA_LGUI:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    register_code(KC_LCTL);
                }else {
                    register_code(KC_LGUI);
                } 
            }else {
                if(osa_detected_host_os()==OS_MACOS) {
                    unregister_code(KC_LCTL);
                }else {
                    unregister_code(KC_LGUI);
                }
            }
            return false;

        case OA_RCTL:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    register_code(KC_LGUI);
                }else {
                    register_code(KC_RCTL);
                }
            }else {       
                if(osa_detected_host_os()==OS_MACOS) {
                    unregister_code(KC_LGUI);
                }else {
                    unregister_code(KC_RCTL);
                }
            }
            return false;

        case OA_RGUI:
            if(pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    register_code(KC_LCTL);
                }else {
                    register_code(KC_RGUI);
                } 
            }else {
                if(osa_detected_host_os()==OS_MACOS) {
                    unregister_code(KC_LCTL);
                }else {
                    unregister_code(KC_RGUI);
                }
            }
            return false;
    }
    return true;
}

bool process_record_osa_keys(uint16_t keycode, keyrecord_t *record) {   
    return osa_process_keycode(keycode, record->event.pressed);
}

void housekeeping_task_osa_keys(void) {
    osa_scroll_update_user();
}

report_mouse_t pointing_device_task_osa_keys(report_mouse_t mouse_report) {
    static float scroll_accumulated_v = 0;
    static float scroll_accumulated_h = 0;

#if defined(PDS_VERTICAL_SCROLL_ROW) && defined(PDS_VERTICAL_SCROLL_COLUMN)        
    if((osa_matrix_is_on(PDS_VERTICAL_SCROLL_ROW, PDS_VERTICAL_SCROLL_COLUMN)) || osa_pds_vertical_scroll) {
#else
    if(osa_pds_vertical_scroll) {
#endif
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;
        if(osa_detected_host_os()==OS_MACOS) 
            mouse_report.v = (int8_t)scroll_accumulated_v;
        else
            mouse_report.v = -(int8_t)scroll_accumulated_v;

        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
        mouse_report.x = 0;
        mouse_report.y = 0;        
    }

#if defined(PDS_HORIZONTAL_SCROLL_ROW) && defined(PDS_HORIZONTAL_SCROLL_COLUMN)    
    if((osa_matrix_is_on(PDS_HORIZONTAL_SCROLL_ROW, PDS_HORIZONTAL_SCROLL_COLUMN)) || osa_pds_horizontal_scroll) {       
#else
    if(osa_pds_horizontal_scroll) {       
#endif
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        if(osa_detected_host_os()==OS_MACOS)
            mouse_report.h = -(int8_t)scroll_accumulated_h;
        else
            mouse_report.h = (int8_t)scroll_accumulated_h;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        mouse_report.x = 0;
        mouse_report.y = 0;                                                   
    } 
    return mouse_report;
} 

bool process_detected_host_os_osa_keys(os_variant_t os) {
    if(os==OS_MACOS) {
        keymap_config.swap_lctl_lgui = true;
        keymap_config.swap_rctl_rgui = true;
        eeconfig_update_keymap(&keymap_config);
        clear_keyboard();
    }else {
        keymap_config.swap_lctl_lgui = false;
        keymap_config.swap_rctl_rgui = false;
        eeconfig_update_keymap(&keymap_config);
        clear_keyboard();
    }
    return true;
}

void osa_tap_code(uint16_t keycode) {
    osa_process_keycode(keycode, true);
}

void osa_activate_vertical_scroll(void) {
    osa_pds_vertical_scroll = true;
}

void osa_deactivate_vertical_scroll(void) {
    osa_pds_vertical_scroll = false;
}

void osa_activate_horizontal_scroll(void) {
    osa_pds_horizontal_scroll = true;
}

void osa_deactivate_horizontal_scroll(void) {
    osa_pds_horizontal_scroll = false;
}