# Magnetic Encoder
This adds support for **AS5600** and **MT6701**. Communication happens over I2C so be sure to wire the sensor properly. No pull-up resistors are required if you're using any of the available on the market PCBs.

**MT6701** needs to have **Pin 2** connected to **VCC** to enable **I2C** mode since by default it's on **Analog** mode.

Include this module in your **keymap.json** file.
```JSON
    {
        "module" : ["everydayergo/magnetic_encoder"]
    }
```
Also be sure to include the definitions.
```C
    #include "magnetic_encoder.h"
```

Module can detect which sensor is connected so no definitions are needed. You can have at most one of each on keyboard/side of the split keyboard since their I2C addresses are not modifiable.  

Processing happens in:
```C
    void housekeeping_task_magnetic_encoder(void) {}
```
There's a weakly defined function to handle the processed angle. You will get the type of the encoder from which the readout is coming as well as it's direction in boolean type. **True == Up**, **False == Down**. This could be implemented like this:
```C
void magnetic_encoder_update_user(magnetic_encoder_kind_t magnetic_encoder, bool direction) {  
  if(magnetic_encoder == AS5600) {
    if(direction)
      print("\nAS5600: Up");
    else
      print("\nAS5600: Down");
  }else {
    if(direction)
      print("\nMT6701: Up");
    else
      print("\nMT6701: Down"); 
  }
}  
```