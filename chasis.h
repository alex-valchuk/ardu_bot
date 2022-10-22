#include "motor.h"

// The speed of the motor depends on the value that was passed to the analogWrite function.
// Remember the value of 'Motors_speed' can be between 0 and 255. 
// If you pass 0, then the motors will stop and if you pass 255 then they will run at full speed.
const int Left_motors_speed_pin = 3;
const int Right_motors_speed_pin = 6;
const int Motors_speed = 180;

class chasis {
public:
  void init() {
    setup_motor_system(2, 4, 7, 8);
    
    pinMode(Left_motors_speed_pin, OUTPUT);
    pinMode(Right_motors_speed_pin, OUTPUT);
  }

  void turn_around() {
    set_speed();
    
    backward();
    delay(Time_90);
    right();
    delay(Time_90);
  }
  
  void go_forward(int time) {
    set_speed();
    
    forward();
    delay(time);
  }
  
  void go_backward() {
    set_speed();
    
    backward();
    delay(Time_90);
  }
  
  void go_forward_left() {
    set_speed();
    
    forward_left();
    delay(Time_90 / 9);
  }
  
  void go_forward_right() {
    set_speed();
    
    forward_right();
    delay(Time_90 / 9);
  }
  
  void go_left() {
    set_speed();
    
    left();
    delay(Time_for_10cm);
  }
  
  void go_right() {
    set_speed();
    
    right();
    delay(Time_for_10cm);
  }
  
  void turn_left() {
    set_speed();
    
    left();
    delay(Time_180);
  }
  
  void turn_right() {
    set_speed();
    
    right();
    delay(Time_180);
  }
private:
  void set_speed() {
    analogWrite(Left_motors_speed_pin, Motors_speed);
    analogWrite(Right_motors_speed_pin, Motors_speed);
  }
};
