#include QMK_KEYBOARD_H
#include "pointing_device.h"


ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1,0,0);

static osa_forced_os_t osa_os = NOT_FORCED;

static bool osa_pds_vertical_scroll = false;
static bool osa_pds_horizontal_scroll = false;

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

bool process_record_macos(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        if((keycode>=QK_MOD_TAP && keycode<=QK_MOD_TAP_MAX) && (!record->tap.count)) {
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_LCTL)) {
                add_mods(MOD_BIT(KC_LGUI));
                return false;
            }
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_LGUI)) {
                add_mods(MOD_BIT(KC_LCTL));
                return false;
            }
             if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_RCTL)) {
                add_mods(MOD_BIT(KC_RGUI));
                return false;
            }
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_RGUI)) {
                add_mods(MOD_BIT(KC_RCTL));
                return false;
            }
        }else if(keycode>=QK_ONE_SHOT_MOD && keycode<=QK_ONE_SHOT_MOD_MAX) {
            if(QK_ONE_SHOT_MOD_GET_MODS(keycode) & MOD_LCTL) {
                add_oneshot_mods(MOD_BIT(KC_LGUI));
                return false;
            }
            if(QK_ONE_SHOT_MOD_GET_MODS(keycode) & MOD_LGUI) {
                add_oneshot_mods(MOD_BIT(KC_LCTL));
                return false;
            }
            if(QK_ONE_SHOT_MOD_GET_MODS(keycode) & MOD_BIT(KC_RCTL)) {
                add_oneshot_mods(MOD_BIT(KC_RGUI));
                return false;
            }
            if(QK_ONE_SHOT_MOD_GET_MODS(keycode) & MOD_BIT(KC_RGUI)) {
                add_oneshot_mods(MOD_BIT(KC_RCTL));
                return false;
            }
        }else if(keycode==KC_LCTL) {
            register_code(KC_LGUI);
            return false;
        }else if(keycode==KC_LGUI) {
            register_code(KC_LCTL);
            return false;
        }
    }else { 
        //RELEASE
        if((keycode>=QK_MOD_TAP && keycode<=QK_MOD_TAP_MAX) && (!record->tap.count)) {
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_LCTL)) {
                del_mods(MOD_BIT(KC_LGUI));
                return true;
            }
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_LGUI)) {
                del_mods(MOD_BIT(KC_LCTL));
                return true;
            }
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_RCTL)) {
                del_mods(MOD_BIT(KC_RGUI));
                return true;
            }
            if(QK_MODS_GET_MODS(keycode) & MOD_BIT(KC_RGUI)) {
                del_mods(MOD_BIT(KC_RCTL));
                return true;
            }
        }else if(keycode==KC_LCTL) {
            unregister_code(KC_LGUI);
            return false;
        }else if(keycode==KC_LGUI) {
            unregister_code(KC_LCTL);
            return false;
        }
    }
    return true;
}

bool process_record_osa_keys(uint16_t keycode, keyrecord_t *record) {   
    report_mouse_t mouse_report = pointing_device_get_report();
    switch(keycode) {
        case OA_VDL:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_LEFT));
                }else {
                    tap_code16(LGUI(LCTL(KC_LEFT)));
                }
            }  
            return false;

        case OA_VDR:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_RIGHT));
                }else {
                    tap_code16(LGUI(LCTL(KC_RIGHT)));
                }
            }
            return false;

        case OA_APQT:
            if(osa_detected_host_os()==OS_MACOS) {
                if(record->event.pressed) {
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
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_UP));
                }else {
                    tap_code16(LGUI(KC_TAB));
                }
            }
            return false;

        case OA_APPW:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LCTL(KC_DOWN));
                }
            }
            return false;

        case OA_WBAK:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_LBRC));
                }else {
                    tap_code(KC_WBAK);
                }
            }
            return false;

        case OA_WFWD:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_RBRC));
                }else {
                    tap_code(KC_WFWD);
                }
            }
            return false;

        case OA_WREF:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_R));
                }else {
                    tap_code(KC_F5);
                }
            }
            return false;
        
        case OA_ZOIN:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_PPLS));
                }else {
                    tap_code16(LCTL(KC_PPLS));
                }
            }
            return false;

        case OA_ZOUT:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_PMNS));
                }else {
                    tap_code16(LCTL(KC_PMNS));
                }
            }
            return false;

        case OA_ZORT:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    tap_code16(LGUI(KC_0));
                }else {
                    tap_code16(LCTL(KC_0));
                }
            }
            return false;
        
        case OA_WHLU:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.v = -1;
                }else {
                    mouse_report.v = 1;
                }
            }
            pointing_device_set_report(mouse_report);
            return false;

        case OA_WHLD:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.v = 1;
                }else {
                    mouse_report.v = -1;
                }
            }
            pointing_device_set_report(mouse_report);
            return false;

        case OA_WHLL:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.h = 1;
                }else {
                    mouse_report.h = -1;
                }
            }
            pointing_device_set_report(mouse_report);
            return false;

        case OA_WHLR:
            if(record->event.pressed) {
                if(osa_detected_host_os()==OS_MACOS) {
                    mouse_report.h = -1;
                }else {
                    mouse_report.h = 1;
                } 
            }
            pointing_device_set_report(mouse_report);
            return false;
        
        case OA_PDSV:
            if(record->event.pressed) {
                osa_pds_vertical_scroll = true;
            }else {
                osa_pds_vertical_scroll = false;
            }
            return false;

        case OA_PDSH:
            if(record->event.pressed) {
                osa_pds_horizontal_scroll = true;
            }else {
                osa_pds_horizontal_scroll = false;
            }
            return false;
    }
    if(osa_detected_host_os()==OS_MACOS)
        return process_record_macos(keycode, record);

    return true;
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