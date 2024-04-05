Using ESP32 to experience the basics of using TFT_eSPI-library and more sensors as [GPS](https://github.com/auryn31/festival_finder), [Compass](https://github.com/VolosR/RotateCompas/tree/main), LoRA etc.
The underlying Library used for the display is Bodmer/TFT_eSPI. [Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI).
[GC9A01-Tutorial](https://dronebotworkshop.com/gc9a01/#GC9A01_with_ESP32) and [raspioverlay](https://github.com/juliannojungle/gc9a01-overlay/tree/main)


This is the first working version not adjusted to actual display size of 240x240 pixels with round shape:
<!--
![first working display](https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/GC9A01.V1_first_display.png)
-->
<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/GC9A01.V1_first_display.png" heigt=300/>

I am using the Wemos Mini D1 ESP2 - board, which is not usable for breadboard usage, 
because it uses double row headers. But works fine for manual soldering on these pcbs. 

Primary connection schema:

pin | gpio 
--- | --- 
**scl** | 18
**sda** | 19
**dc**  | 27
**cs**  | 5
**rst** | 33

This schematic shows the wemos mini d1 ESP32 pinout from the _**botton side**_ (!). 

<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/Schematic_ESP_Breadboard_GC9A01.V1_2024-04-05.png" heigt=150/>

Some GPIO-pins (12,13,14,15) are exclusively reserved for [openOCD-Debugging](https://www.hackster.io/brian-lough/use-the-platformio-debugger-on-the-esp32-using-an-esp-prog-f633b6) with PlatformIO.

[Debugger-HowTo](https://community.platformio.org/t/esp32-pio-unified-debugger/4541/20)

[PIO-Debugging](https://docs.platformio.org/en/latest/plus/debugging.html)

[Debugger-Flaws](https://community.platformio.org/t/error-esp32-prog/19363/14?u=juergen.schweiss) 
> Especially for this annoying kind of error:
> 
> _*.pioinit:11: Error in sourced command file*_


