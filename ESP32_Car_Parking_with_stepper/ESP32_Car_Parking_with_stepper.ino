
char ssid[] = "Wifi";
char pass[] = "wifi1234";


#include <ArduinoJson.h>
#include <StreamUtils.h>
#include <HardwareSerial.h>
HardwareSerial sserial(2); // use UART2

uint8_t p[13];

uint8_t Status,
        wDone;

int gotoParking,
    pCurrLoc,
    getCar,
    parkCar;


#include "fbase.h"


void setup()
{
  sserial.begin(9600, SERIAL_8N1, 16, 17);
  sserial.setTimeout(100);
  Serial.begin(115200);

  connectWifi();

  fbaseBegin();
}

void loop()
{
  if (fbaseRead())
  {
    StaticJsonDocument<100> send;
    send["gC"] = (p[getCar] == 1 || getCar > 12) ? 0 : getCar;
    send["pC"] = (p[parkCar] == 0 || parkCar > 12) ? 0 : parkCar;
    serializeJson(send, sserial);
    
    Serial.println("Serial sent");
  }

  recieveData();
  fbaseSend();
}



bool recieveData()
{
  if (sserial.available())
  {
    String recv = sserial.readString();
    Serial.print("\nrecived: ");
    Serial.println(recv);

    StaticJsonDocument<300> receive;
    DeserializationError error = deserializeJson(receive, recv);

    if (error == DeserializationError::Ok)
    {
      p[1] = receive["p1"].as<int>();
      p[2] = receive["p2"].as<int>();
      p[3] = receive["p3"].as<int>();
      p[4] = receive["p4"].as<int>();
      p[5] = receive["p5"].as<int>();
      p[6] = receive["p6"].as<int>();
      p[7] = receive["p7"].as<int>();
      p[8] = receive["p8"].as<int>();
      p[9] = receive["p9"].as<int>();
      p[10] = receive["p10"].as<int>();
      p[11] = receive["p11"].as<int>();
      p[12] = receive["p12"].as<int>();

      Status = receive["S"].as<int>();
      pCurrLoc = receive["PL"].as<int>();

      if (receive["wD"].as<int>() > 0) {
        wDone = 1;
      }

      return 1;
    }
    else {
      Serial.print("\nerror:  ");
      Serial.println(error.c_str());

      while (sserial.available() > 0)    // Flush all bytes in the "link" serial port buffer
        sserial.read();
    }
  }

  return 0;
}
