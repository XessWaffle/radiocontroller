#include "AnalogManager.h"

AnalogManager::AnalogManager(char* designator, int managedPin, bool sticky, bool reversed){
  _designator = designator;
  _managedPin = managedPin;
  _reversed = reversed;
  _sticky = sticky;
  _currValue = 0;
  _updateDelay = millis();

  pinMode(managedPin, INPUT);
}

int AnalogManager::updateChannelValue(){

  if(!_sticky){
    if(!_reversed){
      _currValue = map(analogRead(_managedPin), 0, 1023, LOWER_WRITE, UPPER_WRITE);
    } else {
      _currValue = map(analogRead(_managedPin), 1023, 0, LOWER_WRITE, UPPER_WRITE);
    }
    
    if(_currValue < LOWER_WRITE){
      _currValue = LOWER_WRITE;
    }
  
    if(_currValue > UPPER_WRITE){
      _currValue = UPPER_WRITE;
    }
  
    return _currValue;
  } else {
    if(millis() - _updateDelay > DELAY){

      int value = 0;

      if(!_reversed){
        value = map(analogRead(_managedPin), 0, 1023, LOWER_WRITE, UPPER_WRITE);
      } else {
        value = map(analogRead(_managedPin), 1023, 0, LOWER_WRITE, UPPER_WRITE);
      }
      
      
      if(value < LOWER_THRESH){
        _currValue--;
      } else if(value > UPPER_THRESH){
        _currValue++;
      }

      if(_currValue > UPPER_WRITE){
        _currValue = UPPER_WRITE;
      }

      if(_currValue < LOWER_WRITE){
        _currValue = LOWER_WRITE;
      }
      _updateDelay = millis();
    }

    return _currValue;
  }
  
}
