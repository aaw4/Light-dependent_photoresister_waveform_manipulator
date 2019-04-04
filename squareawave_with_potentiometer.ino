/*
 * KU EECS 388 project
 * This is the main for the synth
 * blah blah blah 
 */
 // square wave with frequency controlled by potentiometer

const int ledPin = 9;  
const int potPin = A0; 
int value; 


void setup(){
  pinMode(ledPin, OUTPUT); 
  pinMode(potPin, INPUT);
}

void loop(){
  
  value = analogRead(potPin);          //Read and save analog value from potentiometer
  value = map(value, 0, 1023, 10000, 2000); //Map value 0-1023 to 10000-2000 (delay in usec)
  digitalWrite(ledPin, HIGH);          
  delayMicroseconds(value); // delay is now dependent on the potentiometer position.
  digitalWrite(ledPin, LOW);
  delayMicroseconds(value);
}
