/*
  Origin:   https://github.com/VolosR/BreadboardTTGOS3/blob/main/BreadboardTTGOS3.ino

  Location: C:\Users\js\Documents\PlatformIO\Projects

  GC9A01:
    https://github.com/carlfriess/GC9A01_demo/blob/main/GC9A01.c
    https://www.buydisplay.com/1-28-inch-tft-ips-lcd-display-module-240x240-spi-for-arduino-raspberry-pi
  
  TFT pin settings:
  C:\Users\js\Documents\PlatformIO\Projects\ESP32_BreadboardDisplay\.pio\libdeps\wemos_d1_mini32_debug\TFT_eSPI\User_Setup.h
  https://community.platformio.org/t/esp32-debugging-problems-no-continue-step-over-etc/8912
  https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_24.html
  https://community.platformio.org/t/stepover-problem-debuging-esp32-on-pio/21579
  
  NOK:
  1.  Delete the .pio folder of the project to make sure a clean build is made
  2.  Add debug_build_flags = -O0 -g3 -ggdb3 (docs) to the (debug) environment to make sure compiler optimizations are fully disabled. The default is -Og for debug.

  https://github.com/Bodmer/TFT_eSPI/blob/master/examples/Sprite/Transparent_Sprite_Demo/Transparent_Sprite_Demo.ino

  https://dronebotworkshop.com/gc9a01/#GC9A01_with_ESP32

  TFT-Wiki & SW Img2LCD: 
  https://www.waveshare.com/wiki/1.28inch_LCD_Module

  GPS:
  https://gpsd.gitlab.io/gpsd/NMEA.html#_gll_geographic_position_latitudelongitude  
  https://github.com/kosma/minmea/blob/master/minmea.c

  ESP32:
  https://www.robolinkmarket.com/Data/EditorFiles/datasheet/kolban-ESP32.pdf

*/


#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "math.h"

//#include "display/display.h"
//#include "gps/gps.h"
//#include "lora/lora.h"
//#include "orientation/orientation.h"

#include "main.h"

TFT_eSPI lcd = TFT_eSPI();

TFT_eSprite spr     = TFT_eSprite(&lcd);
TFT_eSprite sprite  = TFT_eSprite(&lcd);
TFT_eSprite sprite2 = TFT_eSprite(&lcd);
TFT_eSprite sprite3 = TFT_eSprite(&lcd);
TFT_eSprite sprite4 = TFT_eSprite(&lcd);

#define color1 TFT_WHITE
#define color2 0x8410
#define color3 0x3828
#define color4 0xF2DF
#define color5 0x00A3
#define color6 0x00A3

int ADC1 = 1; //light sensor pin
int ADC2 = 2; //microphone pin
int BTN  = 21;
int LED = LED_BUILDIN; 

//circuit gauge variables

int sx=70; // center x
int sy=70; // center y
int r=62;

double rad=0.01745;
float x[360]; //outer point
float y[360];


float px[360]; //inner point
float py[360];

float lx[360]; //text
float ly[360];

int start[12];
int startP[60];

String cc[10]={"0","10","20","30","40","50","60","70","80","90"};

//Sprite 2 data
int gw = 150; //graph width
int gh =  54; //hraph heigth
int gx =  20; //graph x
int gy =  55; // graph Y

int _count = 0; 
int _state = 0; 

#include <string>
// int old_Angle = 0;
// int old_AngleDistance = 0;
const int mx = TFT_WIDTH / 2;
const int my = TFT_HEIGHT / 2;
const int distanceOffset = 100;
const int textHeight = 30;
const int arrowHeight = distanceOffset - textHeight;

//----------------------------------------------------

void drawStringWithColor(int angle, String text, uint16_t color) 
{
  lcd.setPivot(mx, my);
  spr.setColorDepth(8);
  spr.createSprite(64, textHeight);
  spr.setPivot(32, distanceOffset);
  spr.fillSprite(TFT_BLACK);
  spr.setTextColor(color);
  spr.setTextDatum(MC_DATUM);
  spr.drawString(text, 32, 15, 4);
  spr.pushRotated(angle);
} 

//----------------------------------------------------

void setup() 
{
    pinMode(BTN,INPUT_PULLUP);
    pinMode(LED,OUTPUT);

/*
    Serial.begin(115200);
    
     while (!Serial && (_count < 30) )
    {
      delay(200); // Wait for serial port to connect with timeout. Needed for native USB
      digitalWrite(LED_BUILDIN, _state);
      _state = !_state;
      _count++;
    }
    digitalWrite(LED_BUILDIN, HIGH);
    
    Serial.print("\e[1;31m"); 
    Serial.print("\n\nSetup!"); 
    Serial.print(" ");
    Serial.print(__FILE__);
    Serial.print(" ");
    Serial.print(__LINE__);
    Serial.print(" ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.print(__TIME__);
    Serial.println ("\e[1;37m"); 
*/

    //--- display direct init
    lcd.init();
    lcd.fillScreen(TFT_BLACK);
    lcd.setRotation(0);

    //drawStringWithColor(0, "TEST", TFT_YELLOW);  //TFT_RED

    delay(5000);
               
    lcd.setTextDatum(4);
    lcd.setTextColor(TFT_ORANGE,TFT_BLACK);    
    lcd.drawString("  ADC READ  ",70,10,2);
    
    lcd.setTextColor(TFT_ORANGE,TFT_BLACK);
    lcd.drawString("MICROPHONE",225,10,2);
    lcd.drawString("MINI TERMINAL AC12",210,86);

    sprite.createSprite(140,140);
    sprite.setTextDatum(4);

    sprite2.createSprite(150,55);
    sprite2.setTextDatum(4);

    sprite3.createSprite(120,70);
    sprite4.createSprite(40,80);
    sprite3.fillSprite(color3);

    sprite4.fillSprite(TFT_BLACK);
    sprite4.setTextDatum(4);
    sprite4.setTextColor(color1,color3);

    int b=0;
    int b2=0;

    for(int i=0;i<360;i++)
    {
       x[i]=(r*cos(rad*i))+sx;
       y[i]=(r*sin(rad*i))+sy;
       px[i]=((r-12)*cos(rad*i))+sx;
       py[i]=((r-12)*sin(rad*i))+sy;

       lx[i]=((r-18)*cos(rad*i))+sx;
       ly[i]=((r-18)*sin(rad*i))+sy;
       
       if(i%36==0)
       {
        start[b]=i;
        b++;
       }

       if(i%6==0)
       {
        startP[b2]=i;
        b2++;
       }
    }


}

