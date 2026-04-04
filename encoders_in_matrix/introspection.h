#define EIM_DEFAULT_RESOLUTION 2
#define EIM_ENCODER_NAMES(...) typedef enum {__VA_ARGS__, EIM_LAST_ENCODER} enc_names_t;
enum {EIM_PADA_R, EIM_PADA_C, EIM_PADB_R, EIM_PADB_C, EIM_RES, EIM_FLIP, EIM_LAST_ENC_PROPERTY};
#define EIM_ENCODERS_BEGIN uint8_t eim_encoders[EIM_LAST_ENCODER][EIM_LAST_ENC_PROPERTY] = {
#define EIM_ENCODERS_END };
#define EIM_PADA(p_r, p_c) p_r, p_c
#define EIM_PADB(p_r, p_c) p_r, p_c
#define EIM_ENC(name,  _pad_a, _pad_b) {_pad_a, _pad_b, EIM_DEFAULT_RESOLUTION, false},
#define EIM_ENCR(name, _pad_a, _pad_b, _enc_r) {_pad_a, _pad_b, _enc_r, false},
#define EIM_ENCF(name, _pad_a, _pad_b) {_pad_a, _pad_b, EIM_DEFAULT_RESOLUTION, true},
#define EIM_ENCRF(name, _pad_a, _pad_b, _enc_r) {_pad_a, _pad_b, _enc_r, true},