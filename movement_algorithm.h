/*
 * Describes the baseline contract for moving the robot.
 */
class movement_algorithm {
public:
  virtual void init();
  virtual void move();

protected:
  int Dist_front_prev = 0;

  bool between(int a, int b, int accuracy) {
    return a - accuracy <= b && b <= a + accuracy;
  }

  bool potentially_stuck(int dist_front) {
    return
      dist_front < 3
      || between(dist_front, Dist_front_prev, 5)
      || between(Dist_front_prev, dist_front, 5);
  }
};
