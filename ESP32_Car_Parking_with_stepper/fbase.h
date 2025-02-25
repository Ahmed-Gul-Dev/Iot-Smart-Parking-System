
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>


#define DATABASE_URL "parkingel19-default-rtdb.firebaseio.com"//"car--parking-default-rtdb.firebaseio.com"
#define DATABASE_SECRET "AIzaSyDoiwXoNuJlmRtCSV_F7RnrwqjQAC-Xa0Q"//"t2pK2SKb4ZB6V0Knn4nkBx4tkehCQxpUn36XlQOq"

#define API_KEY ""
#define USER_EMAIL ""
#define USER_PASSWORD ""


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void connectWifi();
void fbaseBegin();
void fbaseNotify(String _msg = "");
void fbaseSend();
bool fbaseRead();



bool fbaseRead()
{
  static uint32_t time = 5000;

  if (Firebase.ready() && (millis() - time > 2000) )
  {
    Serial.println("fbaseRead");

    if (Firebase.getInt(fbdo, "/Car_parking/gotoParking")) {
      if (fbdo.dataType() == "int") {
        gotoParking = fbdo.intData();
        Serial.println(gotoParking);
      }
    }
    else Serial.println(fbdo.errorReason());


    if (Firebase.getInt(fbdo, "/Car_parking/getCar")) {
      if (fbdo.dataType() == "int") {
        getCar = fbdo.intData();
        Serial.println(getCar);
      }
    }
    else Serial.println(fbdo.errorReason());


    if (Firebase.getInt(fbdo, "/Car_parking/parkCar")) {
      if (fbdo.dataType() == "int") {
        parkCar = fbdo.intData();
        Serial.println(parkCar);
      }
    }
    else Serial.println(fbdo.errorReason());

    time = millis();
    return 1;
  }

  return 0;
}


void fbaseSend()
{
  static uint32_t time;
  if (Firebase.ready() && (millis() - time > 1000))
  {
    Serial.print("Set int async... ");

    Firebase.setBoolAsync(fbdo, "/Car_parking/deviceStatus", true);
    Firebase.setBoolAsync(fbdo, "/Car_parking/S", Status);

    Firebase.setIntAsync(fbdo, "/Car_parking/p1", p[1]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p2", p[2]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p3", p[3]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p4", p[4]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p5", p[5]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p6", p[6]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p7", p[7]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p8", p[8]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p9", p[9]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p10", p[10]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p11", p[11]);
    Firebase.setIntAsync(fbdo, "/Car_parking/p12", p[12]);

    Firebase.setIntAsync(fbdo, "/Car_parking/PL", pCurrLoc);

    if (p[getCar] == 1 || Status || getCar > 12)
      Firebase.setIntAsync(fbdo, "/Car_parking/getCar", 0);

    if (p[parkCar] == 0 || Status || parkCar > 12)
      Firebase.setIntAsync(fbdo, "/Car_parking/parkCar", 0);

    if (gotoParking > 0)
    {
      if (gotoParking < 13)
      {
        if (p[gotoParking])
          Firebase.setIntAsync(fbdo, "/Car_parking/parkCar", gotoParking);
        else
          Firebase.setIntAsync(fbdo, "/Car_parking/getCar", gotoParking);
      }
      Firebase.setIntAsync(fbdo, "/Car_parking/gotoParking", 0);
    }

    if (pCurrLoc > 0)
    {
      if (pCurrLoc == getCar)
        Firebase.setIntAsync(fbdo, "/Car_parking/getCar", 0);

      if (pCurrLoc == parkCar)
        Firebase.setIntAsync(fbdo, "/Car_parking/parkCar", 0);
    }


    if (wDone && parkCar == 0 &&  getCar == 0) {
      wDone = 0;
    }

    Serial.println("\nok");

    time = millis();
  }
}


void fbaseBegin()
{
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  config.signer.tokens.legacy_token = DATABASE_SECRET;

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);

#if defined(ESP8266)
  fbdo.setBSSLBufferSize(512, 2048);
#endif

  delay(200);
  if (Firebase.ready())
    Firebase.setIntAsync(fbdo, "/Car_parking/gotoParking", 0);
}


void connectWifi()
{
  WiFi.mode(WIFI_OFF);
  delay(500);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);

  Serial.print("\nConnecting");

  while (WiFi.status() != WL_CONNECTED && (millis() < 10000)) {
    delay(500);
    Serial.print(".");
  }

  Serial.println((WiFi.status() == WL_CONNECTED) ? "\nConnected to WiFi network" : "\nwifi not connected skiped process");

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}
