const int JoyStick_pin = 2;
const int X_pin = A1;
const int Y_pin = A0;

uint8_t Player_x = 64;
uint8_t Player_y = 32;
char state = 'S';
unsigned long prevTimeButton = 0;
unsigned long prevTimeDeboundce = 0;


void ReadJoy() {
  int readX, readY, x, y;
  x = analogRead(X_pin);
  y = analogRead(Y_pin);

  readX = map(x, 0, 1023, 0, 2);
  readY = map(y, 0, 1023, 0, 2);

  // Serial.print(readX);
  // Serial.print(" , ");
  // Serial.print(readY);
  // Serial.println();

  if (readX != 1 || readY != 1) {
    if (readY == 0) {
      state = 'U';
    } else if (readY == 2) {
      state = 'D';
    } else if (readX == 0) {
      state = 'L';
    } else if (readX == 2) {
      state = 'R';
    }
  }
}

bool Deboundce(int Pin) {
  static unsigned long current_time;
  char sw;
  sw = digitalRead(Pin);
  if (sw) {
    return false;
  } else {
    current_time = millis();
    if ((current_time - prevTimeDeboundce) > 25) {
      prevTimeDeboundce = millis();
      return true;
    } else {
      prevTimeDeboundce = millis();
      return false;
    }
  }
}

void controller() {
  if ((millis() - prevTimeButton) > 500) {
    prevTimeButton = millis();
    ReadJoy();
  }

  // if(state != 'S'){
  //   Serial.println(state);
  // }

  if (state == 'D') {
    selectedOption++;
    if (selectedOption > 2) {
      selectedOption = 1;
    }

    state = 'S';

  }

  if (state == 'U') {
    selectedOption--;
    if (selectedOption < 1) {
      selectedOption = 2;
    }

    state = 'S';
  }

  if(Deboundce(4)){
    gameMode = selectedOption;
  }

  // Serial.println(selectedOption);
}
