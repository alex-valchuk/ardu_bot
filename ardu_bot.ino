#include "moments.h"
#include "distance_meter_sonar.h"
#include "chasis_four_wheels.h"

int Stuck_counter = 0;
int Dist_front_prev = 0;

distance_meter_sonar _distance_meter;
chasis_four_wheels _chasis;

void setup()
{
  _distance_meter.init();
  
  _chasis.init();
  _chasis.stand_still();
}

bool between(int a, int b, int accuracy) {
  return a - accuracy < b && b < a + accuracy;
}

bool potentially_stuck(int dist_front) {
  return
    dist_front == Dist_front_prev
    || between(dist_front, Dist_front_prev, 5);
}

void loop()
{
  _chasis.stand_still();
  int dist_to_move = 0;  

  int dist_front = _distance_meter.get_front();
  if (potentially_stuck(dist_front)) {
    Stuck_counter++;
  }
  else {
    Stuck_counter = 0;
  }

  if (Stuck_counter > 1) {
    if (dist_front < 10) {
      _chasis.go_backward(20);
    }
    
    _chasis.turn_around();
    Stuck_counter = 0;
    return;
  }

  if (dist_front > 30) {
    dist_to_move = dist_front;
  }
  else {
    int dist_left = _distance_meter.get_left();
    int dist_right = _distance_meter.get_right();
  
    if ((dist_left > dist_front) && (dist_left > dist_right))
    {
      _chasis.turn_left();
      dist_to_move = dist_left;
    }
    else if (dist_right > dist_front)
    {
      _chasis.turn_right();
      dist_to_move = dist_right;
    }
    else
    {
      _chasis.turn_right();
    }
  }
  
  _chasis.go_forward(dist_to_move * 0.85); // 85% of measured distance to prevent collisions
  
  Dist_front_prev = dist_front;
}
