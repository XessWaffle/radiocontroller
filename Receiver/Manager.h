
#ifndef MANAGER_H
#define MANAGER_H

#define LOWER_WRITE 1000
#define UPPER_WRITE 2000

#include <Servo.h>
#include "Arduino.h"

class Manager{

  public:    
    Manager(char* designator, int managedPin, byte preferredResetValue);
    Manager();

    int getManagedPin();
    void setManagedPin(int pin);

    byte getResetValue();
    void setResetValue(byte resetValue);


    virtual void updateChannelValue(byte value){}
    void forceReset();

    int getCurrentValue();
    
    char* getDesignator();
    void printString();    

  protected:
    char* _designator;
    int _managedPin;
    byte _resetValue;
    int _currValue;
    Servo _writer;

    
};

#endif
