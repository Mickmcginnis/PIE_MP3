float sensor1 = 0;
float a;
void setup() 
{
  Serial.begin(9600); 
  pinMode(sensor1,OUTPUT); 
}
void loop() {  
  a=analogRead(sensor1);
  Serial.println(a); 
  delay(50);
}
