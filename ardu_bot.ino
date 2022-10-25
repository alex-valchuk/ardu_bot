#include "moments.h"
#include "sonar.h"
#include "neck.h"
#include "chasis_four_wheels.h"

const int Max_dist = 300;

const int Left_ang = 160;
const int Between_left_and_front_ang = 125;
const int Front_ang = 90;
const int between_right_and_front_ang = 55;
const int Right_ang = 20;

int Stuck_counter = 0;
int Dist_front_prev = 0;

sonar _sonar;
neck _neck;
chasis_four_wheels _chasis;

void setup()
{
  _sonar.init(13, 12);
  _neck.init(14);
  _chasis.init();

  _chasis.stand_still();
}

int measure_dist_by_eyes(int angle) {
  _neck.rotate(angle);
  return _sonar.measure_dist_with_sonar(Max_dist);
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

  int dist_front = measure_dist_by_eyes(Front_ang);
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
    int dist_left = measure_dist_by_eyes(Left_ang);
    int dist_right = measure_dist_by_eyes(Right_ang);
  
    _neck.rotate(Front_ang); // to always look forward
  
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
