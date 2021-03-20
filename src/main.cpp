#include <Arduino.h>
#include "fsmlist.hpp"

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10000);
  Serial.println("c=Call, f=FloorSensor, a=Alarm, q=Quit ? ");
}

void loop()
{
  fsm_list::start();

  Call call;
  FloorSensor sensor;

  String answer = "";
  if (Serial.available() > 0)
  {
    char c = (char)Serial.read();

    switch (c)
    {
    case 'c':
      Serial.println("Floor ? ");
      answer = Serial.readStringUntil('\n');
      call.floor = answer.toInt();
      send_event(call);
      break;
    case 'f':
      Serial.println("Floor ? ");
      answer = Serial.readStringUntil('\n');
      sensor.floor = answer.toInt();
      send_event(sensor);
      break;
    case 'a':
      send_event(Alarm());
      break;
    case 'q':
      Serial.println("Thanks for playing!");
      //return 0;
    default:
      Serial.println("Invalid input");
    };
  }
}