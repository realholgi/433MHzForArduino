/*
 * This sketch demonstrates how to use InterruptChain to receive and
 * decode both remote switches as remote sensors.
 *
 * Basically, this sketch combines the features of the ShowReceivedCode
 * example of RemoteSwitch and the ThermoHygroReceiver of RemoteSensor
 * at the same time!
 *
 * After uploading, enable the serial monitor at 115200 baud.
 * When you press buttons on a 433MHz remote control, as supported by 
 * RemoteSwitch, the code will be echoed. At the same time, if data
 * of a remote thermo/hygro-sensor is received, as supported by
 * RemoteSensor.
 *
 * Setup:
 * - connect a 433MHz receiver on digital pin 2.
 */

#include <RemoteReceiver.h>
#include <SensorReceiver.h>
#include <InterruptChain.h>

void setup() {
    Serial.begin(115200);
    
    // Interrupt -1 to indicate you will call the interrupt handler with InterruptChain
    RemoteReceiver::init(-1, 3, showCode);
    
    // Again, interrupt -1 to indicate you will call the interrupt handler with InterruptChain
    SensorReceiver::init(-1, showTempHumi);

    // On interrupt, call the interrupt handlers of remote and sensor receivers
    InterruptChain::addInterruptCallback(0, RemoteReceiver::interruptHandler);
    InterruptChain::addInterruptCallback(0, SensorReceiver::interruptHandler);
}

void loop() {
   // You can do other stuff here!
}

// shows the received code sent from a remote switch
void showCode(unsigned long receivedCode, unsigned int period) {
  // Print the received code.
  Serial.print("Code: ");
  Serial.println(receivedCode);
}

void showTempHumi(byte *data) {
  // is data a ThermoHygro-device?
  if ((data[3] & 0x1f) == 0x1e) {
    // Yes!
    byte channel, randomId;
    int temp;
    short int humidity;

    // Decode the data
    SensorReceiver::decodeThermoHygro(data, channel, randomId, temp, humidity);
  
    // Print temperature. Note: temp is 10x the actual temperature!
    Serial.print("Temperature: ");
    Serial.print(temp / 10); // units
    Serial.print('.');
    Serial.println(temp % 10); // decimal
  }
}
