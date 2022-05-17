int Trig_pin;
int Echo_pin;

void Sonar_init(int trig, int echo)
{
   Trig_pin = trig;
   Echo_pin = echo;

   pinMode(Trig_pin, OUTPUT);
   pinMode(Echo_pin, INPUT);
}

int measure_dist_with_sonar(unsigned long Limit)
{
  int Long_cm;
  unsigned long Lim = Limit * 58;

  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  
  Long_cm = int(pulseIn(Echo_pin, HIGH, Lim) / 58);
  
  if(Long_cm == 0) {
    return int(Limit);
  }
  
  return Long_cm;
}
