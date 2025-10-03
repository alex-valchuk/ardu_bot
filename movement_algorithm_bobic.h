/* 
 * Encapsulates the algorithm of the Bobic robot that has a static ultro-sound distance meter HC-SR04 (Vally eyes).
 */
#include "movement_algorithm.h"
#include "distance_meter_sonar.h"
#include "chasis_four_wheels.h"
#include "neck.h"

class movement_algorithm_bobic : public movement_algorithm {
public:
  void init() {
    _distance_meter.init();
    _chasis.init();

    _chasis.stand_still();
  }
  
  void move() {
    int dist_to_move = 0;  

    int distance = _distance_meter.get_front();
    if (potentially_stuck(distance)) {
      Stuck_counter++;
    }
    else {
      Stuck_counter = 0;
    }

    if (Stuck_counter > 1) {
      Side_stuck_counter++;
      if (Side_stuck_counter == 2) {
        is_right_turn = !is_right_turn;
      }
  
      if (distance < 10) {
        _chasis.go_backward(20);
      }
      
      _chasis.turn_around_hard();
      Stuck_counter = 0;
      return;
    }

    if (distance > 30) {
      dist_to_move = distance;
    }
    else {
      if (is_right_turn)
        _chasis.turn_right();
      else
        _chasis.turn_left();
      return;
    }
    
    //int dist_to_move = _distance_meter.get_front();
    //Serial.println(dist_to_move);
    _chasis.go_forward(dist_to_move * 0.5); // 50% of measured distance to prevent collisions
    Dist_front_prev = distance;
  }

private:
  int Stuck_counter = 0;
  int Side_stuck_counter = 0;
  bool is_right_turn = true;

  distance_meter_sonar _distance_meter;
  chasis_four_wheels _chasis;
};