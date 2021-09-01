#ifndef ANALOG_MANAGER_H
#define ANALOG_MANAGER_H

#include "Manager.h"

class AnalogManager : public Manager
{
  public:
    AnalogManager(char* designator, int managedPin, byte preferredResetValue);

    void updateChannelValue(byte value);
};

#endif
