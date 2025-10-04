/* 
 * Encapsulates the algorithm of the Bobic robot that has a static ultro-sound distance meter HC-SR04 (Vally eyes).
 */
#include "movement_algorithm.h"
#include "distance_meter_sonar.h"
//#include "chasis_four_wheels.h"
//#include "chasis_two_front_wheels.h"
#include "chasis_four_wheels.h"
#include "neck.h"

class movement_algorithm_test : public movement_algorithm {
public:
  void init() {
    _distance_meter.init();
    _chasis.init();

    _chasis.stand_still();
  }
  
  void move() {
    int dist_to_move = 200;  

    _chasis.go_forward(dist_to_move);
    _chasis.go_backward(dist_to_move);
    /*_chasis.go_left();
    delay(2000);
    _chasis.go_right();
    delay(2000);
    _chasis.go_forward_left();
    delay(2000);
    _chasis.go_forward_right();
    delay(2000);
    _chasis.turn_left();
    delay(2000);
    _chasis.turn_right();
    delay(2000);
    _chasis.turn_around();*/
  }

private:
  distance_meter_sonar _distance_meter;
  //chasis_two_front_wheels _chasis;
  chasis_four_wheels _chasis;
};