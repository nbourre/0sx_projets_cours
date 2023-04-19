

#ifndef LCD_I2C_EXTENDED_H
#define LCD_I2C_EXTENDED_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <List.hpp>

/**
 * @brief Class that extends the LiquidCrystal_I2C library to add some features such as message queueing and scrolling.
 * 
 */
class LCD_I2C_Extended : public LiquidCrystal_I2C {
    public:
      LCD_I2C_Extended (uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols,lcd_rows) {};
      void setMessageInterval(int interval) {_interval = interval ;};
      void update();
      List<char * (*)()> getCallbacks() {return _callbacks;};
      
    void addCallback(char *(* callback)()) {
      _callbacks.add(callback);
    };    

    private:
      unsigned int _interval = 3000;
      unsigned long currentTime = 0;
      int _currentIdx = 0;
      
      // List of callbacks that returns String
      List<char * (*)()> _callbacks;
      
      char _buffer[20];        
};

#endif