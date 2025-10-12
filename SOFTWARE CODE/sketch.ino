//JUST A BASIC CODE WHICH MAKES IT ABLE TO CONTROL A SQUARE WITH A JOYSTICK, I WILL MAKE THE REST WHEN I CAN TEST IT PHYSICALLY

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#define SCLK_PIN 8
#define MOSI_PIN 10
#define DC_PIN   6
#define CS_PIN   5
#define RST_PIN  7

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

#define JOY_X A0
#define JOY_Y A1 

int squareX = SCREEN_WIDTH / 2;
int squareY = SCREEN_HEIGHT / 2;
const int squareSize = 10;
const int moveSpeed = 3;

void setup() {
  Serial.begin(115200);
  display.begin();
  display.fillScreen(0x0000);

  pinMode(JOY_SW, INPUT_PULLUP);
}

void loop() {
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);

  // Map joystick values (0–4095) to -1, 0, or +1
  int xDir = 0;
  int yDir = 0;

  if (xVal < 1500) xDir = -1;
  else if (xVal > 2500) xDir = 1;

  if (yVal < 1500) yDir = 1; 
  else if (yVal > 2500) yDir = -1;

  // Update position
  squareX += xDir * moveSpeed;
  squareY += yDir * moveSpeed;

  // Boundaries
  if (squareX < 0) squareX = 0;
  if (squareX > SCREEN_WIDTH - squareSize) squareX = SCREEN_WIDTH - squareSize;
  if (squareY < 0) squareY = 0;
  if (squareY > SCREEN_HEIGHT - squareSize) squareY = SCREEN_HEIGHT - squareSize;

  // Draw
  display.fillScreen(0x0000);
  display.fillRect(squareX, squareY, squareSize, squareSize, 0xFFFF);

  delay(30);
}