int angle=0;
int values[20]={0};
int values2[20]={0};
int curent=0;
int counter=0;
int counter_last=2;
int calib=20;

int curentTime=0;
int period=500;

int term[6]={0};
int term2[6]={0};

int t[6]={0};
int t2[6]={0};
bool c=0;
bool c1;
int number=0;
bool onOff=0;
int debounce=0;

//----------------------------------------------------

void loop() 
{

 if(digitalRead(BTN)==0)
 {
  if(debounce==0)
  {
    debounce=1;
    onOff=!onOff;
    digitalWrite(LED,onOff);
    }
  }
  else debounce=0;
  
  angle   = map(analogRead(ADC1),0,4095,0,359);
  int num = analogRead(ADC2);
  curent  = map(num,0,200,0,gh);
  
  for(int i=0;i<20;i++)
    values2[i]=values[i];
  
  for(int i=19;i>0;i--)
    values[i-1]=values2[i];
  
  values[19]=curent;
 
  sprite4.fillRoundRect(0,0,40,80,4,color3);
  sprite2.fillSprite(TFT_BLACK);
  sprite.fillRoundRect(0,0,140,140,3,color6);
  sprite.setTextFont(0);

  for(int i=0;i<10;i++)
     if(start[i]+angle<360)
     {
      sprite.drawString(cc[i],x[start[i]+angle],y[start[i]+angle]);
      sprite.drawLine(px[start[i]+angle],py[start[i]+angle],lx[start[i]+angle],ly[start[i]+angle],color1);
    }
    else
    {
      sprite.drawString(cc[i],x[(start[i]+angle)-360],y[(start[i]+angle)-360]);
      sprite.drawLine(px[(start[i]+angle)-360],py[(start[i]+angle)-360],lx[(start[i]+angle)-360],ly[(start[i]+angle)-360],color1);
    }

  float v=angle/3.60;
  for(int i=0;i<60;i++)
  
  if(startP[i]+angle<360)
      sprite.fillCircle(px[startP[i]+angle],py[startP[i]+angle],1,color1);
  else
      sprite.fillCircle(px[(startP[i]+angle)-360],py[(startP[i]+angle)-360],1,color1);

  sprite.setTextColor(TFT_SILVER,color6);
  sprite.drawString("AMBIENT",sx,sy-22,2);
  sprite.drawString("LIGHT",sx,sy+18,2);
  sprite.setTextColor(color1,color6);
  sprite.drawString(String((int)v)+"%",sx,sy,4);
  sprite.fillTriangle(70,28,74,36,66,36,TFT_RED);
 

  for(int i=1;i<10;i++)
    sprite2.drawLine(gx+(i*gw/10),gy,gx+(i*gw/10),gy-gh,color2);

  for(int i=1;i<6;i++)
  {
    sprite2.drawLine(gx,gy-(i*9),gx+gw,gy-(i*9),color2);
  
    if(i==1 || i==3 || i==5)
      sprite2.drawString(String(i*9-27),gx-12,gy-(i*9));
    }
   
  sprite2.drawLine(gx,gy,gx,gy-gh,TFT_WHITE);

  for(int i=0;i<19;i++)
  {
    sprite2.drawLine(gx+(i*8),gy-values[i]-calib,gx+((i+1)*9),gy-values[i+1]-calib,TFT_RED);
    sprite2.drawLine(gx+(i*8),gy-values[i]-1-calib,gx+((i+1)*8),gy-values[i+1]-1-calib,TFT_RED);
  }

 
  if(curentTime+period<millis())
  {
    sprite3.fillSprite(TFT_BLACK);
    c1=c;
    for(int i=0;i<6;i++)
    {
      term2[i]=term[i];
      t2[i]=t[i];
    }

    for(int i=5;i>0;i--)
    {
      term[i-1]=term2[i];
      t[i-1]=t2[i];
    }

    term[5]=(analogRead(4) * 2 * 3.3 * 1000) / 4096;
    t[5]=number;
    sprite3.setTextColor(TFT_WHITE,color5);
    
    for(int i=0;i<6;i++)
    {
      sprite3.drawString(String(t[i])+"  BATERY="+String(term[i])+"     ",4,4+i*11);
      c1=!c1;
    
    }
    curentTime=millis();
    c=!c;
    number++;
  }

  if(onOff==1)
    sprite4.drawString("ON",20,10);
  else
    sprite4.drawString("OFF",20,10);

  sprite4.drawCircle(20,28,10,TFT_SILVER);
  sprite4.drawCircle(20,64,10,TFT_SILVER);
  sprite4.drawRect(10,28,21,36,TFT_SILVER);
  sprite4.fillRect(11,28,19,36,color3);
  
  sprite4.fillCircle(20,28+(onOff*36),7,TFT_WHITE);

  sprite.pushSprite(0,20);
  sprite2.pushSprite(150,20);
  sprite3.pushSprite(150,92);
  sprite4.pushSprite(276,80);
 
}
