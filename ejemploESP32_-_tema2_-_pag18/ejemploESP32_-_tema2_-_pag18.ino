#include <M5Stack.h>

uint8_t PinGPIO = 39;
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("Pin GPIO value: ");
  pinMode(PinGPIO, INPUT); // INPUT_PULLDOWN
}

void loop() {
  // put your main code here, to run repeatedly:

  M5.Lcd.setCursor(180,0);
  if(digitalRead(PinGPIO)){
    M5.Lcd.print("ON ");
  }else{  
    M5.Lcd.print("OFF");
  };
  delay(500);
  M5.update();
}
