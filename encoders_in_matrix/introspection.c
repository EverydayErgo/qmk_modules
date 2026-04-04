#include QMK_KEYBOARD_H

extern matrix_row_t raw_matrix[MATRIX_ROWS];

static int8_t eim_transitions [] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};    
static int8_t eim_state [EIM_LAST_ENCODER] = {0};
static uint8_t eim_count [EIM_LAST_ENCODER] = {0};


bool eim_matrix_is_on(uint8_t row, uint8_t col) {
    return (raw_matrix[row] & ((matrix_row_t)1 << col));
}

void housekeeping_task_encoders_in_matrix(void) {
    for(enc_names_t encoder=0, pad_ab=0;encoder<EIM_LAST_ENCODER;encoder++) {
            pad_ab |= eim_matrix_is_on(eim_encoders[encoder][EIM_PADA_R], eim_encoders[encoder][EIM_PADA_C]);
            pad_ab <<= 1;
            pad_ab |= eim_matrix_is_on(eim_encoders[encoder][EIM_PADB_R], eim_encoders[encoder][EIM_PADB_C]);

        eim_count[encoder] <<= 2;
        eim_count[encoder] |= pad_ab;
        eim_count[encoder] &= 0xF;
        eim_state[encoder] += eim_transitions[eim_count[encoder]];
        pad_ab = 0;
        if(eim_state[encoder]<=-eim_encoders[encoder][EIM_RES]) {
            encoders_in_matrix_update_user(encoder, eim_encoders[encoder][EIM_FLIP]);
            eim_state[encoder]=0;
        }else if(eim_state[encoder]>=eim_encoders[encoder][EIM_RES]) {
           encoders_in_matrix_update_user(encoder, !eim_encoders[encoder][EIM_FLIP]);
           eim_state[encoder]=0; 
        }
    }
}