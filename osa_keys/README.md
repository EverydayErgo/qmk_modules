# OS Aware keys 
  Set of unified keys and functionalities to make moving between operating system easy. Use one key to yield the same functionality. For example **Zoom In** has different shortcut for Windows and MacOS.
  |Shortcut|Windows|MacOS|
  |--------|-------|-----|
  |Zoom In |Ctrl + |Command +|

## How to use
Include this module in your **keymap.json** file.
```JSON
  {
      "module" : ["everydayergo/osa_keys"]
  }
```
Also be sure to include the definitions.
```C
  #include "osa_keys.h"
```

## Default features
By default based on the operating system type 
```C
  KC_LGUI
```
will be swapped with
```C
  KC_LCTL
```
Basically **Control** will be swapped with **Command/Win**. This also applies to **Mod-Tap** and **One Shot Keys**.

## Overrides 
In case operating system wasn't detected properly it can be overridden by using built in functions.
```C
  void force_macos(void);
  void force_windows(void);
```
For example via use of **Leader Key** 

```C
void leader_end_user(void) {
  if (leader_sequence_two_keys(KC_F, KC_M)) {
    force_macos();
  }else if (leader_sequence_two_keys(KC_F, KC_W)) {
    force_windows();
  }
}
```

## Keys
List of available keys with equivalent shortcuts.
|OSA Key|Windows      |MacOS            |Description                    |
|-------|---------------|---------------|-------------------------------|
|OA_VDL |Win+Ctrl+Left  |Control+Left   |Virtual desktop/Workspace Left |
|OA_VDR |Win+Ctrl+Right |Control+Right  |Virtual desktop/Workspace Right|
|OA_APQT|Alt+F4         |Command+Q      |Application quit               |
|OA_APPV|Win+Tab        |Control+Up     |App view                       |
|OA_APPW|               |Control+Down   |App windows                    |
|OA_WBAK|Back           |Command+[      |Web back                       |
|OA_WFWD|Forward        |Command+]      |Web forward                    |
|OA_WREF|F5             |Command+R      |Web refresh                    |
|OA_ZOIN|Ctrl +         |Command +      |Zoom in                        |
|OA_ZOUT|Ctrl -         |Command -      |Zoom out                       |
|OA_ZORT|Ctrl+0         |Command+0      |Zoom reset (100%)              |