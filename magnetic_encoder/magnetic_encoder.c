#include "magnetic_encoder.h"
#include "print.h"

static int8_t prev_movement = 0;
static uint16_t prev_angle = 0;

__attribute__((weak)) void magnetic_encoder_update_user(bool) {}

uint16_t mt6701read_angle(void)
{   
    uint16_t angle = 0;
    uint8_t data = 0;
    uint8_t addr = SLAVE_TO_ADDR(MT6701_ADDRESS);

    i2c_status_t result = i2c_read_register(addr, REG_ANGA, &data, sizeof(data), I2C_TIMEOUT_INFINITE);
    if(result != I2C_STATUS_SUCCESS)
    {
        print("Error! Can't read REGA from MT6701\n");   
        return 0;     
    }
    angle = data;
    angle <<= 6;

    result = i2c_read_register(addr, REG_ANGB, &data, sizeof(data), I2C_TIMEOUT_INFINITE);
    if(result != I2C_STATUS_SUCCESS)
    {
        print("Error! Can't read REGA from MT6701\n");      
        return 0;  
    }
    
    return angle |= data;
}

uint16_t as5600read_angle(void) {
    uint8_t data = 0;
    uint16_t angle = 0;

    as5600_write(REG_STATUS); 
    as5600_read(&data);

    if(data & MAGNET_DETECTED_MASK) {            
        as5600_write(REG_ANGLE);
        as5600_read(&data);
        angle = data;
        angle <<= 8;
        as5600_read(&data);
        angle |= data;
    }  
    return angle;
}

bool as5600_write(uint8_t reg_addr)
{
    uint8_t addr = SLAVE_TO_ADDR(AS5600_ADDRESS);
    i2c_status_t result = i2c_transmit(addr, &reg_addr, sizeof(uint8_t), I2C_TIMEOUT_INFINITE);
    if(result != I2C_STATUS_SUCCESS) {
        print("Error transmit to AS5600\n");
        return false;
    }
    return true;
}

bool as5600_read(uint8_t* out) { 
    uint8_t addr = SLAVE_TO_ADDR(AS5600_ADDRESS);   
    i2c_status_t result = i2c_receive(addr, out, sizeof(uint8_t), I2C_TIMEOUT_INFINITE);
    if(result != I2C_STATUS_SUCCESS) {
        print("Error reading from AS5600\n");
        return false;
    }
    return true;
}

int8_t get_direction(uint16_t prev_angle, uint16_t new_angle)
{
    if(new_angle > prev_angle)
        return 1;
    if(prev_angle > new_angle)
        return -1;
    
    return 0;
}

uint16_t get_distance(uint16_t prev_angle, uint16_t new_angle)
{
    if(prev_angle > new_angle)
        return prev_angle - new_angle;
    if(prev_angle < new_angle)
        return new_angle - prev_angle;   
    
    return 0;
}

int8_t get_movement(uint16_t prev_angle, uint16_t new_angle)
{
    int direction = get_direction(prev_angle, new_angle);
    uint16_t distance = get_distance(prev_angle, new_angle);
    int max_distance = MAX_DISTANCE;    

    if(direction == 1)
    {
        if(distance < max_distance)
        {
            prev_movement = 1;
            return 1;
        }
        else
        {
            return prev_movement;
        }
    }

    if(direction == -1)
    {
        if(distance < max_distance)
        {
            prev_movement = -1;
            return -1;
        }
        else
        {
            return prev_movement;
        }
    }
    return 0;
}

void process_magnetic_encoder(void) {
    uint16_t angle = 0;
    int8_t movement = 0;

#ifdef AS5600
    angle = as5600read_angle();
#elif defined (MT6701)
    angle = mt6701read_angle();
#else
    return;
#endif    

    if(get_distance(prev_angle, angle) >= DEG_MARGIN) {
        movement = get_movement(prev_angle, angle);       

        if(movement == -1)
        {                       
            magnetic_encoder_update_user(false);
        }

        if(movement == 1)
        {            
            magnetic_encoder_update_user(true);
        }
        prev_angle = angle;
    }   
}

void housekeeping_task_magnetic_encoder(void) {
    process_magnetic_encoder();
}