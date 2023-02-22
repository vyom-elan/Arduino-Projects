int pinumber1 = 9;
int pinumber2 = 10;
int pinumber3 = 11;
int pinumber4 = 12;
void setup() {  
  pinMode(pinumber1, OUTPUT);
  pinMode(pinumber2, OUTPUT);
  pinMode(pinumber3, OUTPUT);
  pinMode(pinumber4, OUTPUT);
}
void loop()
{
  digitalWrite(pinumber1, HIGH);   
  delay(1000);
  digitalWrite(pinumber2, HIGH);   
  delay(1000);
  digitalWrite(pinumber3, HIGH);   
  delay(1000);
  digitalWrite(pinumber4, HIGH);   
  delay(1000);                           
  digitalWrite(pinumber1, LOW);    
  delay(1000);                       
  digitalWrite(pinumber2, LOW);    
  delay(1000);                       
  digitalWrite(pinumber3, LOW);    
  delay(1000);                       
  digitalWrite(pinumber4, LOW);    
  delay(1000);                       
}
