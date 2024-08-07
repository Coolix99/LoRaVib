String loraStreamToString() {
  outputString = "";
  while (LoRa.available()) {
      outputString += (char)LoRa.read();
    }
}

void onReceive(int packetSize) {
  if (packetSize) {
    // Read incoming message
    if (LoRa.available()) {
      uint8_t firstLoraByte = LoRa.read();
      switch (firstLoraByte) {
        case 1:     //command
          String commandReturn = decodeCommand(loraStreamToString());
          decodeCommand("LORASEND,2," + commandReturn);                 //very bad implementation
        break;

        case 2:     //command response
          Serial.println(loraStreamToString());                         //just serial print it i guess?? dunno how to make it better atm
        break;

        case 10:    //morse transmit
        //turn on the vibration motor for 1 second
        break;

      }
    }
  }
}
