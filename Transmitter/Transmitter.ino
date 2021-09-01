/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
* 
* 
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Manager.h"
#include "AnalogManager.h"
#include "DigitalManager.h"

#define LX A3
#define LY A2
#define RX A5
#define RY A4
#define RS 2
#define LS 4

#define CHANNELS 7


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver
RF24 radio(7, 8); // CE, CSN
// The sizeof this struct should not exceed 32 bytes
struct Data {
  byte chDat[CHANNELS];
};

Manager* managers[CHANNELS];

//Create a variable with the structure above and name it sent_data
Data data;

void setup()
{
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(my_radio_pipe);

  Serial.begin(9600);

  managers[0] = new AnalogManager("Throttle", LY, true, false);
  managers[1] = new AnalogManager("LX", LX, false, true);
  managers[2] = new AnalogManager("RX", RX, false, false);
  managers[3] = new AnalogManager("RY", RY, false, true);
  managers[4] = new AnalogManager("Unhooked", A1, false, false);
  managers[5] = new DigitalManager("LS", LS, true, false);
  managers[6] = new DigitalManager("RS", RS, false, false);
  
}

/**************************************************/
//Chapter 8 exercise 28

void loop()
{
  /*If your channel is reversed, just swap 0 to 255 by 255 to 0 below
  EXAMPLE:
  Normal:    data.ch1 = map( analogRead(A0), 0, 1024, 0, 255);
  Reversed:  data.ch1 = map( analogRead(A0), 0, 1024, 255, 0);  */
  
  for(int i = 0; i < CHANNELS; i++){

    data.chDat[i] = managers[i]->updateChannelValue();

    Serial.print(data.chDat[i]);
    Serial.print(" ");
    
  }

  Serial.print("\n");

  //printData();
  
  radio.write(&data, sizeof(Data));
}

void printData(){
  for(int i = 0; i < CHANNELS; i++){
    managers[i]->printString();
  }
}
