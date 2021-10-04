int sensor1 = A0;
void setup() 
{
  Serial.begin(9600); 
  pinMode(sensor1,OUTPUT); 
}
void loop() {  
  float a=analogRead(sensor1);
  Serial.println(a); 
  delay(50);
  }
