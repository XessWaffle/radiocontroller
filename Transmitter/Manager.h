
#ifndef MANAGER_H
#define MANAGER_H

#define LOWER_WRITE 0
#define UPPER_WRITE 255

#define UPPER_THRESH 205
#define LOWER_THRESH 50

#define DELAY 10

#include "Arduino.h"

class Manager{

  public:    
    Manager(char* designator, int managedPin, bool sticky);
    Manager();

    int getManagedPin();
    void setManagedPin(int pin);

    bool isSticky();
    void setSticky(bool sticky);

    bool isReversed();
    void setReversed(bool reversed);

    virtual int updateChannelValue(){}

    char* getDesignator();
    void printString();    

  protected:
    char* _designator;
    int _managedPin;
    int _currValue;
    bool _sticky;
    bool _reversed;
    int _updateDelay;
    

    
};

#endif
