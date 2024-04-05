#include "LCD_I2C_Extended.h"


void LCD_I2C_Extended::update() {
  static unsigned long lastTime = 0; // Last time the screen was updated.
  static int callbackIndex = 0; // Index of the callback to display.
  static bool endReached = false; // Indicates if the end of the callback list has been reached.
  
  currentTime = millis();
  
  // Check if the time interval has elapsed.
  if (currentTime - lastTime >= _interval) {
    clear(); // Clear the screen for the new message.
    setCursor(0, 0); // Reset the cursor to the start of the screen.
    
    // Loop to fill each line of the screen.
    for(int line = 0; line < _rows; line++) {
      // Check if we have reached the end of the callback list.
      if (callbackIndex >= _callbacks.getSize()) {
        if (endReached) {
          // If the end was already reached in the last cycle,
          // clear the screen and start again from the beginning.
          callbackIndex = 0;
          endReached = false;
          clear();
          setCursor(0, 0);
        } else {
          // Mark the end reached and insert blank lines.
          endReached = true;
          for (; line < _rows; line++) {
            print("                "); // Make sure the length matches `_cols`.
            setCursor(0, line + 1);
          }
          break;
        }
      }
      
      if (!endReached) {
        const char* message = _callbacks.get(callbackIndex++)();
        if (message != nullptr) {
          print(message);
        }
        setCursor(0, line + 1);
      }
    }
    
    lastTime = currentTime; // Update the last update time.
  }
}


void LCD_I2C_Extended::clear() {
  // Utiliser lcd_cols pour déterminer le nombre de caractères par ligne.
  const int maxLineLength = _cols;  // Utiliser la variable membre qui stocke le nombre de colonnes.

  char spacesArray[maxLineLength + 1];  // +1 pour le caractère de fin de chaîne '\0'.
  for (int i = 0; i < maxLineLength; i++) {
    spacesArray[i] = ' ';
  }
  spacesArray[maxLineLength] = '\0';  // Caractère de fin de chaîne.

  // Boucler sur chaque ligne de l'écran LCD et écrire la chaîne d'espaces.
  for (int line = 0; line < _rows; line++) {  // Assumer lcd_rows est aussi une variable membre.
    setCursor(0, line);
    print(spacesArray);
  }

  // Remettre le curseur à la position initiale (0,0).
  setCursor(0, 0);
}
