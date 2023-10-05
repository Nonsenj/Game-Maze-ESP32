int Randomscore;

void displayLevel() {
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(40, 20);
  display.print("COMPLETE!");
  display.setCursor(45, 32);
  display.print("Level ");
  display.print(level - 1);
  display.display();

  delay(2000);
  display.clearDisplay();
  display.setCursor(23, 25);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("SCORE");

  display.setCursor(50, 35);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(minute / 10);
  display.print(minute % 10);
  display.print(":");
  display.print(second / 10);
  display.print(second % 10);
  display.display();

  delay(1000);
  display.setCursor(50, 35);
  display.setTextColor(BLACK);
  display.setTextSize(2);
  display.print(minute / 10);
  display.print(minute % 10);
  display.print(":");
  display.print(second / 10);
  display.print(second % 10);
  display.display();

  delay(1000);
  display.setCursor(50, 35);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(minute / 10);
  display.print(minute % 10);
  display.print(":");
  display.print(second / 10);
  display.print(second % 10);
  display.display();

  delay(2000);


  for (int i = 0; i < 6; i++) {
    display.clearDisplay();
    display.setCursor(23, 25);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.print("SCORE");

    display.setCursor(50, 35);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    randomSeed(analogRead(34));
    Randomscore = random(10000);
    display.print(Randomscore);
    display.display();
    delay(500);
  }

  display.clearDisplay();
  display.setCursor(23, 25);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("SCORE");
  display.setCursor(50, 35);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(score);
  display.display();
  delay(4000);

  int i, j, levely = -8, levelnoy = -15;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 50; j += 2) {
      display.clearDisplay();
      if (levely < 20) {
        levely += 2;
      }
      if (levely == 20 and levelnoy < 18) {
        levelnoy += 2;
      }
      display.setTextSize(1);
      display.setCursor(45, levely);
      display.print("LEVEL");
      display.setTextSize(2);
      display.setCursor(80, levelnoy);
      display.print(level);
      display.display();
      
    }
  }
  delay(1500);
  display.setTextSize(1);
  generateMaze();
}