#include "moments.h"
#include "sonar.h"
#include "neck.h"
#include "chasis.h"

const int Max_dist = 300;

const int Left_ang = 160;
const int Between_left_and_front_ang = 125;
const int Front_ang = 90;
const int between_right_and_front_ang = 55;
const int Right_ang = 20;

int Stuck_counter = 0;
int Dist_front_prev = 0;

neck _neck;
chasis _chasis;

void setup()
{
  Sonar_init(13, 12);
  _neck.init(14);
  _chasis.init();


  _stop();
}

}

int measure_dist_by_eyes(int angle) {
  _neck.rotate(angle);
  return measure_dist_with_sonar(Max_dist);
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
  _stop();
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
      _chasis.go_backward();
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
  
  double dist = dist_to_move * 0.85;
  int time_for_move = Time_for_start_moving + dist * Time_for_1cm;
  _chasis.go_forward(time_for_move);
  
  Dist_front_prev = dist_front;
}
