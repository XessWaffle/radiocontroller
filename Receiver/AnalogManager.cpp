#include "AnalogManager.h"

AnalogManager::AnalogManager(char* designator, int managedPin, byte preferredResetValue){
  _designator = designator;
  _managedPin = managedPin;
  _resetValue = preferredResetValue;
  _writer.attach(managedPin);
}

void AnalogManager::updateChannelValue(byte value){

  
  _currValue = map(value, 0, 255, LOWER_WRITE, UPPER_WRITE);
  
  if(_currValue < LOWER_WRITE){
    _currValue = LOWER_WRITE;
  }

  if(_currValue > UPPER_WRITE){
    _currValue = UPPER_WRITE;
  }

  _writer.writeMicroseconds(_currValue);
}
