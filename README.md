Using ESP32 to experience the basics of using TFT_eSPI-library and more sensors as [GPS](https://github.com/auryn31/festival_finder), [Compass](https://github.com/VolosR/RotateCompas/tree/main), LoRA etc.
The underlying Library used for the display is Bodmer/TFT_eSPI. [Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI).
[GC9A01-Tutorial](https://dronebotworkshop.com/gc9a01/#GC9A01_with_ESP32) and [raspioverlay](https://github.com/juliannojungle/gc9a01-overlay/tree/main)
[TFT_eSPI-sprite usage](https://github.com/VolosR/RotateSpritesTutorial)

[PlatformIO configuration](https://net-things.de/index.php/blog/nutzung-der-tft-espi-bibliothek-mit-platformio)



This is the first working version not adjusted to actual display size of 240x240 pixels with round shape:
<!--
![first working display](https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/GC9A01.V1_first_display.png)
-->
<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/GC9A01.V1_first_display.png" heigt="150"/>

I am using the [Wemos Mini D1 ESP2](https://artofcircuits.com/product/wemos-d1-mini-esp32-esp-wroom-32-4mb) - board, which is not usable for breadboard usage, 
because it uses double row headers. But works fine for manual soldering on these pcbs. 

Primary connection schema:

pin | gpio 
--- | --- 
**scl** | 18
**sda/miso** | 19
**dc**  | 27
**cs**  | 5
**rst** | 33

I'm using this eps32 pin configuration TFT_eSPI in User_Setup.h:  

See also: [Setting up the TFT_eSPI Library](https://dronebotworkshop.com/gc9a01/#Setting_up_the_TFT_eSPI_Library)

```cpp
/--- GC9A01.V1 display has no MISO-pin nor a BL-pin!
//###################################################################################
//--- js 3.4.24 changed for Breadboarddisplay and release Debugging-Pins 12,13,14,15
//###################################################################################
#define TFT_MISO -1 
#define TFT_SCLK 18
#define TFT_MOSI 19  // *SDA* labeled pin on GC9A01.V1
#define TFT_CS   5   // Chip select control pin
#define TFT_DC   27  // Data Command control pin
#define TFT_RST  33  // Reset pin (could connect to Arduino RESET pin)
#define TFT_BL   -1  // LED back-light, could be 22
```

This schematic shows the wemos mini d1 ESP32 pinout from the _**botton side**_ (!). 

<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/Schematic_ESP_Breadboard_GC9A01.V1_2024-04-05.png" heigt="300"/>

Some GPIO-pins (12,13,14,15) are exclusively reserved for [openOCD-Debugging](https://www.hackster.io/brian-lough/use-the-platformio-debugger-on-the-esp32-using-an-esp-prog-f633b6) with PlatformIO.

[Debugger-HowTo](https://community.platformio.org/t/esp32-pio-unified-debugger/4541/20)

[PIO-Debugging](https://docs.platformio.org/en/latest/plus/debugging.html)

[Debugger-Flaws](https://community.platformio.org/t/error-esp32-prog/19363/14?u=juergen.schweiss) 
> Especially for this annoying kind of error:
> 
> _*.pioinit:11: Error in sourced command file*_

<img src="https://github.com/juergs/ESP32_GC9A01_Breadboard/blob/main/ESP32_prototype_fitting_for%20ESP32-Debugger%20.png" height="150"/>

[dronebot-Tutorial](https://dronebotworkshop.com/gc9a01/)


[GC9A01 Display Driver Demo](https://github.com/carlfriess/GC9A01_demo/blob/main/README.md)



