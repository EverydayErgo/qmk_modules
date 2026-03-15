#pragma once
#include "i2c_master.h"
#include <stdbool.h>

#define DEG_MARGIN_AS5600 25
#define MAX_DISTANCE_AS5600 500    
#define DEG_MARGIN_MT6701 500
#define MAX_DISTANCE_MT6701 2500      

#define AS5600_ADDRESS (0x36 << 1)
#define MT6701_ADDRESS (0x6 << 1)

#define MAGNET_DETECTED_MASK 0b00100000

typedef enum {
    AS5600,
    MT6701,
    NUM_MAGNETIC_ENCODERS
} magnetic_encoder_kind_t;

enum REG_AS5600 {
    REG_STATUS = 0x0B,
    REG_ANGLE = 0x0E
};

enum REG_MT6701 { 
    REG_ANGA = 0x3,
    REG_ANGB = 0x4
};

typedef struct {
    bool is_present;
    uint16_t new_angle;
    uint16_t prev_angle;
    int8_t movement;
    int8_t prev_movement;
} magnetic_encoder_t;

bool ping_as5600(void);

int16_t mt6701read_angle(void);
int16_t as5600read_angle(void);

bool as5600_write(uint8_t reg_addr);
bool as5600_read(uint8_t* data);

int8_t get_direction(magnetic_encoder_t magnetic_encoder);
uint16_t get_distance(magnetic_encoder_t magnetic_encoder);
int8_t get_movement(int magnetic_encoder_kind, magnetic_encoder_t magnetic_encoder);

void process_magnetic_encoder(void);
void magnetic_encoder_update_user(magnetic_encoder_kind_t magnetic_encoder, bool);
