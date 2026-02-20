# EverydayErgo QMK Modules
### How to use
Read the full [description](https://docs.qmk.fm/features/community_modules#adding-a-community-module-to-your-external-userspace) on how to add this modules to your external user space, or just follow below
```sh
    cd /path/to/your/external/userspace
    mkdir -p modules    
    git submodule add https://github.com/EverydayErgo/qmk_modules.git modules/everydayergo
    git submodule update --init --recursive
```
Alternatively you can add it to your **qmk_firmware/modules** folder.
```sh
    cd qmk_firmware        
    git submodule add https://github.com/EverydayErgo/qmk_modules.git modules/everydayergo
    git submodule update --init --recursive
```

### Available modules
|Module|Description|
|---|---|
|[Magnetic encoder](https://github.com/EverydayErgo/qmk_modules/tree/main/magnetic_encoder) | Support for AS5600 and MT6701 sensors over I2C |



