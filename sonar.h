class sonar {
private:
  int _trig_pin;
  int _echo_pin;
  int _last_recorded_dist = 10;
public:
  void init(int trigPin, int echoPin) {
     _trig_pin = trigPin;
     _echo_pin = echoPin;
  
     pinMode(_trig_pin, OUTPUT);
     pinMode(_echo_pin, INPUT);
  }
  
  int measure_dist(unsigned long limit) {
    int long_cm;
    unsigned long lim = limit * 58;
  
    digitalWrite(_trig_pin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig_pin, LOW);
    
    long_cm = int(pulseIn(_echo_pin, HIGH, lim) / 58);
    
    if(long_cm <= 0 || long_cm > limit) {
      //sometimes it returns > 50_000 value which is impossible
       //let's consider the distance became smaller
      return _last_recorded_dist - _last_recorded_dist * 0.3;
    }
    
    _last_recorded_dist = int(long_cm);
    return _last_recorded_dist;
  }
};
