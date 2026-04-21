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
     for(uint8_t encoder=0, pad_ab=0;encoder<EIM_LAST_ENCODER;encoder++) {
        pad_ab |= eim_matrix_is_on(eim_encoders[encoder].pad_a.row, eim_encoders[encoder].pad_a.col);
        pad_ab <<= 1;
        pad_ab |= eim_matrix_is_on(eim_encoders[encoder].pad_b.row, eim_encoders[encoder].pad_b.col);
       
        eim_count[encoder] <<= 2;
        eim_count[encoder] |= pad_ab;
        eim_count[encoder] &= 0xF;
        eim_state[encoder] += eim_transitions[eim_count[encoder]];

        pad_ab = 0;

        eim_set_matrix_off(eim_encoders[encoder].pad_a.row, eim_encoders[encoder].pad_a.col);
        eim_set_matrix_off(eim_encoders[encoder].pad_b.row, eim_encoders[encoder].pad_b.col);
        if(eim_state[encoder]<=-eim_encoders[encoder].resolution) {
#ifndef EIM_CALLBACK
            if(eim_encoders[encoder].flipped)
                eim_set_matrix_on(eim_encoders[encoder].pad_b.row, eim_encoders[encoder].pad_b.col);
            else
                eim_set_matrix_on(eim_encoders[encoder].pad_a.row, eim_encoders[encoder].pad_a.col);
#else
            encoders_in_matrix_update_user(encoder, eim_encoders[encoder].flipped);
#endif            
            eim_state[encoder]=0;
        }else if(eim_state[encoder]>=eim_encoders[encoder].resolution) {
#ifndef EIM_CALLBACK
            if(eim_encoders[encoder].flipped)
                eim_set_matrix_on(eim_encoders[encoder].pad_a.row, eim_encoders[encoder].pad_a.col);
            else
                eim_set_matrix_on(eim_encoders[encoder].pad_b.row, eim_encoders[encoder].pad_b.col);
#else
           encoders_in_matrix_update_user(encoder, !eim_encoders[encoder].flipped);
#endif
           eim_state[encoder]=0; 
        }
    }
    matrix_scan_user();
}
