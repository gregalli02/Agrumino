#include "CTBot.h"
#include "Agrumino.h" 
#include <ArduinoJson.h>  
CTBot myBot;

String ssid = "mySSID";    
String pass = "myPassword"; 
String token = "Token";   
uint8_t led = 2;            
Agrumino agrumino;            

void setup() {

  agrumino.setup();
  agrumino.turnBoardOn();
  Serial.begin(115200);

  myBot.wifiConnect(ssid, pass);

  myBot.setTelegramToken(token);

  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

}

void loop() {
  float temperature =         agrumino.readTempC()-8;
  unsigned int soilMoisture = agrumino.readSoil();
  float illuminance =         agrumino.readLux();
  float batteryVoltage =      agrumino.readBatteryVoltage();
  
  TBMessage msg;
  String t = String(temperature);
  String h = String(soilMoisture);
  String l = String(illuminance);
  String b = String(batteryVoltage);

  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("Temperatura")) {                                        
      myBot.sendMessage(msg.sender.id, "misuro la temperatura...");  
      myBot.sendMessage(msg.sender.id, "ci sono " + t + "° C");
    }
    else if (msg.text.equalsIgnoreCase("Umidità")) {                                   
      myBot.sendMessage(msg.sender.id, "misuro l'umidità..."); 
      myBot.sendMessage(msg.sender.id, "l'umidità è " + h + "%");
    }
   else if (msg.text.equalsIgnoreCase("Luce")) {                                   
      myBot.sendMessage(msg.sender.id, "misuro la luce..."); 
      myBot.sendMessage(msg.sender.id, "la luce presente è " + l);
    }
    else if (msg.text.equalsIgnoreCase("Batteria")) {                                   
      myBot.sendMessage(msg.sender.id, "misuro la batteria..."); 
      myBot.sendMessage(msg.sender.id, "la batteria ha " + b + "V");
    }
    else {                                                 
      String reply;
      reply = (String)"Ciao " + msg.sender.username + (String)". Cosa vuoi sapere di Conny?";
      myBot.sendMessage(msg.sender.id, reply); 
    }
  }

  delay(500);
}
