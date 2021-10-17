#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Mright = AFMS.getMotor(4);
Adafruit_DCMotor *Mleft = AFMS.getMotor(1);

int sensor1 = 0; // left IR sensor
int sensor2 = 1; // right IR sensor
float Sright;    // right sensor value
float Sleft;     // left sensor value
int threshold;   // IR value threshold used to determine if sensor is on ground or on tape

// define motor speeds for various cases
float Mleft_move_speed = 30;
float Mright_move_speed = 30;
float Mleft_still_speed = 0;
float Mright_still_speed = 0;

unsigned int run_time;
const int check_time = 50;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  run_time = millis();
  threshold = 300;
//  float Mleft_move_speed = 30;
//  float Mright_move_speed = 30;
//  float Mleft_still_speed = 0;
//  float Mright_still_speed = 0;
//  int x;
}

void loop() {
  while(Serial.available()) {
    int x = Serial.readString().toInt();
    if ((x % 10) == 0) {
      Mleft_move_speed = x/10;
      Mright_move_speed = x/10;
      }
    if ((x % 1) == 1) {
      threshold = (x-1)/10;
      }
  }
  
  unsigned int t;
  t = millis();

  if (t >= run_time + check_time) {
    Sright = analogRead(sensor2);
    Sleft = analogRead(sensor1);

    if (Sright > threshold && Sleft < threshold) { //Sright on line
      // Move left motor forward, turn off right motor
      Mleft->setSpeed(Mleft_move_speed);
      Mleft->run(FORWARD);
      Mright->setSpeed(Mright_still_speed);
      Mright->run(FORWARD);

      // Print threshold
      Serial.print(threshold);
      Serial.print("\n");
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

    else if (Sright < threshold && Sleft > threshold) { //Sleft on line
      // Move right motor forward, turn off left motor
      Mright->setSpeed(Mright_move_speed);
      Mright->run(FORWARD);
      Mleft->setSpeed(Mleft_still_speed);
      Mleft->run(FORWARD);
      
      // Print threshold
      Serial.print(threshold);
      Serial.print("\n");
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
    else if (Sright < threshold && Sleft < threshold) {
      // Move both motors forward
      Mleft->setSpeed(Mleft_move_speed);
      Mleft->run(FORWARD);
      Mright->setSpeed(Mright_move_speed);
      Mright->run(FORWARD);

      // Print threshold
      Serial.print(threshold);
      Serial.print("\n");
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
    run_time = t;
  }
}
