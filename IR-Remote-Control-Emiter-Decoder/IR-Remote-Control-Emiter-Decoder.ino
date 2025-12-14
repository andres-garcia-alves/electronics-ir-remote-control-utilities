#include <IRremote.h>
const int IR_RECEIVE_PIN = 7; 

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void dump() {
  
  if (IrReceiver.decodedIRData.protocol == NEC)             { Serial.println("Protocol: NEC"); }
  else if (IrReceiver.decodedIRData.protocol == SONY)       { Serial.println("Protocol: SONY"); }
  else if (IrReceiver.decodedIRData.protocol == RC5)        { Serial.println("Protocol: RC5"); }
  else if (IrReceiver.decodedIRData.protocol == RC6)        { Serial.println("Protocol: RC6"); }
  else if (IrReceiver.decodedIRData.protocol == PANASONIC)  { Serial.println("Protocol: PANASONIC"); }
  else if (IrReceiver.decodedIRData.protocol == LG)         { Serial.println("Protocol: LG"); }
  else if (IrReceiver.decodedIRData.protocol == JVC)        { Serial.println("Protocol: JVC"); }
  else if (IrReceiver.decodedIRData.protocol == WHYNTER)    { Serial.println("Protocol: Whynter"); }
  else if (IrReceiver.decodedIRData.protocol == UNKNOWN)    { Serial.println("Protocol: Unknown"); }

  Serial.print("Raw data: ");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  Serial.print("Detail:   ");
  IrReceiver.printIRResultShort(&Serial); // Received data in one line
  Serial.println("");

  // Statement required to send data
  // IrReceiver.printIRSendUsage(&Serial);
  // IrSender.sendRC5(0x0, 0x10, 1);
}

void loop() {
  if (IrReceiver.decode()) {
    dump();
    IrReceiver.resume();  // continuar
  }
  delay(300);
}
