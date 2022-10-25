/* 
 * Encapsulates the distance measurements based on the ultro-sound distance meter HC-SR04 (Vally eyes) which is set on top of the spinning servo.
 * It requires some time to spin from left to right and then back to the center. Please keep it in mind designing your logic.
 * The distance the HC-SR04 is able to measure is limited by 400 cm.
 */
#include "distance_meter.h"
#include "sonar.h"
#include "neck.h"

class distance_meter_sonar : public distance_meter {
public:
  void init() {
    _sonar.init(Sonar_trig_pin, Sonar_echo_pin);
    _neck.init(Neck_pin);
  }
  
  int get_front() {
    return measure_dist(Front_ang);
  }
  
  int get_left() {
    int dist = measure_dist(Left_ang);
    look_ahead(); // returns to the initial position just not to look oddly
    return dist;
  }
  
  int get_right() {
    int dist = measure_dist(Right_ang);
    look_ahead(); // returns to the initial position just not to look oddly
    return dist;
  }

private:
  int measure_dist(int angle) {
    _neck.rotate(angle);
    return _sonar.measure_dist(Max_dist);
  }

  int look_ahead() {
    _neck.rotate(Front_ang);
  }

  sonar _sonar;
  neck _neck;
  const int Sonar_trig_pin = 13;
  const int Sonar_echo_pin = 12;
  const int Neck_pin = 14;
  const int Max_dist = 400;

  const int Left_ang = 160;
  const int Front_ang = 90;
  const int Right_ang = 20;
};
