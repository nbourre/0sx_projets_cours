#include <LiquidCrystal_I2C.h>

class Affichage{
  public:
    // Constructeur
    Affichage(uint8_t lcdAddress, uint8_t lcdColumns, uint8_t lcdRows);

    void setLine1(String line1);
    void setLine2(String line2);
    void update();
    void clear();
    void setRefreshRate(int refreshRate) { _refreshRate = refreshRate; }
    int getRefreshRate() { return _refreshRate; }

  private:
    uint8_t _lcdAddress;
    uint8_t _lcdColumns;
    uint8_t _lcdRows;
    int _refreshRate = 250;
    String _line1;
    String _line2;
    
    unsigned long currentTime;
    bool _needUpdate = false; // Drapeau pour indiquer si l'affichage doit être mis à jour
    
    // Remarquez le "&" devant le nom de l'attribut
    // En C++, lorsque l'on veut définir un attribut qui est un objet à l'intérieur d'une classe,
    // il faut définir l'attribut comme une référence au type de l'objet. L'objet sera instancié
    // plus tard dans le code.
    LiquidCrystal_I2C &_lcd;
};

// Peut être déplacé dans le fichier Affichage.cpp
Affichage::Affichage(uint8_t lcdAddress, uint8_t lcdColumns, uint8_t lcdRows){
  _lcdAddress = lcdAddress;
  _lcdColumns = lcdColumns;
  _lcdRows = lcdRows;
  _lcd = LiquidCrystal_I2C(_lcdAddress, _lcdColumns, _lcdRows);
  _lcd.init();
  _lcd.backlight();
}

void Affichage::setLine1(String line1){
  // On sort de la méthode si la ligne est la même que la précédente 
  if (line1.equals(_line1)){
    return;
  }

  _line1 = line1;
  _needUpdate = true;
}

void Affichage::setLine2(String line2){
  // On sort de la méthode si la ligne est la même que la précédente
  if (line2.equals(_line2)){
    return;
  }
  _line2 = line2;
  _needUpdate = true;
}

void Affichage::clear(){
  _lcd.clear();
}

void Affichage::update(){
  static unsigned long lastUpdate = 0;
  currentTime = millis();

  // On sort de la méthode si le temps entre le dernier rafraîchissement est plus petit que le temps de rafraîchissement
  if (currentTime - lastUpdate < _refreshRate){
    return;
  }

  if (!_needUpdate){
    return;
  }

  _lcd.clear();
  _lcd.setCursor(0,0);
  _lcd.print(_line1);
  _lcd.setCursor(0,1);
  _lcd.print(_line2);

  // On redescent le drapeau
  _needUpdate = false;
}