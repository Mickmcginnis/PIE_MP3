#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *Mright = AFMS.getMotor(4);
Adafruit_DCMotor *Mleft = AFMS.getMotor(1);

int sensor1 = 0; // left  IR sensor location (A0)
int sensor2 = 1; // right IR sensor location (A1)
float Sright;    // right sensor value
float Sleft;     // left  sensor value
int threshold = 300;   // IR value threshold used to determine if sensor is on ground or on tape
int motorLeftValue;
int motorRightValue;

int forward_count = 0;  //increases by 1 when line is not detected (both sensors off tape); resets to 0 in other cases
int turn_case = 0; // records the most recent turn direction, right (1) or left (2), before robot started moving forward
int scan_threshold = 1; // number of times the robot calls the move forward function before it starts scanning for the line

// define motor speeds for various cases
int Mleft_move_speed = 60;
int Mright_move_speed = 60;
int Mleft_still_speed = 0;
int Mright_still_speed = 0;
uint8_t rundirection = BACKWARD;

unsigned int run_time;
const int check_time = 20;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  run_time = millis();
  threshold = 300;
}

// Define function: Turn right
void turnRight() {
  // Move left motor forward, move right motor backwards
  Mleft->setSpeed(Mleft_move_speed);
  Mleft->run(FORWARD);
  Mright->setSpeed(Mright_still_speed);
  Mright->run(rundirection);

  // Record the directions of the motor values
  motorLeftValue = Mleft_move_speed;
  motorRightValue = Mright_still_speed;
}

// Define function: Turn left
void turnLeft() {
  // Move right motor forward, move left motor backwards
  Mright->setSpeed(Mright_move_speed);
  Mright->run(FORWARD);
  Mleft->setSpeed(Mleft_still_speed);
  Mleft->run(rundirection);

  // Record the directions of the motor values
  motorLeftValue = Mleft_still_speed;
  motorRightValue = Mright_move_speed;
}

// Define function: drive forward with both motors
void driveForward() {
  Mleft->setSpeed(Mleft_move_speed);
  Mleft->run(FORWARD);
  Mright->setSpeed(Mright_move_speed);
  Mright->run(FORWARD);

  // Record the directions of the motor values
  motorLeftValue = Mleft_move_speed;
  motorRightValue = Mright_move_speed;
}

// Define function: Print sensor threshold, sensor values,
// and motor values to Serial Monitor
void serialComms() {
  // Print threshold
  Serial.print(threshold);
  Serial.print("\n");
  // Print in format: (Sleft, Mleft, Sright, Mright)
  Serial.print("(");
  Serial.print(Sleft);
  Serial.print(", ");
  Serial.print(motorLeftValue);
  Serial.print(", ");
  Serial.print(Sright);
  Serial.print(", ");
  Serial.print(motorRightValue);
  Serial.print(")\n");
}

void loop() {
  while (Serial.available()) {
    int x = Serial.readString().toInt();
    if ((x % 10) == 0) {
      Mleft_move_speed = x / 10;
      Mright_move_speed = x / 10;
    }
    if ((x % 10) == 1) {
      threshold = (x - 1) / 10;
    }
  }

  unsigned int t;
  t = millis();

  if (t >= run_time + check_time) {
    Sright = analogRead(sensor2);
    Sleft = analogRead(sensor1);

    if (Sright > threshold && Sleft < threshold) { //Sright on line
      turnRight();

      turn_case = 1; // robot is turning right
      forward_count = 0; // robot has escaped the scan and hit the line

      serialComms();
    }

    else if (Sright < threshold && Sleft > threshold) { //Sleft on line
      turnLeft();

      turn_case = 2; // robot is turning left
      forward_count = 0; // robot has escaped the scan and hit the line

      serialComms();
    }

    else if (Sright < threshold && Sleft < threshold) {
      // both sensors are off the line


      if (forward_count >= scan_threshold) {
        // if the robot has driven forward for more loops than the scan threshold,
        // go back to turning in the most recent direction. This helps the robot navigate around sharp corners
        if (turn_case == 1) { // continue turning to the right
          turnRight();
        }
        else if (turn_case == 2) { // continue turning to the left
          turnLeft();
        }
      }
      else {
        // if forward_count >= scan_threshold is false (forward_count < scan_threshold),
        // robot has not been going forward for very long, and we can keep driving forward
        // Move both motors forward
        driveForward();

        // add one to the value of forward_count; tracks how many times in a row the robot has gone forward
        forward_count ++;
      }

      serialComms();
    }

    else if (Sright > threshold && Sleft > threshold) {
      // if both sensors are on the tape, drive forward
      driveForward();
      serialComms();
    }

    run_time = t;
  }
}
