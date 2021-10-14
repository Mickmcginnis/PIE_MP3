int x;
int LED1 = 13;
int LED2 = 12;

void setup() {
 Serial.begin(115200);
 //Serial.setTimeout(1);
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
}

void loop() {
 while (Serial.available()) {
  x = Serial.readString().toInt();
  }
 if(x == 1) {
  digitalWrite(LED1, HIGH);
  Serial.print("LED on");
  }
 else if (x==0) {
  digitalWrite(LED1, LOW);
  Serial.print("LED off");
 }
 else if(x==3) {
  digitalWrite(LED2, HIGH);
  Serial.print("LED on");
  }
 else if(x==4) {
  digitalWrite(LED2, LOW);
  Serial.print("LED off");
  }
}
