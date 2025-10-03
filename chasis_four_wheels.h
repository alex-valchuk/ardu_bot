/* 
 * Encapsulates the control of the chasis based on 4 independent wheels (1 motor per wheel).
 * Front and rear wheels are spinning to the oposite sides, therefore we can go in different directions.
 */
#include "chasis.h"
#include "motor.h"

class chasis_four_wheels : public chasis {
public:
  // Sets up the used pins for motors and for their speed.
  void init() {
    front_left_motor.init(front_left_motor_pin);
    front_right_motor.init(front_right_motor_pin);
    rear_left_motor.init(rear_left_motor_pin);
    rear_right_motor.init(rear_right_motor_pin);
    
    pinMode(Left_motors_speed_pin, OUTPUT);
    pinMode(Right_motors_speed_pin, OUTPUT);
  }

  void stand_still() {
    front_left_motor.idle();
    front_right_motor.idle();
    rear_left_motor.idle();
    rear_right_motor.idle();
  }
  
  void go_forward(double distance) {
    set_normal_speed();
    
    int time_for_move = calculate_time_for_direct_move(distance);
    forward();
    delay(time_for_move);
  }
  
  void go_backward(double distance) {
    set_max_speed();

    int time_for_move = calculate_time_for_direct_move(distance);
    backward();
    delay(time_for_move);
    
    set_normal_speed();
  }
  
  void go_left() {
    set_normal_speed();
    
    left();
    delay(Time_for_10cm);
  }
  
  void go_right() {
    set_normal_speed();
    
    right();
    delay(Time_for_10cm);
  }
  
  void go_forward_left() {
    set_normal_speed();
    
    forward_left();
    delay(Time_90 / 9);
  }
  
  void go_forward_right() {
    set_normal_speed();
    
    forward_right();
    delay(Time_90 / 9);
  }
  
  void turn_left() {
    set_normal_speed();
    
    left();
    delay(Time_90);
  }
  
  void turn_right() {
    set_normal_speed();
    
    right();
    delay(Time_90);
  }

  void turn_around() {
    set_normal_speed();
    
    backward();
    delay(Time_90);
    right();
    delay(Time_90);
  }

  void turn_around_hard() {
    set_max_speed();
    
    backward();
    delay(Time_90);
    right();
    delay(Time_90);

    set_normal_speed();
  }

private:
  // The pins our motors are connected to.
  const int front_left_motor_pin = 2, front_right_motor_pin = 7;
  const int rear_left_motor_pin = 4, rear_right_motor_pin = 8;
  
  // The speed of the motor depends on the value that was passed to the analogWrite function.
  // Remember the value of 'Motors_speed' can be between 0 and 255. 
  // If you pass 0, then the motors will stop and if you pass 255 then they will run at full speed.
  const int Left_motors_speed_pin = 3;
  const int Right_motors_speed_pin = 6;
  const int Motors_speed = 180;
  
  motor front_left_motor, front_right_motor;
  motor rear_left_motor, rear_right_motor;

  void set_normal_speed() {
    analogWrite(Left_motors_speed_pin, Motors_speed);
    analogWrite(Right_motors_speed_pin, Motors_speed);
  }

  void set_max_speed() {
    analogWrite(Left_motors_speed_pin, Motors_speed);
    analogWrite(Right_motors_speed_pin, Motors_speed);
  }

  int calculate_time_for_direct_move(double distance) {
    return Time_for_start_moving + distance * Time_for_1cm;
  }
  
  void forward() {
    front_left_motor.spin();
    front_right_motor.spin();
    rear_left_motor.idle();
    rear_right_motor.idle();
  }
  
  void forward_left() {
    front_left_motor.idle();
    front_right_motor.spin();
    rear_left_motor.idle();
    rear_right_motor.idle();
  }
  
  void forward_right() {
    front_left_motor.spin();
    front_right_motor.idle();
    rear_left_motor.idle();
    rear_right_motor.idle();
  }
  
  void left() {
    front_left_motor.idle();
    front_right_motor.spin();
    rear_left_motor.spin();
    rear_right_motor.idle();
  }
  
  void right() {
    front_left_motor.spin();
    front_right_motor.idle();
    rear_left_motor.idle();
    rear_right_motor.spin();
  }
  
  void backward() {
    front_left_motor.idle();
    front_right_motor.idle();
    rear_left_motor.spin();
    rear_right_motor.spin();
  }
  
  void backward_left() {
    front_left_motor.spin();
    front_right_motor.idle();
    rear_left_motor.idle();
    rear_right_motor.spin();
  }
  
  void backward_right() {
    front_left_motor.idle();
    front_right_motor.spin();
    rear_left_motor.spin();
    rear_right_motor.idle();
  }
};
