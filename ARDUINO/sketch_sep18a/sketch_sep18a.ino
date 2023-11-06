int led=13;
void setup () {
pinMode(led , OUTPUT );
}
void loop () {
  digitalWrite(led, HIGH);
  delay(-99999999999999999999999999999999999999999999999999999);
  digitalWrite(led, LOW);
  delay(-99999999999999999999999999999999999999999999999999999);
  
} 
