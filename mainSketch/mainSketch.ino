
#include <avr/sleep.h>

uint32_t btnState = 0;
int8_t x1 = 0;
int8_t y1 = 0;

const int Start = 2;
const int Up = 3;
const int Left = 4;
const int Right = 5;
const int Down = 6;
const int A = 7;
const int B = 8;
const int C = 9;
const int X = 10;
const int Y = 11;
const int Z = 12;
const int Mode = 13;

//int buttonState = 0;

//rest for bt power.


void setup() {
  pinMode(Start, INPUT_PULLUP);
  pinMode(Up, INPUT_PULLUP);
  pinMode(Left, INPUT_PULLUP);
  pinMode(Right, INPUT_PULLUP);
  pinMode(Down, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(Mode, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(A);

  if (buttonState == LOW) {
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(16.7);
}
