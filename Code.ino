#include <Wire.h>
#include "RTClib.h"
int PumpRelaisPin = 8;
int LightRelaisPin = 9;
int VentRelaisPin = 10;
RTC_DS3231 rtc;

void setup() {
  
  Serial.begin(9600);

  pinMode(PumpRelaisPin, OUTPUT);
  pinMode(LightRelaisPin, OUTPUT);
  pinMode(VentRelaisPin, OUTPUT);

  //Clock
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  DateTime now = rtc.now();

  //PumpRelais
  delay(100);

  if (sensorValue > 560 and (now.hour() == 8 or now.hour() == 16 or now.hour() == 19)) {    // trockene erde
    digitalWrite(PumpRelaisPin, LOW); // an
    delay(1000);
    digitalWrite(PumpRelaisPin, HIGH);  // aus
  } else {
    digitalWrite(PumpRelaisPin, HIGH);  // aus

  }

  //Light
  Serial.println(String(now.hour()) + ":" + String(now.minute()));
  if (now.hour() > 6 and now.hour() < 22) {
    Serial.println("Licht ist an");
    digitalWrite(LightRelaisPin, HIGH);// an
  } else {
    digitalWrite(LightRelaisPin, LOW); // aus
  }
  delay(1000);

  //Vent
  if (now.hour() > 7 and now.hour() < 22) {
    Serial.println("Vent ist an");
    digitalWrite(VentRelaisPin, HIGH);// an
  } else {
    digitalWrite(VentRelaisPin, LOW); // aus
  }

}
