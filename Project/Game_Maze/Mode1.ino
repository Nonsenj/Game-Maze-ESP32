void Game() {
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("level: ");
  display.print("demo");
  for (int shdw = 0; shdw < 124; shdw += 2) {
    display.drawPixel(shdw, 8, WHITE);
  }
  display.drawLine(0, 9, 123, 9, WHITE);
  generateMaze();
  drawMaze();

  if(Deboundce(4)){
    gameMenu();
  }
}

#define MAZEHEIGHT 32
#define MAZEWIDTH 15
int wallPhase = 1;

int illuminatedRow = 0;
uint8_t geni, genj, genk, genval, genmod;
int8_t genx, geny;

//32
uint16_t Maze[] = {
  0b1101111111111111,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1100000000000001,
  0b1101010101010101,
  0b1111111111111101,
  0b0000000000000000
};


bool readPixel(uint8_t i, uint8_t j) {
  uint16_t Data = Maze[i];
  byte Hi = (Data & 0xFF00) >> 8;
  byte Lo = Data & 0x00FF;
  if (j > 7) {
    return bitRead(Lo, 7 - (j % 8));
  } else {
    //j=j-8;
    return bitRead(Hi, 7 - (j % 8));
  }
}

void drawMaze() {
  uint8_t i, j;
  bool wall;

  for (i = 0; i <= MAZEHEIGHT; i++) {
    for (j = 0; j <= MAZEWIDTH; j++) {
      wall = readPixel(i, j);
      if (wall and j > 1) {
        display.drawPixel(i * 4, j * 4, WHITE);
        display.drawPixel(i * 4, j * 4 + 2, WHITE);
        display.drawPixel(i * 4 + 1, j * 4 + 1, WHITE);
        display.drawPixel(i * 4 + 1, j * 4 + 3, WHITE);
        display.drawPixel(i * 4 + 2, j * 4 + 2, WHITE);
        display.drawPixel(i * 4 + 2, j * 4 + 4, WHITE);
        display.drawPixel(i * 4 + 3, j * 4 + 1, WHITE);
        display.drawPixel(i * 4 + 3, j * 4 + 3, WHITE);
      }
    }
  }
}

int readVcc() {
  int result;  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);             // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);  // Convert
  while (bit_is_set(ADCSRA, ADSC))
    ;
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result;
  // Back-calculate AVcc in mV
  return result;
}

void generateMaze() {
  bool alternate = false;
  for (geni = 1; geni < MAZEHEIGHT - 1; geni++) {
    if (!alternate) {
      Maze[geni] = 0b1100000000000001;
    } else {
      Maze[geni] = 0b1101010101010101;
    }
    alternate = !alternate;
  }

  genmod = 4;
  for (geni = 2; geni < MAZEHEIGHT - 2; geni += 2) {
    for (genj = 3; genj < MAZEWIDTH - 1; genj += 2) {

      Maze[geni] |= (0x8000 >> genj);

      do {
        randomSeed(10);
        genval = (uint8_t)(random(10000) & 0x00FF) % genmod;
        genx = 0, geny = 0;
        if (genval == 0) geny = 1;   //right
        if (genval == 1) genx = -1;  //up
        if (genval == 2) genx = 1;   //down
        if (genval == 3) geny = -1;  //left
      } while ((Maze[geni + geny] & (0x8000 >> (genj + genx))));
      Maze[geni + geny] |= (0x8000 >> (genj + genx));
    }
    genmod = 3;
  }
}


void gameMenu(){
  
  display.fillRect(24,8,80,45,WHITE);
  display.fillRect(25,9,78,43,BLACK);
  display.setTextColor(BLACK);
  display.fillRect(26,10,76,11,WHITE);
  display.setCursor(48,12);
  display.print("PAUSED");
  display.setTextColor(WHITE);
  display.setCursor(48,24);
  display.print("resume");

  // if(selectedOption==1){
  //   display.setCursor(33+menuPointerPos,24);
  //   display.print(">");
  // }
  // display.setCursor(48,34);
  // display.print("quit");
  // if(selectedOption==2){
  //   display.setCursor(33+menuPointerPos,34);
  //   display.print(">");
  // }
}