#ifndef DIGITAL_MANAGER_H
#define DIGITAL_MANAGER_H

#include "Manager.h"

class DigitalManager: public Manager{
  public:
    DigitalManager(char* designator, int managedPin, bool sticky, bool reversed);

    int updateChannelValue();

  private:
    bool _prevVal;
};

#endif
