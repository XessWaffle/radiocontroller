#include "Manager.h"

Manager::Manager(char* designator, int managedPin, byte preferredResetValue){
  _designator = designator;
  _managedPin = managedPin;
  _resetValue = preferredResetValue;
  _writer.attach(managedPin);
}

Manager::Manager(){
  char buff[20];
  sprintf(buff, "DEFAULT");

  _designator = buff;

  _managedPin = 0;
  _resetValue = 0;
  _currValue = 0;
  
}

int Manager::getManagedPin(){
  return _managedPin;
}

void Manager::setManagedPin(int pin){
  _managedPin = pin;
}

byte Manager::getResetValue(){
  return _resetValue;
}

void Manager::setResetValue(byte resetValue){
  _resetValue = resetValue;
}


int Manager::getCurrentValue(){
  return _currValue;
}

char* Manager::getDesignator(){
  return _designator;
}

void Manager::printString(){
  char buff[200];

  sprintf(buff, "  %s at pin %u set to %u(%u)  ", _designator, _managedPin, _currValue, _resetValue);

  Serial.print(buff);
}

void Manager::forceReset(){
  this->updateChannelValue(_resetValue);
}
