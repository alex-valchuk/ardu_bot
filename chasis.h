/*
 * Describes the baseline contract for controlling the chasis of the robot.
 */
class chasis {
public:
  virtual void init();
  virtual void stand_still();
  virtual void go_forward(double distance);
  virtual void go_backward(double distance);
  virtual void go_left();
  virtual void go_right();
  virtual void go_forward_left();
  virtual void go_forward_right();
  virtual void turn_left();
  virtual void turn_right();
  virtual void turn_around();
};
