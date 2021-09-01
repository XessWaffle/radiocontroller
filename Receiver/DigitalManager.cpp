
#include "DigitalManager.h"

DigitalManager::DigitalManager(char* designator, int managedPin, byte preferredResetValue){
  _designator = designator;
  _managedPin = managedPin;
  _resetValue = preferredResetValue;
  _writer.attach(managedPin);
}

void DigitalManager::updateChannelValue(byte value){

  int nextVal = value > 127 ? 1 : 0;
  
  if(nextVal == 0){
    _currValue = LOWER_WRITE;
  } else if(nextVal == 1){
    _currValue = UPPER_WRITE;
  }

  _writer.writeMicroseconds(_currValue);
  
}
