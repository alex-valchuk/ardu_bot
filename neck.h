#include <Servo.h>

const int Time_for_neck_step_rotation = 100;

int current_neck_angle = 90;

Servo neck;

void Neck_init(int pin) {
  neck.attach(pin);
}

void rotate_neck(int angle) {
  int rotation_step = current_neck_angle > angle
    ? -10
    : 10;
    
  while (current_neck_angle != angle) {
    current_neck_angle += rotation_step;
    neck.write(current_neck_angle);
    delay(Time_for_neck_step_rotation);
  }
}
