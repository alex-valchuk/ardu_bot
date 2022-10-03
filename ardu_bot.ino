#include <Servo.h>
#include "motor.h"
#include "sonar.h"

const int Max_dist = 300;

// The speed of the motor depends on the value that was passed to the analogWrite function.
// Remember the value of 'Motors_speed' can be between 0 and 255. 
// If you pass 0, then the motors will stop and if you pass 255 then they will run at full speed.
const int Left_motors_speed_pin = 3;
const int Right_motors_speed_pin = 6;
const int Motors_speed = 180;

const int Left_ang = 160;
const int Between_left_and_front_ang = 125;
const int Front_ang = 90;
const int between_right_and_front_ang = 55;
const int Right_ang = 20;

const int Time_90 = 390;
const int Time_180 = 750;
const int Time_for_start_moving = 100;
const int Time_for_1cm = 10;
const int Time_for_neck_step_rotation = 100;

int Dist_front_prev = 0;

Servo neck;
int current_neck_angle = 90;

void setup()
{
  Sonar_init(13, 12);

  neck.attach(14);

  setup_motor_system(2, 4, 7, 8);
  
  pinMode(Left_motors_speed_pin, OUTPUT);
  pinMode(Right_motors_speed_pin, OUTPUT);

  _stop();
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

int measure_dist(int angle) {
  rotate_neck(angle);
  return measure_dist_with_sonar(Max_dist);
}

void turn_around() {
  backward();
  delay(Time_90);
  right();
  delay(Time_90);
}

bool between(int a, int b, int accuracy) {
  return a - accuracy < b && b < a + accuracy;
}

bool potentially_stuck(int dist_front) {
  return
    dist_front < 5
    && (dist_front == Dist_front_prev
    || between(dist_front, Dist_front_prev, 5));
}

void loop()
{
  _stop();
  analogWrite(Left_motors_speed_pin, Motors_speed);
  analogWrite(Right_motors_speed_pin, Motors_speed);
    
  int dist_to_move = 0;  

  int dist_front = measure_dist(Front_ang);
  if (potentially_stuck(dist_front)) {
    turn_around();
    return;
  }

  if (dist_front > 30) {
    dist_to_move = dist_front;
  }
  else {
    int dist_left = measure_dist(Left_ang);
    int dist_right = measure_dist(Right_ang);
  
    rotate_neck(Front_ang); // to always look forward
  
    if ((dist_left > dist_front) && (dist_left > dist_right))
    {
      left();
      delay(Time_90);
      dist_to_move = dist_left;
    }
    else if (dist_right > dist_front)
    {
      right();
      delay(Time_90);
      dist_to_move = dist_right;
    }
    else
    {
      right();
      delay(Time_180);
    }
  }
  
  double dist = dist_to_move * 0.85;
  int time_for_move = Time_for_start_moving + dist * Time_for_1cm;
  forward();
  delay(time_for_move);
  
  Dist_front_prev = dist_front;
}
