#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

// Color definitions
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// TFT LCD pins (for UNO with 2.4 inch TFT)
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Input pins
#define VOLTAGE_PIN A5
#define CURRENT_PIN A4

int x = 0;
int lastVoltageY = 0;
int lastCurrentY = 0;

void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);  // ILI9341 or use 0x7789 for ST7789V if required
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  drawLayout();
}

void drawLayout() {
  tft.fillScreen(BLACK);
  
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(80, 0);
  tft.print("Oscilloscope");

  // Voltage label
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.print("Voltage");

  // Voltage Y-axis
  tft.drawLine(20, 50, 20, 130, WHITE);
  tft.drawLine(20, 90, 319, 90, WHITE);
  tft.setCursor(0, 50);
  tft.print("+10V");
  tft.setCursor(5, 88);
  tft.print("0");
  tft.setCursor(0, 120);
  tft.print("-10V");

  // Current label
  tft.setCursor(10, 140);
  tft.print("Current");

  // Current Y-axis
  tft.drawLine(20, 160, 20, 240, WHITE);
  tft.drawLine(20, 200, 319, 200, WHITE);
  tft.setCursor(0, 160);
  tft.print("+10");
  tft.setCursor(5, 198);
  tft.print("0");
  tft.setCursor(0, 230);
  tft.print("-10");
}

void loop() {
  int rawVoltage = analogRead(VOLTAGE_PIN);
  int rawCurrent = analogRead(CURRENT_PIN);

  float voltage = map(rawVoltage, 0, 1023, -100, 100) / 10.0;
  float current = map(rawCurrent, 0, 1023, -100, 100) / 10.0;

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Current: ");
  Serial.print(current);
  Serial.println(" A");

  int voltageY = map(voltage * 10, -100, 100, 130, 50);
  int currentY = map(current * 10, -100, 100, 240, 160);

  if (x > 318) {
    x = 21;
    drawLayout();
  }

  if (x > 21) {
    tft.drawLine(x, lastVoltageY, x + 1, voltageY, YELLOW);
    tft.drawLine(x, lastCurrentY, x + 1, currentY, CYAN);
  }

  lastVoltageY = voltageY;
  lastCurrentY = currentY;
  x++;

  delay(20);
}
