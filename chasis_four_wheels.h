#include "motor.h"
#include "chasis.h"

// The speed of the motor depends on the value that was passed to the analogWrite function.
// Remember the value of 'Motors_speed' can be between 0 and 255. 
// If you pass 0, then the motors will stop and if you pass 255 then they will run at full speed.
const int Left_motors_speed_pin = 3;
const int Right_motors_speed_pin = 6;
const int Motors_speed = 180;

// implements the control of the chasis based on 4 independent wheels (motor per wheel)
class chasis_four_wheels : public chasis {
public:
  // sets up the used pins
  void init() {
    setup_motor_system(2, 4, 7, 8);
    
    pinMode(Left_motors_speed_pin, OUTPUT);
    pinMode(Right_motors_speed_pin, OUTPUT);
  }
  
  void go_forward(double distance) {
    set_speed();
    
    int time_for_move = calculate_time_for_direct_move(distance);
    forward();
    delay(time_for_move);
  }
  
  void go_backward(double distance) {
    set_speed();
    
    int time_for_move = calculate_time_for_direct_move(distance);
    backward();
    delay(time_for_move);
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

  void turn_around() {
    set_speed();
    
    backward();
    delay(Time_90);
    right();
    delay(Time_90);
  }
private:
  void set_speed() {
    analogWrite(Left_motors_speed_pin, Motors_speed);
    analogWrite(Right_motors_speed_pin, Motors_speed);
  }

  int calculate_time_for_direct_move(double distance) {
    return Time_for_start_moving + distance * Time_for_1cm;
  }
};
