#ifndef DELTA_H
#define DELTA_H

#include "Manager.h"

class Delta{
  public:
    Delta(Manager* left, Manager* right);

    void updateWingConfiguration(byte elevator, byte roll);

  private:
    Manager *_left, *_right;
};

#endif
