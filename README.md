**Introduction**\
This is a refactored firmware for Arduino UNO robot that I made following the [Michail Momot](https://vk.com/momotmvu) book:\
https://www.litres.ru/book/mihail-momot/mobilnye-roboty-na-baze-arduino-23878269/

The main (though extremely simple) logic is located within ardu_bot.ino file.

**Movement:**\
Though, it is oriented for four wheel chasis, the abstractions allow to adapt it to any type of chasis.\
You just need to provide your own implementation of chasis.h looking at the existing example: chasis_four_wheels.h

**Orientation:**\
The orientation is implemented with rotated ultro-sound distance meter HC-SR04 (Vally eyes).\
But you can exchange it with anything else providing the alternative implementation of distance_meter.h
