# IR Remote Control Utilities

Arduino utilities for Infrared (IR) Remote Control protocols and codes.

&nbsp;

This project use the following electronic components:
- 1 x Arduino Nano v3.0
- 1 x Breadboard
- 1 x IR LED Emiter
- 1 x IR LED Receiver (VS1838 or similar)
- 1 x 220 ohm resistor
- wires

&nbsp;

### IR-Remote-Control-Emiter-Decoder

This Arduino sketch is useful for determining the protocol (RC5, RC6, NEC, Sony, Panasonic, LG, JVC, Whynter) used by an infrared remote control, and the code associated with each button.

Connect the signal pin of an IR LED receiver to pin 7 of the Arduino. When you press the buttons on the remote control, the Arduino IDE's Serial Monitor will display the protocol, the code (command) associated with each button, and other transmission data (duration, etc.).

This is useful, for example, if you want to use an existing remote control with a different device, or as a first step in cloning a remote control.

&nbsp;

### IR-Remote-Control-Receiver-Scanner

This Arduino sketch is useful for determining the protocol (RC5, RC6-MCE, RC6-Generic, NEC, Samsung, JVC, Panasonic, Sharp, Denon, Sony) used by an infrared receiver.

Connect the signal pin of an IR LED emitter to pin 7 of the Arduino (with a 220ohms resistor in series). When executed, it will sequentially emit different commands for each of the supported protocols. The Arduino IDE's Serial Monitor will simultaneously display the different protocols, addresses, and emitted commands.  
I recommend leaving a text editor open with some static text (e.g., 1, 2, 3, 4, 5) in the foreground. Any action (typing a character, moving the cursor, pressing 'Enter') displayed in the text editor indicates the protocol. Then, by scanning through the different command codes for current protocol, you can determine which commands are recognized by the IR receiver.

Useful, for example, if you want to reverse engineer a replacement remote control in case the original one breaks down.  
Note: Some infrared devices use proprietary (customized) protocols that will not respond to this "sweep" technique using standard protocols and commands.

&nbsp;

### Version History

v1.0 (2025.12.15) - Initial release.  

&nbsp;

This source code is licensed under GPL v3.0  
Please send me your feedback about this project: andres.garcia.alves@gmail.com
