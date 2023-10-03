void Game() {
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("level: ");
  display.print("demo");
  for (int shdw = 0; shdw < 127; shdw += 2) {
    display.drawPixel(shdw, 8, WHITE);
  }
  display.drawLine(0, 9, 127, 9, WHITE);

  if (posx == MAZEHEIGHT + 1) {
    posx = 0;
    posy = 2;
    illuminatedRow = 0;
    blinkPlayer = 1;
    wallPhase = 1;
    selectedOption = 1;
    ESP.restart(); //jmp 0 
  } else {
    drawMaze();
    if (gamePause) {
      gameMenu();
      if (Deboundce(ButtonA)) {
        if(selectedOption == 1 ){
          gamePause = false;
        }
        if(selectedOption == 2){
          ESP.restart(); //jmp 0 
        }
      }
    }
  }

  if (!gamePause) {
    if (Deboundce(ButtonA)) {
      gamePause = true;
    }
  }
}
