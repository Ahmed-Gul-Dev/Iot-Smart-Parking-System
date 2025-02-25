
#define step_1 2
#define step_2 3
#define step_3 5
#define dir_ 4

#define stepDelay 130
#define step1Delay 500
#define step2Delay 200
#define step3Delay 80

#define stepsPerRevolution 800
#define step1PerRevo 50
#define step2PerRevo 400
#define step3PerRevo 800

#define step1MaxLen 330
#define step2MaxLen 500
#define step3MaxLen 300

#define initRunLen ((step1MaxLen > ((step2MaxLen > step3MaxLen) ? step2MaxLen : step3MaxLen)) ? step1MaxLen : ((step2MaxLen > step3MaxLen) ? step2MaxLen : step3MaxLen))


uint16_t p_location[13][3] = {
// m1  m2  m3
  {155,   0, 110},    //ramp location
  {103, 33, 210},     //p1
  {104, 245, 210},    //p2
  {105, 375, 210},    //p3
  {201, 20, 210},     //p4
  {201, 230, 210},    //p5
  {201, 380, 210},    //p6
  {299, 20, 210},     //p7
  {302, 215, 210},    //p8
  {302, 380, 210},    //p9
  {5, 20, 210},      //p10
  {7, 230, 210},     //p11
  {6, 365, 210},     //p12
};



void initStepper();
void initRun();
void Calibrate();
void step_1Run(uint32_t steps);
void step_2Run(uint32_t steps);
void step_3Run(uint32_t steps);
void gotoParking(uint16_t p);




void gotoParking(uint16_t p)
{
  Status = 1;
  sendData();

  display(Status);

  if (pCurrLoc > 0) {
    step_2Run(p_location[pCurrLoc][1]);
    step_3Run(p_location[0][2]);
  }

  step_1Run(p_location[p][0]);
  step_2Run(p_location[p][1]);
  step_3Run(p_location[p][2]);

  pCurrLoc = p;
  Status = 0;
  sendData();
}



void step_1Run(uint32_t steps)
{
  static uint32_t currentLocation;

  if (steps > step1MaxLen) steps = step1MaxLen;

  if (steps > currentLocation)
  {
    digitalWrite(dir_, LOW);
    steps = steps - currentLocation;
    currentLocation += steps;
  }
  else if (currentLocation > steps)
  {
    digitalWrite(dir_, HIGH);
    steps = currentLocation - steps;
    currentLocation -= steps;
  }
  else return;

  Serial.println("-----------------\ncurrent: " + (String)currentLocation);
  Serial.println("steps: " + (String)steps);

  for (uint32_t x = 0; x < steps; x++)
  {
    for (uint16_t j = 0; j < step1PerRevo; j++)
    {
      digitalWrite(step_1, HIGH);
      delayMicroseconds(step1Delay);
      digitalWrite(step_1, LOW);
      delayMicroseconds(step1Delay);
    }
  }
}



void step_2Run(uint32_t steps)
{
  static uint32_t currentLocation;

  if (steps > step2MaxLen) steps = step2MaxLen;

  if (steps > currentLocation)
  {
    digitalWrite(dir_, LOW);
    steps = steps - currentLocation;
    currentLocation += steps;
  }
  else if (currentLocation > steps)
  {
    digitalWrite(dir_, HIGH);
    steps = currentLocation - steps;
    currentLocation -= steps;
  }
  else return;

  Serial.println("-----------------\ncurrent: " + (String)currentLocation);
  Serial.println("steps: " + (String)steps);

  for (uint32_t x = 0; x < steps; x++)
  {
    for (uint16_t j = 0; j < step2PerRevo; j++)
    {
      digitalWrite(step_2, HIGH);
      delayMicroseconds(step2Delay);
      digitalWrite(step_2, LOW);
      delayMicroseconds(step2Delay);
    }
  }
}


void step_3Run(uint32_t steps)
{
  static uint32_t currentLocation;

  if (steps > step3MaxLen) steps = step3MaxLen;

  if (steps > currentLocation)
  {
    digitalWrite(dir_, LOW);
    steps = steps - currentLocation;
    currentLocation += steps;
  }
  else if (currentLocation > steps)
  {
    digitalWrite(dir_, HIGH);
    steps = currentLocation - steps;
    currentLocation -= steps;
  }
  else return;

  Serial.println("-----------------\ncurrent: " + (String)currentLocation);
  Serial.println("steps: " + (String)steps);

  for (uint32_t x = 0; x < steps; x++)
  {
    for (uint16_t j = 0; j < step3PerRevo; j++)
    {
      digitalWrite(step_3, HIGH);
      delayMicroseconds(step3Delay);
      digitalWrite(step_3, LOW);
      delayMicroseconds(step3Delay);
    }
  }
}


void Calibrate()
{
  digitalWrite(dir_, HIGH);

  for (uint32_t i = 0; i <= step3MaxLen; i++)
  {
    readLimit();

    for (uint16_t j = 0; j < step3PerRevo; j++) {
      if (limit[3]) digitalWrite(step_3, HIGH);
      delayMicroseconds(step3Delay);
      digitalWrite(step_3, LOW);
      delayMicroseconds(step3Delay);
    }
    if (!limit[3]) break;
  }

  for (uint32_t i = 0; i <= step2MaxLen; i++)
  {
    readLimit();

    for (uint16_t j = 0; j < step2PerRevo; j++) {
      if (limit[2]) digitalWrite(step_2, HIGH);
      delayMicroseconds(step2Delay);
      digitalWrite(step_2, LOW);
      delayMicroseconds(step2Delay);
    }
    if (!limit[2]) break;
  }

  for (uint32_t i = 0; i <= step1MaxLen; i++)
  {
    readLimit();

    for (uint16_t j = 0; j < step1PerRevo; j++) {
      if (limit[1]) digitalWrite(step_1, HIGH);
      delayMicroseconds(step1Delay);
      digitalWrite(step_1, LOW);
      delayMicroseconds(step1Delay);
    }
    if (!limit[1]) break;
  }
}



void initRun()
{
  digitalWrite(dir_, HIGH);

  for (uint32_t i = 0; i <= initRunLen; i++)
  {
    readLimit();

    Serial.println(i);

    for (uint16_t j = 0; j < stepsPerRevolution; j++)
    {
      if (limit[1]) digitalWrite(step_1, HIGH);
      if (limit[2]) digitalWrite(step_2, HIGH);
      if (limit[3]) digitalWrite(step_3, HIGH);

      delayMicroseconds(stepDelay);

      digitalWrite(step_1, LOW);
      digitalWrite(step_2, LOW);
      digitalWrite(step_3, LOW);

      delayMicroseconds(stepDelay);
    }
  }
}


void initStepper()
{
  pinMode(step_1, OUTPUT);
  pinMode(step_2, OUTPUT);
  pinMode(step_3, OUTPUT);
  pinMode(dir_, OUTPUT);

  Calibrate();
}
