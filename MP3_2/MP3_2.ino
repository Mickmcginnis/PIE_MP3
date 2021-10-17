#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Mright = AFMS.getMotor(4);
Adafruit_DCMotor *Mleft = AFMS.getMotor(1);

int sensor1 = 0; // left IR sensor
int sensor2 = 1; // right IR sensor
float Sright;    // right sensor value
float Sleft;     // left sensor value
int threshold = 300;   // IR value threshold used to determine if sensor is on ground or on tape
//int delaytime = 20;
int empty_count = 0;
int turn_case = 0; // was the robot turning right (1), left (2), or forward (3)?
int scan_threshold = 2; // number of times the robot calls the move forward function before it starts scanning for the line

// define motor speeds for various cases
float Mleft_move_speed = 60;
float Mright_move_speed = 60;
float Mleft_still_speed = 30;
float Mright_still_speed = 30;
uint8_t rundirection = BACKWARD;

unsigned int run_time;
const int check_time = 20;

void setup() {
  // put your setup code here, to run once:

  AFMS.begin();
  Serial.begin(115200);
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  run_time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int t;
  t = millis();
  //threshold = 200;

  if (t >= run_time + check_time) {
    Sright = analogRead(sensor2);
    Sleft = analogRead(sensor1);
    //Serial.println(a);
    //  delay(50);

    if (Sright > threshold && Sleft < threshold) { //Sright on line
      // Move left motor forward, turn off right motor
      Mleft->setSpeed(Mleft_move_speed);
      Mleft->run(FORWARD);
      Mright->setSpeed(Mright_still_speed);
      Mright->run(rundirection);

      turn_case = 1; // robot is turning right
      empty_count = 0; // robot has escaped the scan and hit the line

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
      //delay(20);
    }

    else if (Sright < threshold && Sleft > threshold) { //Sleft on line
      // Move right motor forward, turn off left motor
      Mright->setSpeed(Mright_move_speed);
      Mright->run(FORWARD);
      Mleft->setSpeed(Mleft_still_speed);
      Mleft->run(rundirection);

      turn_case = 2; // robot is turning left
      empty_count = 0; // robot has escaped the scan and hit the line

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
      //delay(20);
    }
    else if (Sright < threshold && Sleft < threshold) {
      if (empty_count >= scan_threshold) {
        if (turn_case == 1) { // continue turning to the right
          // Move left motor forward, turn off right motor
          Mleft->setSpeed(Mleft_move_speed);
          Mleft->run(FORWARD);
          Mright->setSpeed(Mright_still_speed);
          Mright->run(rundirection);
        }
        else if (turn_case == 2) {
          // Move right motor forward, turn off left motor
          Mright->setSpeed(Mright_move_speed);
          Mright->run(FORWARD);
          Mleft->setSpeed(Mleft_still_speed);
          Mleft->run(rundirection);
        }
      }
      else {
        // Move both motors forward
      Mleft->setSpeed(Mleft_move_speed);
      Mleft->run(FORWARD);
      Mright->setSpeed(Mright_move_speed);
      Mright->run(FORWARD);

      empty_count ++;
      }
      
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
      //delay(50);
    }
    else if(Sright > threshold && Sleft > threshold){
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
