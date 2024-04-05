Using ESP32 to experience the basics of using TFT_eSPI-library and more sensors as GPS, [Compass](https://github.com/VolosR/RotateCompas/tree/main), LoRA etc.
The underlying Library used for the display is Bodmer/TFT_eSPI. [Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI).


This is the first working version not adjusted to actual display size of 240x240 pixels with round shape:
<!--
![first working display](https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/GC9A01.V1_first_display.png)
-->
<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/GC9A01.V1_first_display.png" heigt=300/>

I am using the Wemos Mini D1 ESP2 - board, which is not usable for breadboard usage, 
because it uses double row headers. But works fine for manual soldering on these pcbs. 

connection schema:

pin | gpio 
--- | --- 
**scl** | 18
**sda** | 19
**dc**  | 27
**cs**  | 5
**rst** | 33

This schematics shows the wemos mini d1 ESP32 pinout from the _botton side_ (!). 
<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/Schematic_ESP_Breadboard_GC9A01.V1_2024-04-05.png" heigt=150/>


