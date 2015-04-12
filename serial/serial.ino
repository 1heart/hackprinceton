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
}

/*
* Clear history and turn off all pixels. 
*/
void reset(){ 
  memset(history, 0, sizeof(history));
  for (int i = 0; i<=59; i++) strip.setPixelColor(i,0,0,0); 
  strip.show(); 
}

void loop() {
  float x; 
  if(Serial.available() ) {
      x = Serial.parseFloat();
      Serial.println(x); 
      if (x == 9.0) reset(); 
      else if (x != 0) addColor(x);      
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
   if (sentiment < .3) { 
      int sediment = ((sentiment)/.3)*10+1;

     red(sediment); 
   }
   else if (sentiment < .6) {
     int sediment = ((sentiment-.3)/.3)*10+1;
     Serial.println(sediment); 
     blue(sediment); 
   }
   else{ 
      int sediment = ((sentiment-.6)/.6)*10+1;

     green(sediment); 
   }
   
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
     delay(25);
   }
   

   currentSegment++;
  delay(1000); 
   
   
 
 }
    
// Uses the history to recover the color of the ith pixel
void recoverPixel(int i){ 
  //float x = history[(int)(i/WIDTH)];
  
  //Serial.println(x); 
//  delay(25);
//   strip.setPixelColor(i, history[(int)(i/WIDTH)]); 
//   strip.show(); 
   uint32_t c =  history[(int)(i/WIDTH)];
      uint8_t
      r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
      b = (uint8_t)c; 
   fadeToColor(i, r, g, b);  
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

void red(int sediment) {
//  for (int j = 0; j<=255; j++) { 
//      for (int i=0; i<=59; i++) { 
//        strip.setPixelColor(i, j,0, 0); 
//      }
//      strip.show(); 
//      delay(1); 
//  }
  uint16_t i, j;
  int limit = 30 + (sediment*5);
  for(j=25; j< limit; j++) {
    //Serial.println(j); 
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
        strip.show();
      delay(20);
}
}

void green(int sediment) { 

  uint16_t i, j;
  int limit = 190 + (sediment*3);
  for(j=180; j< limit; j++) {
    //Serial.println(j); 
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(20);
  }
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


/*
* Slowly fade a particular pixel to an end color
* @param i index of pixel to change
*/
void fadeToColor(int i,  int Rend, int Gend, int Bend) { 
  uint32_t c = strip.getPixelColor(i); 
   uint8_t
      r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
      b = (uint8_t)c;
      
   int n = 15; 
   int Rnew, Gnew, Bnew; 
   for(int j = 0; j < n; j++) {
     Rnew = r + (Rend - r) * j / n;
     Gnew = g + (Gend - g) * j / n;
     Bnew = b + (Bend - b) * j / n;
     
     strip.setPixelColor(i, strip.Color(Rnew, Gnew, Bnew)); 
     strip.show();
     delay(1); 
    }
}
