#define EIM_DEFAULT_RESOLUTION 2
#define EIM_ENCODER_NAMES(...)  enum {__VA_ARGS__, EIM_LAST_ENCODER};
#define EIM_ENCODERS_BEGIN eim_encoder eim_encoders[EIM_LAST_ENCODER] = {
#define EIM_PADA(p_r, p_c) {.row=p_r, .col=p_c}
#define EIM_PADB(p_r, p_c) {.row=p_r, .col=p_c}
#define EIM_ENC(_name, _pad_a, _pad_b) {.name=_name, _pad_a, _pad_b, .resolution=EIM_DEFAULT_RESOLUTION, .flipped=false},    
#define EIM_ENCR(_name, _pad_a, _pad_b, _enc_r) {.name=_name, _pad_a, _pad_b, .resolution=_enc_r, .flipped=false},
#define EIM_ENCF(_name, _pad_a, _pad_b) {.name=_name, _pad_a, _pad_b, .resolution=EIM_DEFAULT_RESOLUTION, .flipped=true},
#define EIM_ENCRF(_name, _pad_a, _pad_b, _enc_r) {.name=_name, _pad_a, _pad_b, .resolution=_enc_r, .flipped=true},
#define EIM_ENCODERS_END };

typedef struct {
    uint8_t row;
    uint8_t col;
}eim_enc_pad;

typedef struct {
    uint8_t name;
    eim_enc_pad pad_a;
    eim_enc_pad pad_b;
    uint8_t resolution;
    bool flipped;
}eim_encoder;