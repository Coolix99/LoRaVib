/*
void checkSerialCommands(void)      interprets the commands which are sent via the USB Serial Terminal. Has to be called frequently. This might interfere with other functions which listen for serial inputs
String decodeCommand(String)        takes a command string as an input, and returns the value
processCommandContent()             interprets and executes the command. This function is automatically called in decodeCommand(). Do not call this function elsewhere

example commands:
"id"                                returns a custom identifier string                          (like "untitled esp32 dev board")
"analogRead,34"                     returns the analogRead value of pin 34                      (like "2538")
"analogRead,34#1357"                returns the analogRead value of pin 34 and the message ID   (like "2538#1357")
"eepromWrite,3,123"                 sets the value of EEPROM cell 3 to 123                      (like "done")
"digitalWrite,16,1#abc123"          turns pin 16 on and returns the id                          (like "done#abc123")

note: to avoid errors in communication it makes sense to send the execution time or a counter as an id, because it won't send the same value twice in a row
*/
#include "CommandDecoder.h"
#include <esp_wifi.h>
#include <LoRa.h>

String processCommandContent(String request[]) {  //add custom commands here
  String com = request[0];                        //use com (for command) to make the code more readable and reduce errors
  com.toUpperCase();                              //convert com to upper case to avoid capitalization errors
  String returnString = "";

  if (com == "PING") {
    returnString = "pong";
  } else if (com == "ID") {
    returnString = deviceName;
  } else if (com == "INFO") {
    returnString = deviceName;
    returnString += "\nCompiled from: " + String(__FILE__);
    returnString += "\n";
    returnString += __DATE__;
    returnString += "\n";
    returnString += __TIME__;
  } else if (com == "STATUS") {
    returnString = "operational\n";
    returnString += "system time: " + String(millis() / 1000) + "s\n";
  } else if (com == "HELP") {
    returnString = "Quick Manual:\n";
    returnString += "command structure:\ncommand,parameter1,parameter2...\n";
    returnString += "example:\nPINMODE,15,INPUT_PULLDOWN\n";
  } else if (com == "NAP") {
    esp_sleep_enable_timer_wakeup(1000 * request[1].toFloat());
    esp_light_sleep_start();
  } else if (com == "CPUFREQUENCY") {
    setCpuFrequencyMhz(request[1].toInt());
  } else if (com == "MESSAGE") {
    Serial.println(request[1]);
  } else if (com == "MILLIS") {
    returnString = millis();
  } else if (com == "MICROS") {
    returnString = micros();
  } else if (com == "PINMODE") {
    request[2].toUpperCase();
    if (request[2] == "INPUT") {
      pinMode(request[1].toInt(), INPUT);
    } else if (request[2] == "OUTPUT") {
      pinMode(request[1].toInt(), OUTPUT);
    } else if (request[2] == "INPUT_PULLUP") {
      pinMode(request[1].toInt(), INPUT_PULLUP);
    } else if (request[2] == "INPUT_PULLDOWN") {
      pinMode(request[1].toInt(), INPUT_PULLDOWN);
    } else {
      returnString = "invalid pinMode";
    }
  } else if (com == "ANALOGREAD") {
    returnString = analogRead(request[1].toInt());
  } else if (com == "DIGITALREAD") {
    returnString = digitalRead(request[1].toInt());
  } else if (com == "TOUCHREAD") {
    returnString = touchRead(request[1].toInt());
  } else if (com == "DIGITALWRITE") {
    digitalWrite(request[1].toInt(), request[2].toInt());
  } else if (com == "ANALOGWRITE") {
    analogWrite(request[1].toInt(), request[2].toInt());
  } else if (com == "LEDCSETUP") {
    ledcSetup(request[1].toInt(), request[2].toInt(), request[3].toInt());
  } else if (com == "LEDCATTACHPIN") {
    ledcAttachPin(request[1].toInt(), request[2].toInt());
  } else if (com == "LEDCDETACHPIN") {
    ledcDetachPin(request[1].toInt());
  } else if (com == "LEDCWRITE") {
    ledcWrite(request[1].toInt(), request[2].toInt());
  } else if (com == "DACWRITE") {
    dacWrite(request[1].toInt(), request[2].toInt());
  } else if (com == "PRINTSERIAL") {
    Serial.print(request[1]);
  } else if (com == "EEPROMWRITE") {
    EEPROM.write(request[1].toInt(), request[2].toInt());
  } else if (com == "EEPROMREAD") {
    returnString = EEPROM.read(request[1].toInt());
  } else if (com == "EEPROMCOMMIT") {
    EEPROM.commit();
  } else if (com == "EEPROMREADUNTIL") {
    returnString = "";
    for (int i = 0; i <= request[1].toInt(); i++) {
      returnString += EEPROM.read(i);
      returnString += "; ";
    }
  } else if (com == "EEPROMSPILL") {
    returnString = "";
    for (int i = 0; i <= EEPROM_SIZE; i++) {
      if (request[1].toInt()) {
        returnString += char(EEPROM.read(i));
      } else {
        returnString += EEPROM.read(i);
      }
      returnString += "; ";
    }
  } else if (com == "DEEPSLEEP") {
    Serial.println("going into deepsleep");
    Serial.println("going into deepsleep");
    esp_sleep_enable_timer_wakeup(1000 * request[1].toFloat());
    esp_sleep_enable_ext0_wakeup((gpio_num_t)request[2].toInt(), request[3].toInt());
    esp_deep_sleep_start();
  } else if (com == "RESTART") {
    if (millis() > 5000) {
      Serial.println("performing system restart, please stand by...");
      ESP.restart();
    } else {
      returnString = "restart failed, wait 5 seconds and try again";
    }
  }else if (com == "SENDLORA") {
  LoRa.beginPacket();
  LoRa.print(request[1]);
  LoRa.endPacket();
  LoRa.receive();
  } else if (com == "") {
  } else {
    Serial.println("unknown command: " + com);
    returnString = "unknown command: " + com;
  }
  if (returnString == "") {
    returnString = "Done";
  }
  return returnString;
}

String decodeCommand(String commandandID) {

  String request[10];
  int tokenIndex = 0;
  String currentToken = "";
  bool escapeNext = false;
  String lastMessageID = "";

  int idIndex = commandandID.lastIndexOf("#");

  if (commandandID.charAt(idIndex - 1) == '\\') {  //ignore # if it is preceeded by a backslash
    idIndex = -1;
  }

  if (idIndex > 0) {  //if the message has an ID
    lastMessageID = commandandID.substring(idIndex);
  }
  String command = commandandID.substring(0, idIndex) + ",";

  for (int i = 0; i < command.length(); i++) {
    char c = command.charAt(i);
    if (escapeNext) {
      if (c == ',') {
        currentToken += ",";
      } else if (c == '\\') {
        currentToken += "\\";
      } else if (c == 'n') {
        currentToken += "\n";
      } else if (c == 't') {
        currentToken += "\t";
      } else {
        currentToken += "\\";
        currentToken += c;
      }
      escapeNext = false;
    } else if (c == '\\') {
      escapeNext = true;
    } else if (c == ',') {
      request[tokenIndex] = currentToken;
      tokenIndex++;
      currentToken = "";
    } else {
      currentToken += c;
    }
  }

  return processCommandContent(request) + lastMessageID;
}

void checkSerialCommands() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.replace("\r", "");  //courtesy of openAI
    Serial.println(decodeCommand(command));
  }
}

void commandDecoderSetup() {
  EEPROM.begin(EEPROM_SIZE);
}