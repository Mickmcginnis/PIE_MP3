#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Mright = AFMS.getMotor(4);
Adafruit_DCMotor *Mleft = AFMS.getMotor(1);

int sensor1 = 0;
int sensor2 = 1;
float Sright;
float Sleft;

unsigned int run_time;
const int check_time = 50;

void setup() {
  // put your setup code here, to run once:

  AFMS.begin();
  Serial.begin(9600);
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  run_time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int t;
  t = millis();

  if (t >= run_time + check_time) {
    Sright = analogRead(sensor1);
    Sleft = analogRead(sensor2);
    //Serial.println(a);
    //delay(50);

    if(Sright > 500 && Sleft < 500){  //Sright on line
      Mleft->setSpeed(50);
      Mleft->run(FORWARD);
      Mright->setSpeed(0);
      Mright->run(FORWARD);
    }
    else if(Sright < 500 && Sleft > 500){  //Sleft on line
      Mright->setSpeed(50);
      Mright->run(FORWARD);
      Mleft->setSpeed(0);
      Mleft->run(FORWARD);
    }
    else if(Sright < 500 && Sleft < 500){
      Mleft->setSpeed(50);
      Mleft->run(FORWARD);
      Mright->setSpeed(50);
      Mright->run(FORWARD);
    }

    //From Adafruit documentation, 0=stop, 255=full speed
//    Mright->setSpeed(50);
//    Mright->run(FORWARD);
//    Mleft->setSpeed(50);
//    Mleft->run(FORWARD);

    run_time = t;
  }
  //delay(50);
  //Mright->run(RELEASE);
  //Mleft->run(RELEASE);
}
