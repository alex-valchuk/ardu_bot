/* 
 * Encapsulates the algorithm of the Bobic robot that has a static ultro-sound distance meter HC-SR04 (Vally eyes).
 */
#include "movement_algorithm.h"
#include "distance_meter_sonar.h"
//#include "chasis_four_wheels.h"
#include "chasis_two_front_wheels.h"
//#include "neck.h"

class movement_algorithm_bobic : public movement_algorithm {
public:
  void init() {
    _distance_meter.init();
    _chasis.init();

    _chasis.stand_still();
  }
  
  void move() {
    _chasis.stand_still();
    int dist_to_move = 0;  

    int distance = _distance_meter.get_front();
    String str = "distance: ";
    str.concat(distance);
    Serial.println(str);

    str = "Dist_front_prev: ";
    str.concat(Dist_front_prev);
    Serial.println(str);

    if (potentially_stuck(distance)) {
      Stuck_counter = Stuck_counter + 1;
      str = "potentially_stuck: ";
      str.concat(Stuck_counter);
      Serial.println(str);
    }
    else {
      Stuck_counter = 0;
    }
    //Stuck_counter = 1;//temp
    if (Stuck_counter > 1) {
      Side_stuck_counter++;
      if (Side_stuck_counter == 2) {
        is_right_turn = !is_right_turn;
      }
  
      str = "distance < 20 == ";
      str.concat(distance < 20);
      Serial.println(str);

      if (distance < 20) {
        Serial.println("go_backward(50)");

        //_chasis.set_max_speed();
        _chasis.go_backward(30);
      }
      
      // turn around hard
      _chasis.turn_around();
      //_chasis.set_normal_speed();
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
    }
    
    //dist_to_move = _distance_meter.get_front();
    str = "dist_to_move: ";
    str.concat(dist_to_move);
    Serial.println(str);
    _chasis.go_forward(dist_to_move * 0.85); // 85% of measured distance to prevent collisions

    Dist_front_prev = distance;
  }

private:
  int Stuck_counter = 0;
  int Side_stuck_counter = 0;
  bool is_right_turn = true;

  distance_meter_sonar _distance_meter;
  chasis_two_front_wheels _chasis;
  //chasis_four_wheels _chasis;
};