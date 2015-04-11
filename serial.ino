int incomingByte = 0;   // for incoming serial data

void setup() {
   Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

String content = "";
  char character;
  double x; 

  if(Serial.available()) {
      x = Serial.parseFloat();
      Serial.println(x); 
  }



}
