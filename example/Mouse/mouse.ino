// Arduino + Laptop TouchPad. iPod style gesture
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

int value;
int i;
int l;
int dir; // indicates where user is "turning" the dial

void setup()
{
   lc.setIntensity(0,8);
   lc.shutdown(0,false); // need to take MAX out of shutdown
   lc.clearDisplay(0); 
   delay(10);

  Serial.begin(115200); 
   mouse_one.initialize();
  mouse_one.set_scaling_1_1();

   value=7;
}

void loop()
{
   int data[2];

  mouse_one.report(data);

   // handle the leds. Made this way to combat flickering...
  for(i=7;i>=0;i--)
  {
     if(value<=i)
    { 
      for(l=0;l<=7;l++)
      lc.setLed(0,l,i,true); 
    }
    else
    { 
      for(l=0;l<=7;l++)
      lc.setLed(0,l,i,false); 
    }
  }


  // Moving to the right 
  if(data[1]>SENSITIVITY)
  {
    if(dir==0) // direction is counter clockwise
   dir=-1; // dec
  }

  // Moving to the left
  if(data[1]<-SENSITIVITY)
  {
    if(dir==0) // direction is clockwise
    dir=1; // incrementation
  }

  // top of the "turn" 
  if(data[2]>SENSITIVITY)
  {
    dir=0; // we got the start indication (top part of the circle)
  }

  // bottom of the "turn"
  if(data[2]<-SENSITIVITY)
  {
    if(dir==-1) // we got counter clockwise turn
    {
      if(value>0)
      {
        value=value-1;
        dir=-2; // reset the value to something non-valid
      }
    } 
    if(dir==1) 
    {
       if(value<7)
       { 
         value=value+1; 
         dir=-2; // reset the value to something non-valid
       } 
    } 
  }

// some delay so one can see the leds properl 
delay(100);


}