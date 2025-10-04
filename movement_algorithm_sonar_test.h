/* 
 * Encapsulates the algorithm for testing a static ultro-sound distance meter HC-SR04 (Vally eyes).
 */
#include "movement_algorithm.h"
#include "distance_meter_sonar.h"
#include "neck.h"

class movement_algorithm_sonar_test : public movement_algorithm {
public:
  void init() {
    _distance_meter.init();
  }
  
  void move() {
    int dist = _distance_meter.get_front();
    Serial.println(dist);
    delay(1000);
  }

private:
  distance_meter_sonar _distance_meter;
};