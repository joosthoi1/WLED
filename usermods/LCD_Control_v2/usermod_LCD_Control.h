#pragma once

#include "wled.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);  // (I2C address, LCD width, LCD height)
//This is an empty v2 usermod template. Please see the file usermod_v2_example.h in the EXAMPLE_v2 usermod folder for documentation on the functions you can use!
class LCDControlUsermod : public Usermod {
  private:
    unsigned long lastExecutionTime = 0;  // Track last execution time
    const unsigned long interval = 1000;  // Run every 1000ms (1 second)
    StaticJsonDocument<1024> doc0;
    StaticJsonDocument<1024> doc1;
    JsonObject root0 = doc0.createNestedObject("state");
    JsonDocument *xDoc = &doc1;
    String top_text = "";
    String bottom_text = "";
    void write_text(String text, bool top) {
      if (text != (top ? top_text : bottom_text)) {
        (top ? top_text : bottom_text) = text;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(top_text);
        lcd.setCursor(0,1);
        lcd.print(bottom_text);
      }
    }
  public:
    bool handleButton(uint8_t b) override {
      //DEBUG_PRINTF("HANDLE BUTTON %d\n", b);
      return false;
    }
    void setup() override {
      // i2c_sda
      // i2c_sda
      // Start the I2C communication
      Wire.begin(i2c_sda, i2c_scl);

      // Initialize the LCD
      lcd.init();
      lcd.backlight();  // Turn on the backlight
      lcd.setCursor(0, 0);  // Set cursor to the first row, first column
    }
    void loop() override {
    }
    void onStateChange(uint8_t mode) override {
      DEBUG_PRINTLN("state change");
      String playlist;
      String preset;
      
      getPresetName(currentPlaylist, playlist);
      getPresetName(currentPreset, preset);
      DEBUG_PRINTLN(playlist);
      DEBUG_PRINTLN(preset);

      write_text(playlist, true);
      write_text(preset, false);
    }
};