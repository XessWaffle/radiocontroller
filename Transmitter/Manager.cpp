#include "Manager.h"

Manager::Manager(char* designator, int managedPin, bool sticky){
  _designator = designator;
  _managedPin = managedPin;
  _reversed = false;
  _sticky = sticky;
  _updateDelay = millis();
}

Manager::Manager(){
  char buff[20];
  sprintf(buff, "DEFAULT");

  _designator = buff;

  _managedPin = 0;
  _sticky = false;
  _currValue = 0;
  
}

int Manager::getManagedPin(){
  return _managedPin;
}

void Manager::setManagedPin(int pin){
  _managedPin = pin;
}

bool Manager::isSticky(){
  return _sticky;
}

void Manager::setSticky(bool sticky){
  _sticky = sticky;
}

bool Manager::isReversed(){
  return _reversed;
}

void Manager::setReversed(bool reversed){
  _reversed = reversed;
}

char* Manager::getDesignator(){
  return _designator;
}

void Manager::printString(){
  char buff[200];

  sprintf(buff, "%s at pin %u set to %u", _designator, _managedPin, _currValue);

  Serial.println(buff);
}
