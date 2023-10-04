void displayLevel() {
  int levely = -8, levelnoy = -8, i, j;

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(40, 20);
  display.print("COMPLETE!");
  display.setCursor(45, 32);
  display.print("Level ");
  display.print(level-1);
  display.display();

  delay(2000);

  levely = -8;
  levelnoy = -8;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 50; j += 2) {
      display.clearDisplay();
      if (levely < 20) {
        levely += 2;
      }
      if (levely == 20 and levelnoy < 30) {
        levelnoy += 2;
      }
      display.setCursor(45, levely);
      display.print("LEVEL");
      display.setCursor(75, levelnoy);
      display.print(level);

      displayBattery(WHITE);
      displayIndicators(WHITE);

      display.display();
    }
  }


  delay(1500);
  generateMaze();
}