
#include "DigitalManager.h"

DigitalManager::DigitalManager(char* designator, int managedPin, bool sticky, bool reversed){
  _designator = designator;
  _managedPin = managedPin;
  _reversed = reversed;
  _sticky = sticky;
  _updateDelay = millis();
  _currValue = 0;
  _prevVal = 0;

  pinMode(managedPin, INPUT_PULLUP);
  
}

int DigitalManager::updateChannelValue(){
  if(!_sticky){
    bool nextVal = !digitalRead(_managedPin);

    if(_reversed) nextVal = !nextVal;
    
    if(!nextVal){
      _currValue = LOWER_WRITE;
    } else {
      _currValue = UPPER_WRITE;
    }
  
    return _currValue;
  } else {
    bool nextVal = !digitalRead(_managedPin);
    
    if(!_prevVal && nextVal){
      if(_currValue == LOWER_WRITE){ _currValue = UPPER_WRITE; } else { _currValue = LOWER_WRITE; }
    }

    _prevVal = nextVal;

    return _currValue;
  }
  
}
