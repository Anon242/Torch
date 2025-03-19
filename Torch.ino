#include <iarduino_NeoPixel.h>
uint8_t stepp = 0, stBY = 0;
uint8_t lines[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t linesNew[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t green = 0;
iarduino_NeoPixel led(18, 144); //Инициализируем ленту
#define STEP_4 0xFFFFFFF4UL
#define STEP_2 0xFFFFFFF2UL
#define STEP_128 0xFFFFFF40UL

void setup()
{
  DDRC = 0b00001111;
  DDRD = 0b01111100;
  DDRB = 0b00000000;
  PORTC |= 0b00100000;
  led.begin();
  delay(100);
}
void loop()
{
  static volatile unsigned long t2 = 0, p2 = 0;
  t2 = millis();
  if (((t2 & STEP_2) != (p2 & STEP_2)))
  {
    stepp++;
    if (stepp > 17)
    {
      for (int m = 0; m < 9; m++) linesNew[m] = random(0, stBY / 100);
      stepp = 0;
      if ((PINC & 0x20) > 0 && stBY < 1700) stBY += 10;
      else if ((PINC & 0x20) == 0 && stBY) stBY--;
    }
    for (int m = 0; m < 9; m++)
    {
      if (lines[m] > linesNew[m]) lines[m]--;
      else if (lines[m] < linesNew[m]) lines[m]++;
      else lines[m] = linesNew[m];
    }
    green = random(20, 70);
    p2 = t2;
  }
  if (stBY > 10)ledUpdate();
}
void ledUpdate()
{
  for (int i = 1; i < 10; i++)
  {
    for (int i1 = 1; i1 < 17; i1++)
    {
      if (i1 <= lines[i - 1])
      {
        if (i % 2 == 0) {
          led.setColor((i * 16) - (i1), 255, green, 0);
        } else {
          led.setColor((i * 16) - (16 - i1) - 1, 255, green, 0);
        }
      }
      else
      {
        if (i % 2 == 0) {
          led.setColor((i * 16) - (i1), 0, 0, 0);
        } else {
          led.setColor((i * 16) - (16 - i1) - 1, 0, 0, 0);
        }

      }
    }
  }

led.write();
}
