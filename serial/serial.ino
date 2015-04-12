// Connect green wire from LED strip to PIN 6 of Arduino

#include <Adafruit_NeoPixel.h>
#define PIN 7
#define WIDTH 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
int currentSegment = 0; 
    uint32_t history[59/WIDTH]; 

void setup() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

//    history[0] = .2;
//    history[1] = .4;
//    history[2] = .6;  
//    updateHistory(history); 
//    
//    addColor(.2);
//    addColor(.9);

}

void loop() {
  float x; 
  if(Serial.available() ) {
      x = Serial.parseFloat();
      Serial.println(x); 
      addColor(x); 
  }
}

void updateHistory(float history[]){ 
  Serial.println("Updating History");
  int historyCount = 0;
  for (int i = 0; i<= 2*WIDTH; i+=WIDTH){ 
   // if (!history[i]) break; 
     
    float x = history[historyCount]; 
      Serial.println(x);

      if (x < .3) {
        //Red Segment
        for (int j = i; j < i+WIDTH; j++) { 
          Serial.println("Setting red");
          strip.setPixelColor(j, 255,0,0);
        }        
      }
      else if (x < .6) {
        for (int j = i; j < i+WIDTH; j++) { 
          strip.setPixelColor(j, 0,0,255);
        }        
      }
      else {
        for (int j = i; j < i+WIDTH; j++) { 
          strip.setPixelColor(j, 0,255,0);
        }        
      }
      historyCount ++; 
    } 

  strip.show();
             
 }
 
 //Given the sentiment of a message, adds the color to the strip
 void addColor(float sentiment){ 
   //First set color of entire strip to sentiment color
   //Then one by one (starting from beginenning, recover color of segments
   //When there are WIDTH pixels left, animated those into the strip, joining the rest
   

   //1
   if (sentiment < .3) red(); 
   else if (sentiment < .6) {
     int sediment = ((sentiment-.3)/.3)*10+1;
     Serial.println(sediment); 
     blue(sediment); 
   }
   else green(); 
   
     delay(1000); 
   //2 Recover Pixels
   for (int i = 0; i< 60-WIDTH; i++){ 
    // Serial.println(i); 
     recoverPixel(i); 
   }
   
         history[currentSegment] = strip.getPixelColor(59); 
   //3 Slide new one over
   for (int i = 59; i> ((currentSegment+1) *WIDTH)-1 ; i--){ 
     strip.setPixelColor(i,0,0,0); 
     strip.setPixelColor(i-WIDTH, strip.getPixelColor(i-1)); 
     strip.show(); 
     delay(35);
   }
   

   currentSegment++;
  delay(1000); 
   
   
 
 }
    
// Uses the history to recover the color of the ith pixel
void recoverPixel(int i){ 
  float x = history[(int)(i/WIDTH)];
  
  //Serial.println(x); 
  delay(35);
   if (x == 0) strip.setPixelColor(i, 0,0,0); 
   else if (x < .3) strip.setPixelColor(i, 255,50,0); 
   else if (x < .6) strip.setPixelColor(i, 0,100,255);
   else strip.setPixelColor(i, 10,255,0);
   strip.show(); 
  
}

void blue(int sediment) { 
//  for (int i=0; i<=59; i++) { 
//    strip.setPixelColor(i, 0,0, 255); 
//  }
//  strip.show(); 
//  sediment = 10;
  uint16_t i, j;
  int limit = 130 + (sediment*6);
  for(j=110; j< limit; j++) {
    //Serial.println(j); 
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(20);
  }
}

void red() {
  for (int j = 0; j<=255; j++) { 
      for (int i=0; i<=59; i++) { 
        strip.setPixelColor(i, j,0, 0); 
      }
      strip.show(); 
      delay(1);
    
  }

}

void green() { 
  for (int i=0; i<=59; i++) { 
    strip.setPixelColor(i, 0,255, 0); 
  }
  strip.show(); 
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
