
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
}

void mainMenu() {

  if (selectedOption == 1) {
    cursor_Blink(35,32);
    display.setCursor(50, 32);
    display.setTextColor(WHITE);
  }else{
    display.setCursor(35, 32);
  }
  display.print("Start");
  display.setTextSize(1);

  if (selectedOption == 2){
    cursor_Blink(35,44);
    display.setCursor(47, 44);
    display.setTextColor(WHITE);
  }else{
    display.setCursor(35, 44);
  }

  display.print("Setting");
  display.setTextSize(1);
}