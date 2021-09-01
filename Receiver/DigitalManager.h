#ifndef DIGITAL_MANAGER_H
#define DIGITAL_MANAGER_H

#include "Manager.h"

class DigitalManager: public Manager{
  public:
    DigitalManager(char* designator, int managedPin, byte preferredResetValue);

    void updateChannelValue(byte value);
};

#endif
