#include <tinyfsm.hpp>
#include "motor.hpp"
#include <Arduino.h>
using namespace std;


// ----------------------------------------------------------------------------
// Motor states
//

class Stopped
: public Motor
{
  void entry() override {
    Serial.println("Motor: stopped");
    direction = 0;
  };
};

class Up
: public Motor
{
  void entry() override {
    Serial.println("Motor: moving up");
    direction = 1;
  };
};

class Down
: public Motor
{
  void entry() override {
    Serial.println("Motor: moving down");
    direction = -1;
  };
};


// ----------------------------------------------------------------------------
// Base State: default implementations
//

void Motor::react(MotorStop const &) {
  transit<Stopped>();
}

void Motor::react(MotorUp const &) {
  transit<Up>();
}

void Motor::react(MotorDown const &) {
  transit<Down>();
}

int Motor::direction{0};


// ----------------------------------------------------------------------------
// Initial state definition
//
FSM_INITIAL_STATE(Motor, Stopped)
