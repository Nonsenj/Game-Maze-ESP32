#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <RTClib.h>
#include <Preferences.h>
#include "DHT.h"
#include "pitches.h"

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Nonsense";
const char* password = "00000000";

const char* serverName = "http://justbelieve.thddns.net:7330/post-esp-data.php";

//api need to match with post-esp-data.php file on raspi
String apiKeyValue = "tPmAT5Ab3j7F9";

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SH1106 display(OLED_SDA, OLED_SCL);

// '368253026_817568569838035_167469562880917573_n', 125x60px
const unsigned char Title[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xc9, 0x07, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0e, 0x08, 0x1f, 0xdf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x3e, 0x1c, 0x03, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x3e, 0x3e, 0x03, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0x6e, 0x37, 0x06, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0xce, 0x63, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0x80, 0xe1, 0x9f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x07, 0x00, 0x1d, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x06, 0x07, 0x80, 0x3d, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x0f, 0x07, 0xc0, 0x7d, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x7e, 0x1f, 0x87, 0xe0, 0xfd, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x7e, 0x3b, 0x87, 0x71, 0xfd, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x0e, 0x39, 0xc7, 0x3b, 0xdd, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x0e, 0x70, 0xe7, 0x1f, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xe0, 0x77, 0x0e, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Preferences preferences;
#define ACTIVATED LOW
#define MAZEHEIGHT 31
#define MAZEWIDTH 15
#define ButtonA 26
#define ButtonB 27
#define ButtonM 14
#define sound 15

#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


float h;
float t;
float f;

int selectedOption = 1;
int Modegame;
bool sound_enabled = true;

unsigned long prevTimeblink = 0;
unsigned long prevTimeSleep = 0;
unsigned long prevSetCursor = 0;

RTC_DATA_ATTR int gameMode = 0;
RTC_DATA_ATTR int8_t posx = 0, posy = 2;
int8_t blinkPlayer = 1;
RTC_DATA_ATTR bool gamePause = true;
RTC_DATA_ATTR bool setOn = false;

int8_t illuminatedRow = 0;
int8_t wallPhase = 1;
RTC_DATA_ATTR int8_t level = 1;

const int JoyStick_pin = 25;
const int X_pin = 32;
const int Y_pin = 33;

hw_timer_t* My_timer = NULL;
RTC_DATA_ATTR uint8_t minute = 0;
RTC_DATA_ATTR uint8_t second = 0;
RTC_DATA_ATTR bool timerOn = false;
RTC_DS1307 rtc;

RTC_DATA_ATTR int score;
RTC_DATA_ATTR int totalScore;
int pertotalScore;
bool setSelect = false;
String NameID;

void IRAM_ATTR onTimer() {
  if (second == 59) {
    second = 0;
    minute++;
  } else {
    second++;
  }
}

void SendData() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&name=" + NameID
                             + "&value1=" + String(Modegame)
                             + "&value2=" + String(totalScore) + "";


    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // Free resources
    http.end();
    Serial.println("SendData");
  }
  else {
    Serial.println("WiFi Disconnected");
  }

}

void Speak(uint8_t pin, int note, int noteDuration) {
  if (sound_enabled) {
    tone(pin, note, noteDuration);
    noTone(sound);
  }
}

void ReadDH11() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
}

void ReadEEprom() {
  preferences.begin("Savegame", false);
  totalScore = preferences.getUInt("totalScore", 0);
  Modegame = preferences.getUInt("modegame", 1);
  NameID = preferences.getString("username", "NONE");
  pertotalScore = preferences.getUInt("totalScore", 0);
  preferences.end();
}

void displayWIFI(uint8_t font) {
  display.drawLine(91, 1, 91, 5, font);
  display.drawPixel(90, 1, font);
  display.drawLine(90, 3, 90, 6, font);
  display.drawLine(89, 1, 89, 5, font);
}

void displayClock(uint8_t font) {
  DateTime now = rtc.now();
  display.setCursor(3, 2);
  display.setTextColor(font);
  display.setTextSize(1);
  display.print(now.hour());
  display.print(":");
  display.print(now.minute() / 10);
  display.print(now.minute() % 10);

}

void readHTF() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
}


void displayIndicators(uint8_t font) {
  //speaker
  display.drawLine(103, 1, 103, 6, font);
  display.drawLine(102, 1, 102, 6, font);
  display.drawLine(101, 2, 101, 5, font);
  display.drawLine(100, 3, 100, 4, font);
  display.drawLine(99, 3, 99, 4, font);
  if (sound_enabled) {
    display.drawPixel(105, 2, font);
    display.drawPixel(106, 3, font);
    display.drawPixel(106, 4, font);
    display.drawPixel(105, 5, font);
  }
}

void displayBattery(uint8_t font) {

  display.setTextColor(font);
  display.setCursor(82, 0);
  //display.print("vcc: ");
  int batt = 3000;
  //display.print(batt);

  display.drawLine(114, 1, 125, 1, font);
  display.drawLine(114, 6, 125, 6, font);
  display.drawLine(114, 1, 114, 6, font);
  display.drawLine(125, 1, 125, 6, font);
  display.drawLine(126, 3, 126, 4, font);

  if (batt > 4300) {
    display.drawLine(109, 2, 109, 1, font);
    display.drawLine(111, 2, 111, 1, font);
    display.drawLine(108, 3, 112, 3, font);
    display.drawLine(108, 4, 112, 4, font);
    display.drawPixel(110, 5, font);
    display.drawPixel(111, 6, font);
    display.drawPixel(112, 6, font);
    display.drawPixel(113, 6, font);
  }
  if (batt > 2900) {
    display.drawLine(116, 3, 116, 4, font);
    display.drawLine(117, 3, 117, 4, font);
  }
  if (batt > 3000) {
    display.drawLine(119, 3, 119, 4, font);
    display.drawLine(120, 3, 120, 4, font);
  }
  if (batt > 3100) {
    display.drawLine(122, 3, 122, 4, font);
    display.drawLine(123, 3, 123, 4, font);
  }
}

int readVcc() {
  float result;  // Read 1.1V reference against AVcc
  result = analogRead(25);
  return result;
}

void setup() {
  WiFi.begin(ssid, password);
  rtc.begin();
  dht.begin();  
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000000, true);
  pinMode(JoyStick_pin, INPUT_PULLUP);
  pinMode(ButtonA, INPUT_PULLUP);
  pinMode(ButtonB, INPUT_PULLUP);
  pinMode(ButtonM, INPUT_PULLUP);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.display();
  display.clearDisplay();

  display.drawBitmap(0, 10, Title, 128, 64, WHITE);
  display.display();
  delay(3000);

  display.clearDisplay();

  ReadEEprom();
}

void loop() {
  display.clearDisplay();
  if (gameMode == 0) {
    mainMenu();
    controller();
    displayClock(WHITE);
  }

  if (gameMode == 1) {
    Game();
    controller();
  }

  if (gameMode == 2) {
    setting();
    controller();
  }

  if (gameMode != 2) {
    displayBattery(WHITE);
    displayIndicators(WHITE);
  }
  
  if(WiFi.status()== WL_CONNECTED){
    displayWIFI(WHITE);
  }

  display.display();

  if ((millis() - prevTimeSleep) > 60000 && gamePause) {
    prevTimeSleep = millis();
    timerDetachInterrupt(My_timer);
    Serial.println("Going to sleep now");
    display.clearDisplay();
    display.display();
    esp_deep_sleep_start();
  }
}
