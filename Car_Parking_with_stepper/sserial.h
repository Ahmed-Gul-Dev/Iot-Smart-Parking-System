#include <ArduinoJson.h>
#include <StreamUtils.h>
#include <SoftwareSerial.h>


#define sserial_TX 7
#define sserial_RX 8
SoftwareSerial sserial(sserial_RX, sserial_TX); // RX, TX

int16_t GoToparking = -1,
        getCar = 0,
        parkCar = 0;

uint8_t pCurrLoc = 0,
        Status = 0,
        wDone = 0;


void initSserial();
bool recieveData();
void sendData();



bool recieveData()
{
  if (sserial.available())
  {
    String recv = sserial.readString();
    Serial.print("\nrecived: ");
    Serial.println(recv);

    StaticJsonDocument<100> receive;
    DeserializationError error = deserializeJson(receive, recv);

    if (error == DeserializationError::Ok)
    {
      //GoToparking = receive["p"].as<int>();
      getCar = receive["gC"].as<int>();
      parkCar = receive["pC"].as<int>();

      return 1;
    }
    else {
      Serial.println("error");
      Serial.println(error.c_str());

      while (sserial.available() > 0) sserial.read();
    }
  }

  return 0;
}



void sendData()
{
  readParking();

  StaticJsonDocument<200> doc;

  doc["p1"] = parking[1];
  doc["p2"] = parking[2];
  doc["p3"] = parking[3];
  doc["p4"] = parking[4];
  doc["p5"] = parking[5];
  doc["p6"] = parking[6];
  doc["p7"] = parking[7];
  doc["p8"] = parking[8];
  doc["p9"] = parking[9];
  doc["p10"] = parking[10];
  doc["p11"] = parking[11];
  doc["p12"] = parking[12];
  doc["PL"] = pCurrLoc;
  doc["S"] = Status;
  doc["wD"] = wDone;

  serializeJson(doc, sserial);
  delay(1000);
}


void initSserial() {
  sserial.begin(9600);
}
