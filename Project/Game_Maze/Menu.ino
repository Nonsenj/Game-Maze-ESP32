bool sec = false;

void cursor_Blink(int x, int y) {
  uint8_t font;
  if ((millis() - prevTimeblink) > 800) {
    prevTimeblink = millis();
    sec = !sec;
  }

  if(sec == 1){
    font = BLACK;
  }else{
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
    cursor_Blink(35,32);
    display.setCursor(50, 32);
  }else{
    display.setCursor(35, 32);
  }
  display.print("Start");
  display.setTextSize(1);

  if (selectedOption == 2){
    cursor_Blink(35,44);
    display.setCursor(47, 44);
  }else{
    display.setCursor(35, 44);
  }

  display.print("Setting");
  display.setTextSize(1);
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
  if(selectedOption == 1){
    cursor_Blink(33,24);
  }

  display.setCursor(48, 34);
  display.print("quit");
  if(selectedOption == 2){
    cursor_Blink(33,34);
  }
}

// void setting(){

// }