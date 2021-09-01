#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "AnalogManager.h"
#include "DigitalManager.h"
#include "Manager.h"
#include "Delta.h"

#define THROTTLE 10
#define AILERON_LEFT 3
#define AILERON_RIGHT 5
#define RUDDER 9
#define WHEEL 6
#define DIGITAL_LEFT 4
#define DIGITAL_RIGHT 2

#define CHANNELS 7
#define DIGITAL_CHANNELS 2
#define ANALOG_CHANNELS 5


const uint64_t pipeIn = 0xE8E8F0F0E1LL;     //Remember that this code is the same as in the transmitter
RF24 radio(7, 8);  //CSN and CE pins

// The sizeof this struct should not exceed 32 bytes

struct Data {
  byte chDat[CHANNELS];
};

Data data;

Manager* channelManagers[CHANNELS];

Delta* wingConfig;

/**************************************************/

void setup() {

  Serial.begin(9600);
  
  while(CHANNELS != DIGITAL_CHANNELS + ANALOG_CHANNELS){
    Serial.println("INCORRECT VALUES");
  }
  
  channelManagers[0] = new AnalogManager("Throttle", THROTTLE, 0);
  channelManagers[1] = new AnalogManager("Rudder", RUDDER, 127);
  channelManagers[2] = new AnalogManager("Left Aileron", AILERON_LEFT, 127);
  channelManagers[3] = new AnalogManager("Right Aileron", AILERON_RIGHT, 127);
  channelManagers[4] = new AnalogManager("Wheel", WHEEL, 127);
  channelManagers[5] = new DigitalManager("Left Digital", DIGITAL_LEFT, 0);
  channelManagers[6] = new DigitalManager("Right Digital", DIGITAL_RIGHT, 0);

  wingConfig = new Delta(channelManagers[2], channelManagers[3]);
  
  //Once again, begin and radio configuration
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  
  //We start the radio comunication
  radio.startListening();

}

/**************************************************/

unsigned long lastRecvTime = 0;

//We create the function that will read the data each certain time
void receive() {
  while ( radio.available() ) {
    radio.read(&data, sizeof(Data));
    lastRecvTime = millis(); //Here we receive the data
  }
}

/**************************************************/

void loop(){
  //Receive the radio data
  receive();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    for(int i = 0; i < CHANNELS; i++){
      channelManagers[i]->forceReset();
    }
  } 

  
  channelManagers[0]->updateChannelValue(data.chDat[0]);
  channelManagers[4]->updateChannelValue(255 - data.chDat[1]);
  channelManagers[1]->updateChannelValue(data.chDat[1]);
  wingConfig->updateWingConfiguration(data.chDat[3], data.chDat[2]);

  
  //printChannelManagers();
  
}//Loop end

void printChannelManagers(){
  for(int i = 0; i < CHANNELS; i++){
    channelManagers[i]->printString();
  }

  Serial.print("\n");
}
