#include <M5Stack.h>

#define PinGPIO G5;
static volatile uint8_t active = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  M5.Lcd.setTextSize(2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
