
#include <avr/sleep.h>

//  MARK: - Ports reference
const uint8_t Start = 2;
const uint8_t Up = 3;
const uint8_t Left = 4;
const uint8_t Right = 5;
const uint8_t Down = 6;
const uint8_t A = 7;
const uint8_t B = 8;
const uint8_t C = 9;
const uint8_t X = 10;
const uint8_t Y = 11;
const uint8_t Z = 12;
const uint8_t Mode = A0;

const uint8_t bluetoothEnable = A1; // Pin for control BlueTooh module power

const uint8_t buttonsCount = 12;  // SEGA 6-buttons

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
uint8_t buttonsData[buttonsCount];
int messageLength = 0;

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

  // Handling Key pin on HC-05 -> High level for enable it
  pinMode(bluetoothEnable, OUTPUT);
  
  Serial.begin(9600); 
  delay(500);
  digitalWrite(bluetoothEnable, 1);
}

// Sleep mode for low power idle
void goSleep() {
  sleep_enable();                   //Enable sleep
  attachInterrupt(0, wakeUp, LOW);  //Set interrupt for pin2(start button)
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(bluetoothEnable, 0);// Power off BT
  sleep_cpu();
}

void wakeUp() {
  digitalWrite(bluetoothEnable, 1);
  sleep_disable();
  detachInterrupt(0);
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

    //  SLEEP-COMBO = A+Z+MODE+Left
    if (digitalRead(A) == 0 && 
        digitalRead(Z) == 0 && 
        digitalRead(Mode) == 0 && 
        digitalRead(Left) == 0) 
        {
          goSleep();
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
  sendHidMessage();
   delay(13);
}
