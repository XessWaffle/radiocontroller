#include "Delta.h"

Delta::Delta(Manager* left, Manager* right){
  _left = left;
  _right = right;
}

void Delta::updateWingConfiguration(byte elevator, byte roll){
  byte left = 255 - elevator, right = elevator;

  byte dev = elevator < 127 ? elevator : 255 - elevator;
  
  bool rollDir = roll < 127;

  double mag = rollDir ? (128 - roll)/128.0 : (128 - (255 - roll))/128.0;

  dev = (byte) (mag * dev);

  Serial.print(mag);
  Serial.print(" ");
  Serial.print(dev);
  

  if(!rollDir){
    left -= dev;
    right -= dev;
  } else {
    right += dev;
    left += dev;
  }


  _left->updateChannelValue(left);
  _right->updateChannelValue(right);
  
  
  
}
