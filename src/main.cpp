#include <Arduino.h>
#include <Ultrasonic.h>
#include <Display4Digit7Segments.h>
#include <TM1637Display.h>
#define CLK 12
#define DIO 13
const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
	SEG_C | SEG_E | SEG_G,
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
	};

TM1637Display display(CLK, DIO);

int aPin = 2;
int bPin = 3;
int cPin = 4;
int dPin = 5;
int ePin = 6;
int fPin = 7;
int gPin = 8;
int GND1 = A0;
int GND2 = A1;
int GND3 = A2;
int GND4 = A3;
int DTime = 4;

int sensorTrigPlotId = 11;
int sensorEchoPlotId = 10;

Ultrasonic ultrasonic(sensorTrigPlotId, sensorEchoPlotId); //(Trig,Echo)
Display4Digit7Segments ledComponent(aPin, GND1); //(segA, Digit1)

const long interval = 1000;
unsigned long previousMillis = 0;
int mDistanceInCm = 0;

int lastBT = 0;
int ledSTATE = 0;


void setup() {
  // initialise la communication série
  Serial.begin(9600);

  pinMode(3, INPUT);
  ledComponent.Setup();
  
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);
  display.clear();

}

void loop() {
  int etatBT = digitalRead(3);
  if (lastBT == 0 && etatBT == 1) {
    lastBT = 1;
    delay(100);
    ledSTATE = 1;
    delay(100);
  }
  else if (lastBT == 1 && etatBT == 1) {
    lastBT = 0;
    delay(100);
    ledSTATE = 0;
    delay(100);
  }

  if (mDistanceInCm <= 1000){
    if (ledSTATE == 1) {
      delay(100);
      ledComponent.Display(1, 3);
      delay(100);
      display.showNumberDec(mDistanceInCm, false);
      delay(DTime);
    } else {
      display.clear();
    }
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    mDistanceInCm = ultrasonic.Ranging(CM);
    Serial.println(mDistanceInCm);
  }

}