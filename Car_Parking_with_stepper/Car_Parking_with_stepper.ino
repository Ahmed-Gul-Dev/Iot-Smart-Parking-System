
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint32_t time1,
         time2;

void lcdBegin();
void display(bool i = 0);

#include "sensors.h"
#include "sserial.h"
#include "stepper.h"


void setup()
{
  Serial.begin(115200);

  lcdBegin();

  initSensors();
  initSserial();
  initStepper();

  sserial.print("{\"status\":0}");
}


void loop()
{
  if (recieveData())
  {
    if (getCar > 0)
    {
      Serial.println(getCar);
      readParking();
      Serial.println(!parking[getCar]);
      if (!parking[getCar])
      {
        Serial.println("getCar");
        Status = 1;
        sendData();
        display(Status);

        step_3Run(0);
        step_1Run(p_location[getCar][0]);
        step_2Run(p_location[getCar][1]);
        step_3Run(p_location[getCar][2]);
        delay(500);
        step_2Run(p_location[getCar][1] + 30);
        
        pCurrLoc = getCar;
        p[pCurrLoc] = 1;
        
        sendData();
        display();
        delay(1000);

        step_3Run(0);
        step_1Run(p_location[0][0]);
        step_2Run(p_location[0][1] + 30);
        step_3Run(p_location[0][2]);
        step_2Run(p_location[0][1]);

        pCurrLoc = 0;
        Status = 0;
        wDone = 1;
        sendData();

        while (sserial.available() > 0) sserial.read();
      }
      else {
        Serial.println("no getCar");
        pCurrLoc = 0;
        Status = 0;
        wDone = 1;
        sendData();
      }
    }
    else if (parkCar > 0)
    {
      readParking();
      if (parking[parkCar])
      {
        Status = 1;
        sendData();
        display(Status);

        step_2Run(0);
        step_3Run(p_location[0][2]);
        step_2Run(30);
        step_3Run(0);
        step_2Run(p_location[parkCar][1] + 30);
        step_1Run(p_location[parkCar][0]);
        step_3Run(p_location[parkCar][2]);
        delay(500);
        step_2Run(p_location[parkCar][1]);

        pCurrLoc = parkCar;
        p[pCurrLoc] = 0;
        
        sendData();
        display();
        delay(1000);

        step_3Run(0);
        step_1Run(p_location[0][0]);
        step_2Run(p_location[0][1]);
        step_3Run(p_location[0][2]);

        pCurrLoc = 0;
        Status = 0;
        wDone = 1;
        sendData();

        while (sserial.available() > 0) sserial.read();
      }
      else {
        pCurrLoc = 0;
        Status = 0;
        wDone = 1;
        sendData();
      }
    }
  }
  else if (parkCar == 0 && getCar == 0)
  {
    if (pCurrLoc != 0)
      step_2Run(20);

    step_1Run(p_location[0][0]);
    step_2Run(p_location[0][1]);
    step_3Run(p_location[0][2]);
  }

  if (millis() - time1 > 1000)
  {
    wDone = 0;
    sendData();

    time1 = millis();
  }

  display();
}



void lcdBegin()
{
//  lcd.begin();
  lcd.backlight();
  lcd.clear();

  delay(5);

  lcd.setCursor(0, 0);
  lcd.print("      IOT       ");
  lcd.setCursor(0, 1);
  lcd.print(" Car Parking Sys");

  delay(3000);

  lcd.clear();
}


void display(bool i)
{
  if (millis() - time2 > 1000 || i)
  {
    lcd.setCursor(0, 0);
    lcd.print("Status: ");

    if (Status)
      lcd.print("Moving  ");
    else
      lcd.print("Stoped  ");

    lcd.setCursor(0, 1);
    lcd.print("Curr Pad LOC: ");
    if (!i) {
      lcd.print(pCurrLoc);
      if (pCurrLoc < 10) lcd.print(" ");
    }

    time2 = millis();
  }
}
