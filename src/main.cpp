#include <Arduino.h>
#include "qrcode.h"
#include <TFT_eSPI.h> 
#include <SPI.h>

QRCode qrcode;
TFT_eSPI tft = TFT_eSPI();  // Invoke library

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  if ( y >= tft.height() ) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  // Return 1 to decode next block
  return 1;
}

void setup() {
    tft.begin(); /* TFT init */
    tft.invertDisplay(1);
    tft.setRotation(0);
    tft.fillScreen(TFT_WHITE);

    // Start time
    uint32_t dt = millis();
  
    // Create the QR code
    int version = 1;
    int scale = 6;
    int shift_x = 60;
    int shift_y = 60;
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(version)];
    qrcode_initText(&qrcode, qrcodeData, version, ECC_LOW, "https://530520.com.tw/");
  
    // Delta time
    dt = millis() - dt;
    Serial.print("QR Code Generation Time: ");
    Serial.print(dt);
    Serial.print("\n");

    for (uint32_t row = 0; row < qrcode.size*scale; row++) {
        for (uint32_t col = 0; col < qrcode.size*scale; col++) {
            if (qrcode_getModule(&qrcode, int(col/scale), int(row/scale)))
                tft.drawPixel(shift_x+row, shift_y+col, TFT_BLACK);
            else 
                tft.drawPixel(shift_x+row, shift_y+col, TFT_WHITE);
        }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
}