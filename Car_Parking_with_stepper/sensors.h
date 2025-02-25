

#define CHIP_EN 10
#define DATA 12
#define LOAD 9
#define CLOCK 13

uint8_t limit[4],
        parking[13],
        p[13];


void initSensors();
void readLimit();
void readParking();



void readLimit()
{
  digitalWrite(LOAD, LOW);
  delayMicroseconds(5);
  digitalWrite(LOAD, HIGH);

  digitalWrite(CLOCK, HIGH);
  digitalWrite(CHIP_EN, LOW);

  for (uint8_t i = 0; i < 4; ++i)
  {
    digitalWrite(CLOCK, HIGH);

    limit[i] = digitalRead(DATA);

    digitalWrite(CLOCK, LOW);
  }

  digitalWrite(CHIP_EN, HIGH);
}


void readParking()
{
  digitalWrite(LOAD, LOW);
  delayMicroseconds(5);
  digitalWrite(LOAD, HIGH);

  digitalWrite(CLOCK, HIGH);
  digitalWrite(CHIP_EN, LOW);

  for (uint8_t i = 0; i < 16; ++i)
  {
    digitalWrite(CLOCK, HIGH);

    //if (i > 3) parking[i - 3] = digitalRead(DATA);
    if (i > 3)
      parking[i - 3] = p[i - 3];

    digitalWrite(CLOCK, LOW);
  }

  digitalWrite(CHIP_EN, HIGH);
}




void initSensors()
{
  pinMode(CHIP_EN, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, INPUT);

  digitalWrite(CHIP_EN, HIGH);
  digitalWrite(LOAD, LOW);
  digitalWrite(CLOCK, LOW);

  for (uint8_t i = 0; i < 13; i++) p[i] = 1;
}
