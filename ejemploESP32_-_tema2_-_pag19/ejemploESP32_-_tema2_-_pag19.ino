#include <M5Stack.h>


int buff(int pin){

  int out = ( 50 - touchRead(pin) );

  if( out > 0 ){
    return ( out + 2 );
  }else{
    return 0;
  }
  
}

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("Touch sensor value: ");
}

void loop() {
  // put your main code here, to run repeatedly:

  M5.Lcd.setCursor(240,0);
  M5.Lcd.print(touchRead(G2));
  M5.Lcd.setCursor(0,16);
  M5.Lcd.printf(" RAW: %d     ", buff(G2));
  Serial.println(buff(G2));
  delay(500);
  M5.update();
}
