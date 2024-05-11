/*
CommandDecoder library by DELTA
created 1.5.2024
*/

#ifndef CommandDecoder_h
#define CommandDecoder_h

#define deviceName "Digibone Babblefish"

#include <EEPROM.h>
#define EEPROM_SIZE 100

void commandDecoderSetup();                         //only initializes eeprom
void checkSerialCommands();                         //checks the serial buffer and calls the decodeCommand() function and serially prints the command output
String decodeCommand(String commandandID);          //splits the command into an array, calls processCommandContent() it and returns the command output
String processCommandContent(String request[]);     //where the magic happens -> Never Call Directly!

#endif