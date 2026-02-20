# Magnetic Encoder
This adds support for **AS5600** and **MT6701**. Communication happens over I2C so be sure to wire the sensor properly. No pull-up resistors are required if you're using any of the available on the market PCBs.

**MT6701** needs to have **Pin 2** connected to **VCC** to enable **I2C** mode since by default it's on **Analog** mode.

Include this module in your **keymap.json** file.
```JSON
    {
        "module" : ["everydayergo/magnetic_encoder"]
    }
```

Define either sensor in use:
```C 
    #define AS5600  
    or  
    #define MT6701 
```

Processing happens in:
```C
    void housekeeping_task_magnetic_encoder(void) {}
```
There's a weakly defined function to handle the processed angle. In order to perform any action you will have to implement it, i.e. like this:
```C
    void magnetic_encoder_update_user(bool direction) {    
        report_mouse_t report = pointing_device_get_report();

        if(direction) {
            report.v = -1;
        }else {
            report.v = 1;        
        }

        pointing_device_set_report(report);
        pointing_device_send(); 
    }   
```