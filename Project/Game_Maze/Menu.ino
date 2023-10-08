bool sec = false;
bool setstateone = true;
bool setstatetwo = false;
int i;

void sercorTriangleDown(uint8_t x, uint8_t y) {
  display.fillTriangle(x, y, x - 3, y - 3, x + 3, y - 3, WHITE);
}

void sercorTriangleUP(uint8_t x, uint8_t y) {
  display.fillTriangle(x, y, x + 3, y + 3, x - 3, y + 3, WHITE);
}

void cursor_Blink(int x, int y) {
  uint8_t font;
  if ((millis() - prevTimeblink) > 800) {
    prevTimeblink = millis();
    sec = !sec;
  }

  if (sec == 1) {
    font = BLACK;
  } else {
    font = WHITE;
  }

  display.setCursor(x, y);
  display.setTextColor(font);
  display.cp437(true);
  display.write(0x10);
  display.setTextColor(WHITE);
}

void mainMenu() {

  if (selectedOption == 1) {
    cursor_Blink(35, 32);
    display.setCursor(50, 32);
  } else {
    display.setCursor(35, 32);
  }
  display.print("Start");
  display.setTextSize(1);

  if (selectedOption == 2) {
    cursor_Blink(35, 44);
    display.setCursor(47, 44);
  } else {
    display.setCursor(35, 44);
  }

  display.print("Setting");
  display.setTextSize(1);

  if (Deboundce(ButtonA) or Deboundce(JoyStick_pin)) {
    gameMode = selectedOption;
    if (Modegame == 1 && selectedOption == 1) {
      gamePause = false;
      generateMaze();
    }

    if (Modegame == 2 && selectedOption == 1) {
      gamePause = false;
    }

    selectedOption = 1;
  }
}

void gameMenu() {
  display.fillRect(24, 8, 80, 45, WHITE);
  display.fillRect(25, 9, 78, 43, BLACK);
  display.setTextColor(BLACK);
  display.fillRect(26, 10, 76, 11, WHITE);
  display.setCursor(48, 12);

  display.print("PAUSED");
  display.setTextColor(WHITE);

  display.setCursor(48, 24);
  display.print("resume");
  if (selectedOption == 1) {
    cursor_Blink(33, 24);
  }

  display.setCursor(48, 34);
  display.print("quit");
  if (selectedOption == 2) {
    cursor_Blink(33, 34);
  }
}

void setting() {
  display.fillRect(10, 0, 107, 10, WHITE);
  display.drawRect(10, 10, 107, 53, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(22, 2);
  display.print("Setting Option");
  display.setTextSize(1);

  if ((millis() - prevSetCursor) > 50) {
    prevSetCursor = millis();
    i < 6 ? i++ : i = 0;
  }

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(38, 18);
  display.print("Game Mode");
  // display.print("Time Mode");
  if (!setSelect) {
    display.setCursor(95 + i, 18);
    display.cp437(true);
    display.write(0x10);
  }else{
    display.setCursor(36, 37);
    display.print("Count Down");
    sercorTriangleDown(66, 50 + i);
  }
  
  if (setOn) {
    SettingMenu();
    if (Deboundce(ButtonA)) {
      if (selectedOption == 1) {
        setOn = false;
      }
      if (selectedOption == 2) {
        // ESP.restart();  //jmp 0
        setOn = false;
        gameMode = 0;
        selectedOption = 1;
      }
    }
  }

  if (Deboundce(ButtonM)) {
    setOn = true;
  }  
}

void SettingMenu() {
  display.fillRect(24, 8, 80, 45, WHITE);
  display.fillRect(25, 9, 78, 43, BLACK);
  display.setTextColor(BLACK);
  display.fillRect(26, 10, 76, 11, WHITE);
  display.setCursor(48, 12);

  display.print("WANNING");
  display.setTextColor(WHITE);

  display.setCursor(48, 24);
  display.print("SAVE");
  if (selectedOption == 1) {
    cursor_Blink(33, 24);
  }

  display.setCursor(48, 34);
  display.print("QUIT");
  if (selectedOption == 2) {
    cursor_Blink(33, 34);
  }
}
