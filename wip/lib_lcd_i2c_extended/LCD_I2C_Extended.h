/**
 * @file LCD_I2C_Extended.h
 * @author Nicolas Bourré (nbourre+git @ cshawi.ca)
 * @brief Class that extends the LiquidCrystal_I2C library to add some features such as message queueing and scrolling.
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LCD_I2C_EXTENDED_H
#define LCD_I2C_EXTENDED_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define QUEUE_SIZE 10
#define MSG_SIZE 32

/**
 * @brief Class that extends the LiquidCrystal_I2C library to add some features such as message queueing and scrolling.
 * 
 */
class LCD_I2C_Extended : public LiquidCrystal_I2C {
    public:
        // Constructor
        LCD_I2C_Extended(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

    private:
        // Queue containing the messages to display using char arrays
        char _queue[QUEUE_SIZE][MSG_SIZE];
        // Index of the first message in the queue
        uint8_t _queueStart;
        // Index of the last message in the queue
        uint8_t _queueEnd;
        // Index of the current message in the queue
        uint8_t _queueCurrent;
        // Index of the current character in the current message
        uint8_t _queueCurrentChar;
        // Number of messages in the queue
        uint8_t _queueCount;
        // Number of characters in the current message
        uint8_t _queueCurrentCharCount;
        // Number of characters in the current line
        uint8_t _queueCurrentLineCharCount;

        // Method to add a message to the queue
        void _queueAdd(char *msg);
        // Method to remove a message from the queue
        void _queueRemove();
        // Method to display the next message in the queue
        void _queueDisplayNext();
        // Method to display the previous message in the queue
        void _queueDisplayPrevious();
        


        
}

#endif