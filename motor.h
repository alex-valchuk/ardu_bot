/*
 * Encapsulates the control of the motor connected to the passing pin.
 */
class motor {
public:
  void init(int pin) {
    _pin = pin;

    pinMode(_pin, OUTPUT);
  }

  void spin() {
    digitalWrite(_pin, HIGH);
  }

  void idle() {
    digitalWrite(_pin, LOW);
  }
private:
  int _pin;
};
