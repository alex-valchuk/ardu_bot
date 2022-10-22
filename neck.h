#include <Servo.h>

const int Time_for_neck_step_rotation = 100;

Servo neck_servo;

class neck {
public:
  void init(int pin) {
    neck_servo.attach(pin);
  }

  void rotate(int angle) {
    int rotation_step = current_neck_angle > angle
      ? -10
      : 10;
      
    while (current_neck_angle != angle) {
      current_neck_angle += rotation_step;
      neck_servo.write(current_neck_angle);
      delay(Time_for_neck_step_rotation);
    }
  }
private:
  int current_neck_angle = 90;
};
