#include QMK_KEYBOARD_H

extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];

static int8_t eim_transitions [] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};    
static int8_t eim_state [EIM_LAST_ENCODER] = {0};
static uint8_t eim_count [EIM_LAST_ENCODER] = {0};


bool eim_matrix_is_on(uint8_t row, uint8_t col) {
    return (raw_matrix[row] & ((matrix_row_t)1 << col));
}

void eim_set_matrix_on(uint8_t row, uint8_t col) {
    matrix[row] |= ((matrix_row_t)1 << col);
}

void eim_set_matrix_off(uint8_t row, uint8_t col) {
    matrix[row] &= ~((matrix_row_t)1 << col);
}

void matrix_scan_kb(void) {
     for(enc_names_t encoder=0, pad_ab=0;encoder<EIM_LAST_ENCODER;encoder++) {
            pad_ab |= eim_matrix_is_on(eim_encoders[encoder][EIM_PADA_R], eim_encoders[encoder][EIM_PADA_C]);
            pad_ab <<= 1;
            pad_ab |= eim_matrix_is_on(eim_encoders[encoder][EIM_PADB_R], eim_encoders[encoder][EIM_PADB_C]);

        eim_count[encoder] <<= 2;
        eim_count[encoder] |= pad_ab;
        eim_count[encoder] &= 0xF;
        eim_state[encoder] += eim_transitions[eim_count[encoder]];
        pad_ab = 0;
        eim_set_matrix_off(eim_encoders[encoder][EIM_PADA_R], eim_encoders[encoder][EIM_PADA_C]);
        eim_set_matrix_off(eim_encoders[encoder][EIM_PADB_R], eim_encoders[encoder][EIM_PADB_C]);
        if(eim_state[encoder]<=-eim_encoders[encoder][EIM_RES]) {
#ifndef EIM_CALLBACK
            eim_set_matrix_on(eim_encoders[encoder][EIM_PADA_R], eim_encoders[encoder][EIM_PADA_C]);
#else
            encoders_in_matrix_update_user(encoder, eim_encoders[encoder][EIM_FLIP]);
#endif            
            eim_state[encoder]=0;
        }else if(eim_state[encoder]>=eim_encoders[encoder][EIM_RES]) {
#ifndef EIM_CALLBACK
            eim_set_matrix_on(eim_encoders[encoder][EIM_PADB_R], eim_encoders[encoder][EIM_PADB_C]);
#else
           encoders_in_matrix_update_user(encoder, !eim_encoders[encoder][EIM_FLIP]);
#endif
           eim_state[encoder]=0; 
        }
    }
    matrix_scan_user();
}
