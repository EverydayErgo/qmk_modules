#pragma once
#include "i2c_master.h"
#include <stdbool.h>

#ifndef SLAVE_TO_ADDR
    #define SLAVE_TO_ADDR(n) (n << 1)
#endif

#ifdef AS5600    
    #define DEG_MARGIN 25
    #define MAX_DISTANCE 500    
#elif defined (MT6701) 
    #define DEG_MARGIN 500
    #define MAX_DISTANCE 2500      
#else
    #define DEG_MARGIN 25
    #define MAX_DISTANCE 500    
#endif

#define AS5600_ADDRESS 0x36
#define MT6701_ADDRESS 0x6

#define MAGNET_DETECTED_MASK 0b00100000

enum AS5600 {
    REG_STATUS = 0x0B,
    REG_ANGLE = 0x0E
};

enum MT6701 { 
    REG_ANGA = 0x3,
    REG_ANGB = 0x4
};    

uint16_t mt6701read_angle(void);
uint16_t as5600read_angle(void);

bool as5600_write(uint8_t reg_addr);
bool as5600_read(uint8_t* data);

int8_t get_direction(uint16_t prev_angle, uint16_t new_angle);
uint16_t get_distance(uint16_t prev_angle, uint16_t new_angle);
int8_t get_movement(uint16_t prev_angle, uint16_t new_angle);

void process_magnetic_encoder(void);
void magnetic_encoder_update_user(bool);