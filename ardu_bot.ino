#include <Servo.h>
#include "motor.h"
#include "sonar.h"

const int Max_dist = 300;

// The speed of the motor depends on the value that was passed to the analogWrite function.
// Remember the value of 'Motors_speed' can be between 0 and 255. 
// If you pass 0, then the motors will stop and if you pass 255 then they will run at full speed.
const int Left_motors_speed_pin = 3;
const int Right_motors_speed_pin = 6;
const int Motors_speed = 127;

const int left_ang = 160;
const int between_left_and_front_ang = 125;
const int front_ang = 90;
const int between_right_and_front_ang = 55;
const int right_ang = 20;

const int time_90 = 390;
const int time_180 = 750;
const int time_for_start_moving = 100;
const int time_for_1cm = 10;
const int time_for_neck_step_rotation = 100;

int stuck_counter = 0;
int dist_front_prev = 0;

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
    delay(time_for_neck_step_rotation);
  }
}

int measure_dist(int angle) {
  rotate_neck(angle);
  return measure_dist_with_sonar(Max_dist);
}

void turn_around() {
  backward();
  delay(time_90);
  right();
  delay(time_90);
}

bool between(int a, int b, int accuracy) {
  return a - accuracy < b && b < a + accuracy;
}

bool potentially_stuck(int Dist_front) {
  return 
    Dist_front == dist_front_prev
    || between(Dist_front, dist_front_prev, 5);
}

void loop()
{
  _stop();
  analogWrite(Left_motors_speed_pin, Motors_speed);
  analogWrite(Right_motors_speed_pin, Motors_speed);
    
  int dist_to_move = 0;  

  int Dist_front = measure_dist(front_ang);
  if (potentially_stuck(Dist_front)) {
    stuck_counter++;
  }
  else {
    stuck_counter = 0;
  }

  if (stuck_counter > 1) {
    turn_around();
    stuck_counter = 0;
    return;
  }

  if (Dist_front > 30) {
    dist_to_move = Dist_front;
  }
  else {
    int Dist_left = measure_dist(left_ang);
    int Dist_right = measure_dist(right_ang);
  
    rotate_neck(front_ang); // to always look forward
  
    if ((Dist_left > Dist_front) && (Dist_left > Dist_right))
    {
      left();
      delay(time_90);
      dist_to_move = Dist_left;
    }
    else if (Dist_right > Dist_front)
    {
      right();
      delay(time_90);
      dist_to_move = Dist_right;
    }
    else
    {
      right();
      delay(time_180);
    }
  }
  
  double dist = dist_to_move * 0.85;
  int time_for_move = time_for_start_moving + dist * time_for_1cm;
  forward();
  delay(time_for_move);
  
  dist_front_prev = Dist_front;
}
