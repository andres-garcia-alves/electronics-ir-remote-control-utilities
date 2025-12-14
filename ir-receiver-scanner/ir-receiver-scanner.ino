#include <IRremote.hpp>

#define IR_LED_PIN 7
#define WAIT_TIME 500

void Protocol_RC5();
void Protocol_RC6_MCE();
void Protocol_RC6_Generic();
void Protocol_NEC();
void Protocol_Samsung();
void Protocol_JVC();
void Protocol_Panasonic();
void Protocol_Sharp();
void Protocol_Denon();
void Protocol_Sony_12();
void Protocol_Sony_15();
void Protocol_Sony_20();
void Protocol_RC5_Extended();
void Protocol_RC6_Extended();
void Protocol_NEC_Extended();


void setup() {
  Serial.begin(9600);
  IrSender.begin(IR_LED_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {

  Protocol_RC5();
  Protocol_RC6_MCE();
  Protocol_RC6_Generic();
  Protocol_NEC();
  Protocol_Samsung();
  Protocol_JVC();
  Protocol_Panasonic();
  Protocol_Sharp();
  Protocol_Denon();
  Protocol_Sony_12();
  Protocol_Sony_15();
  Protocol_Sony_20();

  // extended scans, try this if previus lines doesn't work (but it takes a while)
  // Protocol_RC5_Extended();
  // Protocol_RC6_Extended();
  // Protocol_NEC_Extended();

  while (1);
}


// Protocolo RC5 (Phillips)
void Protocol_RC5() {

  Serial.println("Trying RC5...");
  static bool toggle = false;

  for (uint8_t address = 0; address <= 3; address++) {
    for (uint8_t command = 0x00; command <= 0x3F; command++) {
      Serial.print("RC5 Addr ");
      Serial.print(address);
      Serial.print(" Cmd 0x");
      Serial.print(command, HEX);
      Serial.print(" Toggle ");
      Serial.println(toggle);

      IrSender.sendRC5(address, command, toggle);
      toggle = !toggle;

      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan RC5 completed");
}

// Protocol RC6-MCE
void Protocol_RC6_MCE() {

  Serial.println("Trying RC6 MCE...");

  // Comandos MCE típicos
  uint16_t mceCommands[] = {
    0x0C, // Power
    0x10, // Volume Up
    0x11, // Volume Down
    0x20, // Play
    0x21, // Pause
    0x22, // Stop
    0x23, // Next
    0x24  // Previous
  };

  for (uint8_t i = 0; i < sizeof(mceCommands) / 2; i++) {
    Serial.print("Sending RC6 MCE cmd: 0x");
    Serial.println(mceCommands[i], HEX);

    // RC6 mode 0, customer 0x800F es estándar MCE
    IrSender.sendRC6(0x800F, mceCommands[i], 0);
    delay(WAIT_TIME);
  }

  Serial.println("Scan RC6-MCE completed");
}

// Protocolo RC6-Generico
void Protocol_RC6_Generic() {

  Serial.println("Trying RC6 mode 0...");

  for (uint8_t address = 0; address <= 3; address++) {
    for (uint8_t command = 0x00; command <= 0x3F; command++) {
      Serial.print("RC6 Addr ");
      Serial.print(address);
      Serial.print(" Cmd 0x");
      Serial.println(command, HEX);

      IrSender.sendRC6(address, command, 0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan RC6-Generic completed");
}

// Protocolo NEC (small scan)
void Protocol_NEC() {

  Serial.println("Trying NEC...");
  uint16_t addresses[] = {0x00FF, 0x10EF, 0x20DF, 0x40BF};

  for (uint8_t a = 0; a < sizeof(addresses) / 2; a++) {
    for (uint8_t cmd = 0x00; cmd <= 0x3F; cmd++) {
      Serial.print("Addr 0x");
      Serial.print(addresses[a], HEX);
      Serial.print(" Cmd 0x");
      Serial.println(cmd, HEX);

      IrSender.sendNEC(addresses[a], cmd, 0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan NEC completed");
}

// Protocolo Samsung
void Protocol_Samsung() {

  Serial.println("Trying Samsung...");
  uint16_t address = 0x07; // Samsung típico

  for (uint8_t cmd = 0x00; cmd <= 0x3F; cmd++) {
    Serial.print("Samsung Cmd 0x");
    Serial.println(cmd, HEX);

    IrSender.sendSamsung(address, cmd, 0);
    delay(WAIT_TIME);
  }

  Serial.println("Scan Samsung completed");
}

// Protocolo JVC
void Protocol_JVC() {

  Serial.println("Trying JVC...");

  for (uint8_t cmd = 0x00; cmd <= 0x3F; cmd++) {
    Serial.print("JVC Cmd 0x");
    Serial.println(cmd, HEX);

    // Address = 0x01, Command = cmd, Repeats = 0
    IrSender.sendJVC((uint8_t)0x01, (uint8_t)cmd, (uint_fast8_t)0);
    delay(WAIT_TIME);
  }

  Serial.println("Scan JVC completed");
}

// Protocolo Panasonic
void Protocol_Panasonic() {

  Serial.println("Trying Panasonic...");
  uint16_t panasonicAddress = 0x4004;

  for (uint16_t cmd = 0x0000; cmd <= 0x003F; cmd++) {
    Serial.print("Panasonic Cmd 0x");
    Serial.println(cmd, HEX);

    IrSender.sendPanasonic((uint16_t)panasonicAddress, (uint16_t)cmd, (uint_fast8_t)0); // 0 repeats
    delay(WAIT_TIME);
  }

  Serial.println("Scan Panasonic completed");
}

// Protocol Sharp
void Protocol_Sharp() {

  Serial.println("Trying Sharp...");

  for (uint8_t cmd = 0x00; cmd <= 0x3F; cmd++) {
    Serial.print("Sharp Cmd 0x");
    Serial.println(cmd, HEX);

    IrSender.sendSharp(0x5AA5, cmd);
    delay(WAIT_TIME);
  }

  Serial.println("Scan Sharp completed");
}

// Protocol Denon
void Protocol_Denon() {

  Serial.println("Trying Denon...");

  for (uint8_t cmd = 0x00; cmd <= 0x3F; cmd++) {
    Serial.print("Denon Cmd 0x");
    Serial.println(cmd, HEX);

    IrSender.sendDenon(0x04, cmd);
    delay(WAIT_TIME);
  }

  Serial.println("Scan Denon completed");
}

// Protocol Sony SIRC 12 bits
void Protocol_Sony_12() {

  Serial.println("Trying SONY SIRC 12 bits...");
  uint16_t sonyAddresses[] = {1, 5, 10};

  for (uint8_t a = 0; a < sizeof(sonyAddresses) / sizeof(sonyAddresses[0]); a++) {
    for (uint8_t cmd = 0; cmd < 32; cmd++) {
      Serial.print("SONY12 Addr ");
      Serial.print(sonyAddresses[a]);
      Serial.print(" Cmd ");
      Serial.println(cmd);

      IrSender.sendSony((uint16_t)sonyAddresses[a], (uint16_t)cmd, (uint_fast8_t)12, (uint_fast8_t)0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan SONY 12 bits completed");
}

// Protocol Sony SIRC 15 bits
void Protocol_Sony_15() {

  Serial.println("Trying SONY SIRC 15 bits...");
  uint16_t sonyAddresses[] = {1, 5, 10};

  for (uint8_t a = 0; a < sizeof(sonyAddresses) / sizeof(sonyAddresses[0]); a++) {
    for (uint8_t cmd = 0; cmd < 128; cmd++) {
      Serial.print("SONY15 Addr ");
      Serial.print(sonyAddresses[a]);
      Serial.print(" Cmd ");
      Serial.println(cmd);

      IrSender.sendSony((uint16_t)sonyAddresses[a], (uint16_t)cmd, (uint_fast8_t)15, (uint_fast8_t)0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan SONY 15 bits completed");
}

// Protocol Sony SIRC 20 bits
void Protocol_Sony_20() {

  Serial.println("Trying SONY SIRC 20 bits...");
  uint16_t sonyAddresses[] = {1, 5};

  for (uint8_t a = 0; a < sizeof(sonyAddresses) / sizeof(sonyAddresses[0]); a++) {
    for (uint16_t cmd = 0; cmd < 256; cmd++) {
      Serial.print("SONY20 Addr ");
      Serial.print(sonyAddresses[a]);
      Serial.print(" Cmd ");
      Serial.println(cmd);

      IrSender.sendSony((uint16_t)sonyAddresses[a], (uint16_t)cmd, (uint_fast8_t)20, (uint_fast8_t)0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan SONY 20 bits completed");
}

// Protocol RC5 (extended scan)
void Protocol_RC5_Extended() {

  Serial.println("Trying RC5 (extended test)...");

  for (uint8_t address = 0; address < 32; address++) {
    for (uint8_t cmd = 0; cmd < 64; cmd++) {
      for (uint8_t toggle = 0; toggle < 2; toggle++) {

        Serial.print("RC5 addr=");
        Serial.print(address);
        Serial.print(" cmd=");
        Serial.print(cmd);
        Serial.print(" toggle=");
        Serial.println(toggle);

        IrSender.sendRC5((uint8_t)address, (uint8_t)cmd, (uint_fast8_t)toggle);
        delay(WAIT_TIME);
      }
    }
  }

  Serial.println("Scan RC5 (extended) completed");
}

// Protocolo RC6-Generico (extended scan)
void Protocol_RC6_Extended() {

  Serial.println("Trying RC6 (extended test)...");

  for (uint8_t address = 0; address < 16; address++) {
    for (uint8_t cmd = 0; cmd < 64; cmd++) {

      Serial.print("RC6 addr=");
      Serial.print(address);
      Serial.print(" cmd=");
      Serial.println(cmd);

      IrSender.sendRC6((uint8_t)address, (uint8_t)cmd, (uint_fast8_t)0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan RC6-Generico (extended) completed");
}

// Protocolo NEC (extended scan)
void Protocol_NEC_Extended() {

  Serial.println("Trying NEC (extended test)...");

  for (uint16_t address = 0x0000; address <= 0x00FF; address++) {
    for (uint8_t cmd = 0x00; cmd <= 0x3F; cmd++) {

      Serial.print("NEC addr=0x");
      Serial.print(address, HEX);
      Serial.print(" cmd=0x");
      Serial.println(cmd, HEX);

      IrSender.sendNEC((uint16_t)address, (uint8_t)cmd, (uint_fast8_t)0);
      delay(WAIT_TIME);
    }
  }

  Serial.println("Scan NEC (extended) completed");
}
