
#include <avr/sleep.h>

//  MARK: - Ports reference
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
const int Mode = A0;

const int buttonsCount = 12;  // SEGA 6-buttons

//  MARK: - buttonsData index reference
/*
 0 - Up
 1 - Left
 2 - Right
 3 - Down
 4 - A
 5 - B
 6 - C
 7 - X
 8 - Y
 9 - Z
 10 - Mode
 11 - Start
 */
int buttonsData[buttonsCount];
int messageLength = 0;

//  MARK: - BT Power ext port // TODO

//  MARK: - For send data to BT module (Serial port)
uint32_t buttonState = 0;
int8_t x1 = 0;
int8_t y1 = 0;

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
  
  // Debug to console
  Serial.begin(9600); 
}

void readButtons() {
    // fiil high 
    for (int index = 0; index < buttonsCount; index++) {
      buttonsData[index] = 1;
    }
    
    // UP
    if (digitalRead(Up) == 0) {
      buttonsData[0] = 0;
    }
    // LEFT
    if (digitalRead(Left) == 0) {
      buttonsData[1] = 0;
    }
    // RIGHT
    if (digitalRead(Right) == 0) {
      buttonsData[2] = 0;
    }
    // DOWN
    if (digitalRead(Down) == 0) {
      buttonsData[3] = 0;
    }
    // A
    if (digitalRead(A) == 0) {
      buttonsData[4] = 0;
    }
    // B
    if (digitalRead(B) == 0) {
      buttonsData[5] = 0;
    }
    // C
    if (digitalRead(C) == 0) {
      buttonsData[6] = 0;
    }
    // X
    if (digitalRead(X) == 0) {
      buttonsData[7] = 0;
    }
    // Y
    if (digitalRead(Y) == 0) {
      buttonsData[8] = 0;
    }
    // Z
    if (digitalRead(Z) == 0) {
      buttonsData[9] = 0;
    }
    // MODE
    if (digitalRead(Mode) == 0) {
      buttonsData[10] = 0;
    }
    // START
    if (digitalRead(Start) == 0) {
      buttonsData[11] = 0;
    }
}
//  MARK: - Debug print to console
void printToSetial() {
  if (buttonsData[0] == 0) {
    Serial.println("Up");
  }
  
  if (buttonsData[1] == 0) {
    Serial.println("Left");
  }
  
  if (buttonsData[2] == 0) {
    Serial.println("Right");
  }
  
  if (buttonsData[3] == 0) {
    Serial.println("Down");
  }
  
  if (buttonsData[4] == 0) {
    Serial.println("A");
  }
  
  if (buttonsData[5] == 0) {
    Serial.println("B");
  }
  
  if (buttonsData[6] == 0) {
    Serial.println("C");
  }
  
  if (buttonsData[7] == 0) {
    Serial.println("X");
  }
  
  if (buttonsData[8] == 0) {
    Serial.println("Y");
  }
  
  if (buttonsData[9] == 0) {
    Serial.println("Z");
  }
  
  if (buttonsData[10] == 0) {
    Serial.println("Mode");
  }
  
  if (buttonsData[11] == 0) {
    Serial.println("Start");
  }
}

//  MARK: - preparing hid message
void sendHidMessage() {
  x1 = 0;
  y1 = 0;
  buttonState = 0;
  messageLength = 0;
  
  // MARK: - Directions
  
  //  UP + RIGHT
  if (buttonsData[0] == 0 && buttonsData[2] == 0) {
    messageLength = 1;
    x1 = 127;
    y1 = -127;
  } 
  //  UP+LEFT
  else if (buttonsData[0] == 0 && buttonsData[1] == 0) {
    messageLength = 1;
    x1 = -127;
    y1 = -127;
  }
  //  DOWN+RIGHT
  else if (buttonsData[3] == 0 && buttonsData[2] == 0) {
    messageLength = 1;
    x1 = 127;
    y1 = 127;
  }
  //  DOWN+LEFT
  else if (buttonsData[3] == 0 && buttonsData[1] == 0) {
    messageLength = 1;
    x1 = -127;
    y1 = 127;
  }
  //  UP
  else if (buttonsData[0] == 0) {
    messageLength = 1;
    y1 = -127;
  }
  //  DOWN
  else if (buttonsData[3] == 0) {
    messageLength = 1;
    y1 = 127;
  }
  //  LEFT
  else if (buttonsData[1] == 0) {
    messageLength = 1;
    x1 = -127;
  }
  //  RIGHT
  else if (buttonsData[2] == 0) {
    messageLength = 1;
    x1 = 127;
  }

  //  MARK: - Buttons

  //  A
  if (buttonsData[4] == 0) {
    messageLength = 1;
    buttonState |= (1 << 0);
  }
  //  B
  if (buttonsData[5] == 0) {
    messageLength = 1;
    buttonState |= (1 << 1);
  }
  //  C
  if (buttonsData[6] == 0) {
    messageLength = 1;
    buttonState |= (1 << 2);
  }
  //  X
  if (buttonsData[7] == 0) {
    messageLength = 1;
    buttonState |= ( 1 << 3);
  }
  //  Y
  if (buttonsData[8] == 0) {
    messageLength = 1;
    buttonState |= (1 << 4);
  }
  //  Z
  if (buttonsData[9] == 0) {
    messageLength = 1;
    buttonState |= (1 << 5);
  }
  //  MODE
  if (buttonsData[10] == 0) {
    messageLength = 1;
    buttonState |= (1 << 12);
  }
  //  START
  if (buttonsData[11] == 0) {
    messageLength = 1;
    buttonState |= (1 << 11);
  }

  if (messageLength >= 1) {
    
    Serial.write((uint8_t)0xFD);  //  Start HID Report
    Serial.write((uint8_t)0x06);  //  Length Byte
    //  1. X/Y-Axis
    Serial.write((uint8_t)x1);    //  First X coordinate
    Serial.write((uint8_t)y1);    //  First Y coordinate
    //  2. X/Y-Axis
    Serial.write((uint8_t)0x00);  //  Second X coordinate
    Serial.write((uint8_t)0x00);  //  Second Y coordinate
    // 3. Buttons
    uint8_t buttonState1 = buttonState & 0xFF;
    uint8_t buttonState2 = (buttonState >> 8) & 0xFF;
    //  Send
    Serial.write((uint8_t)buttonState1);  //  First byte (Buttons 1-8)
    Serial.write((uint8_t)buttonState2);  //  Second byte (Buttons 9-16)
    
  } else {
    
    Serial.write((uint8_t)0xFD);  //  Start HID Report
    Serial.write((uint8_t)0x06);  //  Length Byte
    //  1. X/Y-Axis
    Serial.write((uint8_t)0x00);  //  First X coordinate
    Serial.write((uint8_t)0x00);  //  First Y coordinate
    //  2. X/Y-Axis
    Serial.write((uint8_t)0x00);  //  Second X coordinate
    Serial.write((uint8_t)0x00);  //  Second Y coordinate
    // 3. Buttons
    Serial.write((uint8_t)0x00);  //  First byte (Buttons 1-8)
    Serial.write((uint8_t)0x00);  //  Second byte (Buttons 9-16)
  }
}

void loop() {

  readButtons();
  delay(16.7);
  printToSetial();
//  sendHidMessage();
}
