#include "moments.h"
//#include "movement_algorithm_with_neck.h"
#include "movement_algorithm_bobic.h"

//movement_algorithm_with_neck _movement_algorithm;
movement_algorithm_bobic _movement_algorithm;

void setup()
{
  Serial.begin(9600);

  _movement_algorithm.init();
}

void loop()
{
  _movement_algorithm.move();
}
