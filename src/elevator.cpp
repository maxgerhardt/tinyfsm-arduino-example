#include <tinyfsm.hpp>

#include "elevator.hpp"
#include "fsmlist.hpp"

#include <Arduino.h>

using namespace std;

class Idle; // forward declaration


// ----------------------------------------------------------------------------
// Transition functions
//

static void CallMaintenance() {
  Serial.println("*** calling maintenance ***");
}

static void CallFirefighters() {
  Serial.println("*** calling firefighters ***");
}


// ----------------------------------------------------------------------------
// State: Panic
//

class Panic
: public Elevator
{
  void entry() override {
    send_event(MotorStop());
  }
};


// ----------------------------------------------------------------------------
// State: Moving
//

class Moving
: public Elevator
{
  void react(FloorSensor const & e) override {
    int floor_expected = current_floor + Motor::getDirection();
    if(floor_expected != e.floor)
    {
      Serial.println("Floor sensor defect (expected " + String(floor_expected) + ", got " + String(e.floor) + ")");
      transit<Panic>(CallMaintenance);
    }
    else
    {
      Serial.println("Reached floor " + String(e.floor));
      current_floor = e.floor;
      if(e.floor == dest_floor)
        transit<Idle>();
    }
  };
};


// ----------------------------------------------------------------------------
// State: Idle
//

class Idle
: public Elevator
{
  void entry() override {
    send_event(MotorStop());
  }

  void react(Call const & e) override {
    dest_floor = e.floor;

    if(dest_floor == current_floor)
      return;

    /* lambda function used for transition action */
    auto action = [] { 
      if(dest_floor > current_floor)
        send_event(MotorUp());
      else if(dest_floor < current_floor)
        send_event(MotorDown());
    };

    transit<Moving>(action);
  };
};


// ----------------------------------------------------------------------------
// Base state: default implementations
//

void Elevator::react(Call const &) {
  Serial.println("Call event ignored");
}

void Elevator::react(FloorSensor const &) {
  Serial.println("FloorSensor event ignored");
}

void Elevator::react(Alarm const &) {
  transit<Panic>(CallFirefighters);
}

int Elevator::current_floor = Elevator::initial_floor;
int Elevator::dest_floor    = Elevator::initial_floor;


// ----------------------------------------------------------------------------
// Initial state definition
//
FSM_INITIAL_STATE(Elevator, Idle)
