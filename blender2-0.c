#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OFF 0
#define SPEED1 1
#define SPEED2 2
#define SPEED3 3
#define VARIANT 4

#define time_used(start, end) ((double)(end - start) / CLOCKS_PER_SEC)
#define calcPeriod(seconds) (((double)1 / seconds))

int setSpeed(char s);
void blender();

int main() {

  blender();

  return EXIT_SUCCESS;
}

int setSpeed(char s) {
  int speed;

  switch (s) {

  case '0':
    speed = OFF;
    break;

  case '1':
    speed = SPEED1;
    break;

  case '2':
    speed = SPEED2;
    break;

  case '3':
    speed = SPEED3;
    break;

  case 'p':
  case 'P':
    speed = VARIANT;
    break;

  default:
    return -1;
  }
  return speed;
}

void blender() {
  char *ledOn = "LED-ON";
  char *ledOff = "LED-OFF";
  bool on = false;
  int speed = 0;
  char pressed;
  clock_t start_time;
  double timeOn;
  bool t = false;
  // siempre checando si se presiona un a tecla
  while (true) {

    while (on) {

      if (speed == SPEED1) {
        timeOn = calcPeriod(1) / 2;
      } else if (speed == SPEED2) {
        timeOn = calcPeriod(1 / 2) / 2;
      } else if (speed == SPEED3) {
        timeOn = calcPeriod(1 / 3) / 2;
      } else if (speed == VARIANT) {

      } else if (speed == OFF) {
        on = false;
      }

      if (time_used(start_time, clock()) <= timeOn) {
        if (!t) {
          system("cls");
          printf("%s %f", ledOn,time_used(start_time, clock()));
          t = true;
        }

      } else if (time_used(start_time, clock()) <= (timeOn * 2)) {

        if (t) {
          t = false;
          system("cls");
          printf("%s %f", ledOff,time_used(start_time, clock()));
        }

      } else {
        start_time = clock();
      }

      if (kbhit()) {
        pressed = getch();
        if (setSpeed(pressed) != -1) {
          start_time = clock();
          speed = setSpeed(pressed);
        }
      }
    }

    if (kbhit()) {
      pressed = getch();
      speed = setSpeed(pressed);
      if (speed != -1) {
        on = true;
        start_time = clock();
      }
    }
  }
}
