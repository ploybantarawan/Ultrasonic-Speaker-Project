#include <M5Stack.h>

void setup() {
  Serial.begin(9600);
  M5.begin();
  M5.Lcd.setCursor(60, 75);
  M5.Lcd.setTextColor(PINK);
  M5.Lcd.setTextSize(5);
  M5.Lcd.print("unmuted");
}

void loop() {

  long duration, inches, cm;

  pinMode(21, OUTPUT);
  
  digitalWrite(21, LOW);
  delayMicroseconds(2);
  digitalWrite(21, HIGH);
  delayMicroseconds(5);
  digitalWrite(21, LOW);

  duration = pulseIn(22, HIGH);

  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 
  delay(100);

   int toneToPlay = 0;
  
  if(cm <= 35 && cm > 25){
      toneToPlay = 392; 
  }
  if(cm <= 25 && cm > 15){
     toneToPlay = 349; 
  }
  if(cm <= 15){
      toneToPlay = 330; 
  }
 
  if(analogRead(35)!= 0 ){
    toneToPlay += (analogRead(35)/100);
  }

  if(analogRead(36)!= 0) {
    toneToPlay += (analogRead(36)/100);
  }
 
  M5.Speaker.tone(toneToPlay);

  
  if(poten() > 2500) {
    delay(100);
  }

  if (M5.BtnA.read() || M5.BtnB.read() || M5.BtnC.read()) {
    M5.Lcd.clear();
  }

  while (M5.BtnA.read() || M5.BtnB.read() || M5.BtnC.read()) {
     M5.Speaker.mute();
     M5.Lcd.setCursor(60, 75);
     M5.Lcd.setTextColor(PINK);
     M5.Lcd.setTextSize(5);
     M5.Lcd.print("muted");
  }
 
  if (M5.BtnA.wasReleased() || M5.BtnB.wasReleased() || M5.BtnC.wasReleased()) {
     M5.Lcd.clear();
     M5.Lcd.setCursor(60, 75);
     M5.Lcd.setTextColor(PINK);
     M5.Lcd.setTextSize(5);
     M5.Lcd.print("unmuted");
  }

}

long poten() {
  long val = 0;
  val = analogRead(26);
  M5.Lcd.setCursor(60, 75);
  M5.Lcd.setTextColor(PINK);
  M5.Lcd.setTextSize(5);
  return val;
}

long microsecondsToCentimeters(long microseconds) {  
  return microseconds / 29 / 2;
}
