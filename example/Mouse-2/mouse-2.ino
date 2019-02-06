// Arduino + Laptop TouchPad. Basic functionality
//
// http://Metku.net 
// Jani Pönkkö 
// 23.07.2009


#include "PS2Mouse.h"
#include "LedControl.h"

#define MDATA 5 // touchpad ps/2 data pin
#define MCLK 6 // touchpad ps/2 clock pin
#define SENSITIVITY 5 // amount of movement needed to get a reaction


LedControl lc=LedControl(12,11,10,1); // forum pin outs

PS2Mouse mouse_one(MCLK, MDATA, REMOTE);

void setup()
{
   lc.setIntensity(0,8);
   lc.shutdown(0,false); // need to take MAX out of shutdown
   lc.clearDisplay(0); 
   delay(10);
  
   Serial.begin(115200);   
   mouse_one.initialize();  
   mouse_one.set_scaling_1_1();
}

void loop()
{
  int data[2];
  mouse_one.report(data);
  Serial.print(data[0]); // Status Byte
  Serial.print(":");
  Serial.print(data[1]); // X Movement Data
  Serial.print(",");
  Serial.print(data[2]); // Y Movement Data
  Serial.println();

  // draw the initial box to the center
  lc.clearDisplay(0);

  // if no movement, light up the center block
  if(data[1]==0 && data[2]==0) 
  {
    lc.setLed(0,3,3,true);
    lc.setLed(0,3,4,true);
    lc.setLed(0,4,3,true);
    lc.setLed(0,4,4,true); 
  } 


   // X-movement 
   if(data[1]>SENSITIVITY)
   {
     lc.setLed(0,1,3,true);
     lc.setLed(0,1,4,true);
     lc.setLed(0,2,3,true);
     lc.setLed(0,2,4,true);
   }
   if(data[1]<-SENSITIVITY)
  {
    lc.setLed(0,5,3,true);
    lc.setLed(0,5,4,true);
    lc.setLed(0,6,3,true);
    lc.setLed(0,6,4,true);
  }


  // Y-movement 
  if(data[2]>SENSITIVITY)
  {
    lc.setLed(0,3,1,true);
    lc.setLed(0,3,2,true);
    lc.setLed(0,4,1,true);
    lc.setLed(0,4,2,true);
  }
  if(data[2]<-SENSITIVITY)
  {
    lc.setLed(0,3,5,true);
    lc.setLed(0,3,6,true);
    lc.setLed(0,4,5,true);
    lc.setLed(0,4,6,true);
  }


  // Left button 
  if(data[0]==10)
 {
    lc.setLed(0,0,6,true);
    lc.setLed(0,0,7,true);
    lc.setLed(0,1,6,true);
    lc.setLed(0,1,7,true);
 }

  // Middle button 
  if(data[0]==12)
 {
    lc.setLed(0,3,6,true);
    lc.setLed(0,3,7,true);
    lc.setLed(0,4,6,true);
    lc.setLed(0,4,7,true);
 }

  // Right button 
  if(data[0]==9)
  {
    lc.setLed(0,6,6,true);
    lc.setLed(0,6,7,true);
    lc.setLed(0,7,6,true);
    lc.setLed(0,7,7,true);
  }

 // some delay so one can see the leds properl 
 delay(100);

}

