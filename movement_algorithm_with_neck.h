/* 
 * Encapsulates the algorithm of the robot that has a neck (servo) which rotates an ultro-sound distance meter HC-SR04 (Vally eyes).
 */
#include "movement_algorithm.h"
#include "distance_meter_sonar.h"
#include "chasis_four_wheels.h"
#include "neck.h"

class movement_algorithm_with_neck : public movement_algorithm {
public:
  void init() {
    _distance_meter.init();
    _chasis.init();

    _chasis.stand_still();
  }
  
  void move() {
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
    
    //int dist_to_move = _distance_meter.get_front();
    //Serial.println(dist_to_move);
    _chasis.go_forward(dist_to_move * 0.85); // 85% of measured distance to prevent collisions
    Dist_front_prev = dist_front;
  }

private:
  int Stuck_counter = 0;

  distance_meter_sonar _distance_meter;
  chasis_four_wheels _chasis;
};