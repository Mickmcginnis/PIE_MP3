#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Mright = AFMS.getMotor(4);
Adafruit_DCMotor *Mleft = AFMS.getMotor(1);

int sensor1 = 0; //left
int sensor2 = 1; //right
float Sright;
float Sleft;
int threshold;

float Mleft_move_speed = 30;
float Mright_move_speed = 30;
float Mleft_still_speed = 0;
float Mright_still_speed = 0;

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
  threshold = 300;

  if (t >= run_time + check_time) {
    Sright = analogRead(sensor2);
    Sleft = analogRead(sensor1);
    //Serial.println(a);
    //  delay(50);

    if (Sright > threshold && Sleft < threshold){  //Sright on line
      // Move left motor forward
      Mleft->setSpeed(Mleft_move_speed);
      Mleft->run(FORWARD);
      Mright->setSpeed(Mright_still_speed);
      Mright->run(FORWARD);
      
      // Print in format: (Sleft, Mleft, Sright, Mright)
      Serial.print("(");
      Serial.print(Sleft);
      Serial.print(", ");
      Serial.print(Mleft_move_speed);
      Serial.print(", ");
      Serial.println(Sright);
      Serial.print(", ");
      Serial.print(Mright_still_speed);
      Serial.print(")\n");
      delay(50);
    }
    
    else if(Sright < threshold && Sleft > threshold){  //Sleft on line
      // Move right motor forward
      Mright->setSpeed(Mright_move_speed);
      Mright->run(FORWARD);
      Mleft->setSpeed(Mleft_still_speed);
      Mleft->run(FORWARD);

      // Print in format: (Sleft, Mleft, Sright, Mright)
      Serial.print("(");
      Serial.print(Sleft);
      Serial.print(", ");
      Serial.print(Mleft_still_speed);
      Serial.print(", ");
      Serial.println(Sright);
      Serial.print(", ");
      Serial.print(Mright_move_speed);
      Serial.print(")\n");
      delay(50);
    }
    else if(Sright < threshold && Sleft < threshold){
      // Move both motors forward
      Mleft->setSpeed(Mleft_move_speed);
      Mleft->run(FORWARD);
      Mright->setSpeed(Mright_move_speed);
      Mright->run(FORWARD);
      
      // Print in format: (Sleft, Mleft, Sright, Mright)
      Serial.print("(");
      Serial.print(Sleft);
      Serial.print(", ");
      Serial.print(Mleft_move_speed);
      Serial.print(", ");
      Serial.println(Sright);
      Serial.print(", ");
      Serial.print(Mright_move_speed);
      Serial.print(")\n");
      delay(50);
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
